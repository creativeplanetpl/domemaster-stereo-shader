// DomemasterStereo Vray Shader v0.5
// 2015-04-01 10.34 pm
// ---------------------------------
// Ported to Vray 3.0 by Andrew Hazelden
// Based upon the mental ray shader domeAFL_FOV_Stereo  
// by Roberto Ziche

// Todo:
// Work out the return black color code if the check for "if (r < 1.0)" comes back as false

//**************************************************
//**************************************************

#include "vrayplugins.h"
#include "vrayinterface.h"
#include "vrayrenderer.h"
#include "misc_ray.h"
#include "mcsampler.h"
#include "camerasampler.h"

using namespace VR;

#define SEPARATION_FRAME_COUNT 30

struct DomemasterStereo_ParamsStruct {
  int   camera;
  float fov_angle;
  float parallax_distance;
  float separation;
  float forward_tilt;
  int   tilt_compensation;
  int   vertical_mode;
  float separation_map;
  float head_turn_map;
  float head_tilt_map;
  int   flip_x;
  int   flip_y;
  int   poles_corr;
  float poles_corr_start;
  float poles_corr_end;
  float neck_offset;

  int start_frame;
  int end_frame;
  float separation_anim[SEPARATION_FRAME_COUNT];
  float parallax_distance_anim[SEPARATION_FRAME_COUNT];
};

#define CENTERCAM    0
#define LEFTCAM      1
#define RIGHTCAM     2

#define DOME_PI  3.141592653589793238
#define DOME_DTOR  0.0174532925199433 
#define DOME_PIOVER2 1.57079632679489661923 
#define DOME_EPSILON	0.00001

#define GETDIR        0
#define GETORG        1

//**************************************************
// The actual camera
class DomemasterStereoImpl: public VRayCamera {
  DomemasterStereo_ParamsStruct *params;
  VRayRenderer *vray;

	VR::VRayFrameDataCameraFilmTrans* cameraFilmTrans;
public:
	DomemasterStereoImpl() : cameraFilmTrans(NULL) {}

	// From VRayCamera
	int getScreenRay(
		double xs,
		double ys,
		double time,
		const float *rnds,
		int numRnds,
		TraceRay &ray,
		Ireal &mint,
		Ireal &maxt,
		RayDeriv &rayDeriv,
		ShadeCol &multResult,
		uint32 flags
	) const override;

	/// Returns camera flags @see VRayCameraFlags enum
	uint32 getFlags(void) const override {
		return vrayCameraFlags_empty;
	}

    float separation_final;
    float parallax_distance_final;

	void renderBegin(VRayRenderer *vray) {}
	void renderEnd(VRayRenderer *vray) {}
	void frameBegin(VR::VRayRenderer *vray);
	void frameEnd(VRayRenderer *vray) {}

	// From VRayCamera2
	void frameBeginImpl(VR::VRayRenderer *vray, const VR::VRaySequenceData &sdata, const VR::VRayFrameData &fdata) { frameBegin(vray); }

	// Other methods
	void init(DomemasterStereo_ParamsStruct &params);
	simd::Vector3f getDir(double xs, double ys, int rayVsOrgReturnMode) const;
};

void DomemasterStereoImpl::init(DomemasterStereo_ParamsStruct &p) {
  params=&p;
}

void DomemasterStereoImpl::frameBegin(VR::VRayRenderer *vray) {
	this->vray=vray;
	
	const VR::VRayFrameData &_fdata=vray->getFrameData();
	VR::VRayFrameData &fdata=const_cast<VR::VRayFrameData&>(_fdata);

	VR::VRayFrameDataCameraFilmTrans* filmTrans = static_cast<VR::VRayFrameDataCameraFilmTrans*>(fdata.newInterface(EXT_FRAME_DATA_CAMERA_FILM_TRANS));

	if (filmTrans && filmTrans->params.enabled) {
		cameraFilmTrans = filmTrans;
	}

    // get the actual frame number in the chunk
    int separation_var_number = vray->getFrameData().t - params->start_frame;
    
    // store the final version of parameters of for this frame, so we could use this later in other metods
    const int frameNumberValid=(separation_var_number>=0 && separation_var_number<SEPARATION_FRAME_COUNT);
    separation_final=frameNumberValid ? params->separation_anim[separation_var_number] : 0.0f;
    parallax_distance_final=frameNumberValid ? params->parallax_distance_anim[separation_var_number] : 0.0f;
}

simd::Vector3f DomemasterStereoImpl::getDir(double xs, double ys, int rayVsOrgReturnMode) const {
  // Note: rayVsOrgReturnMode == 0 means ray, rayVsOrgReturnMode == 1 means org data is returned

  const VR::VRayFrameData &fdata=vray->getFrameData();

  // Swap X-Y to rotate the cartesian axis 90 degrees CW
  double ry = (xs-fdata.imgWidth*0.5f)/(fdata.imgWidth*0.5f);
  double rx = (ys-fdata.imgHeight*0.5f)/(fdata.imgHeight*0.5f);
  
  double r, phi, theta, rot, tmp, tmpY, tmpZ;
  double sinP, cosP, sinT, cosT, sinR, cosR, sinD, cosD;

  VR::Vector org, ray, target, htarget;

  // Head tilt transform matrix
  VR::Matrix tilt(1);
  
  // Check the stereo camera view for 0=center, 1=Left, 2=Right
  int stereo_camera = params->camera;
  
  double fov_angle = params->fov_angle * DOME_DTOR;
  // when we really need to use our parameter, instead of reading static params,
  // we use the previously calculated ones.
  float parallax_distance = this->parallax_distance_final; // this is keyable
  float separation = this->separation_final; // this is keyable
  double forward_tilt = params->forward_tilt * DOME_DTOR;
  float tilt_compensation = params->tilt_compensation;
  int vertical_mode = params->vertical_mode;
  int flip_x = params->flip_x;
  int flip_y = params->flip_y;
  int poles_corr = params->poles_corr;
  float poles_corr_start = params->poles_corr_start * DOME_DTOR;
  float poles_corr_end = params->poles_corr_end * DOME_DTOR;
  float neck_offset = params->neck_offset;

  // additional parameters
  double deltaY = 2.0f * forward_tilt / DOME_PI;
  double rx2 = -(rx + deltaY);
  double r2 = sqrt((rx2 * rx2) + (ry * ry));

  // check poles correction angles
  if (poles_corr_end < poles_corr_start)
    poles_corr_end = poles_corr_start;
  
  // calculate vector to tilted dome pole
  VR::Vector poleTarget;
  poleTarget.x = 0.0f;
  poleTarget.y = (float)(sin(forward_tilt));
  poleTarget.z = (float)(-cos(forward_tilt));
  
  // Compute radius
  r = sqrt((rx * rx) + (ry * ry));

  // Check if the shader should return black
  if (r < 1.0) {
    // Compute phi angle
    if ((r > -DOME_EPSILON) && (r < DOME_EPSILON)) {
      phi = 0.0;
    } else {
      phi = atan2(ry,rx);
    }

    // Compute theta angle
    theta = r * (fov_angle/2.0);
    
    // Start by matching camera (center camera)
    org.x = org.y = org.z = 0.0;
    
    // Compute commonly used values
    sinP = sin(phi);
    cosP = cos(phi);
    sinT = sin(theta);
    cosT = cos(theta);
    
    // Center camera target vector (normalized)
    target.x = (float)(sinP * sinT);
    target.y = (float)(-cosP * sinT);
    target.z = (float)(-cosT);
    
    // Camera selection and initial position
    // 0=center, 1=Left, 2=Right
    if (stereo_camera != CENTERCAM) {
    
      //float separation_mult = params->separation_map;
      //float head_turn_mult = params->head_turn_map;
      //float head_tilt = params->head_tilt_map;

      float separation_mult = 0.0f;
      if (r2 >= 0) {
        // separation_mult = 1.0f * r2 * 10 - 1.5;
        // separation_mult = (-cos((1.0f * r2 * 5) * DOME_PI) + 1) / 2;
        separation_mult = 1.0f * r2 * 5;
        if (r2 > 0.20) {
          separation_mult = 1.0f;
        }
      }

      float separation_mult_zenith = 0.0f;
      if (r >= 0) {
        // separation_mult = 1.0f * r2 * 10 - 1.5;
        // separation_mult = (-cos((1.0f * r2 * 5) * DOME_PI) + 1) / 2;
        separation_mult_zenith = 1.0f * r * 5;
        if (r > 0.20) {
          separation_mult_zenith = 1.0f;
        }
      }

      float separation_mult_auto = 1.0f;
      float head_turn_mult = 1.0f;
      float head_tilt = 0.5f;

      // Additional automatic separation fade
      if (poles_corr && !vertical_mode) {
        float tmpTheta;
        if (tilt_compensation) {
          // angle between target vector and tilted dome pole vector
          tmpTheta = acos(target*poleTarget);
          tmpTheta = abs(DOME_PIOVER2 - tmpTheta);
        } else {
          // angle from zenith
          tmpTheta = abs(DOME_PIOVER2 - theta);
        }
        if (tmpTheta > poles_corr_start) {
          if (tmpTheta < poles_corr_end) {
            float fadePos = (tmpTheta - poles_corr_start) / (poles_corr_end - poles_corr_start);
            separation_mult_auto = (cos(fadePos*DOME_PI) + 1.0f) / 2.0f;
          }
          else
            separation_mult_auto = 0.0f;
        }
      }
      // combine both separation values
      separation_mult *= separation_mult_auto;
    
      // camera selection and initial position
      // use the keyable separation
      if (stereo_camera == LEFTCAM) {
        org.x = (float)(-separation * separation_mult / 2.0);
      }
      else if (stereo_camera == RIGHTCAM) {
        org.x = (float)(separation * separation_mult / 2.0);
      }
      
      
      // Tilted dome mode ON
      if(tilt_compensation) {
        // head rotation
        tmpY = target.y * cos(-forward_tilt) - target.z * sin(-forward_tilt);
        tmpZ = target.z * cos(-forward_tilt) + target.y * sin(-forward_tilt);
        rot = atan2(target.x,-tmpY) * head_turn_mult;
        
        if (vertical_mode) {
          rot *= fabs(sinP);
        }
        
        sinR = sin(rot); 
        cosR = cos(rot);
        sinD = sin(forward_tilt);
        cosD = cos(forward_tilt);
        
        // rotate camera
        tmp = org.x * cosR - org.y * sinR;
        org.y = (float)(org.y * cosR + org.x * sinR);
        org.x = (float)tmp;
        
        // compensate for dome tilt
        tmp = org.y * cosD - org.z * sinD;
        org.z = (float)(org.z * cosD + org.y * sinD);
        org.y = (float)tmp;

        // calculate head target
        tmp = sqrt(target.x * target.x + tmpY * tmpY);
        htarget.x = (float)(sinR * tmp);
        htarget.y = (float)(-cosR * tmp);
        htarget.z = (float)tmpZ;
        
        // dome rotation again on head target
        tmp = htarget.y * cosD - htarget.z * sinD;
        htarget.z = (float)(htarget.z * cosD + htarget.y * sinD);
        htarget.y = (float)tmp;
      } else {
        // Tilted dome mode OFF
        
        // Vertical Mode ON
        if (vertical_mode) {
          // head rotation
          rot = atan2(target.x,-target.z) * head_turn_mult * fabs(sinP);
          sinR = sin(rot);
          cosR = cos(rot);
          
          // rotate camera
          tmp = org.x * cosR - org.z * sinR;
          org.z = (float)(org.z * cosR + org.x * sinR);
          org.x = (float)tmp;
          
          // calculate head target
          tmp = sqrt(target.x * target.x + target.z * target.z);
          htarget.x = (float)(sinR * tmp);
          htarget.y = (float)target.y;
          htarget.z = (float)(-cosR * tmp);
        } else {            
          // Vertical Mode OFF  (horizontal dome mode)
          
          // Head rotation
          rot = phi * head_turn_mult;
          sinR = sin(rot);
          cosR = cos(rot);
          
          // Rotate camera
          tmp = (org.x * cosR) - (org.y * sinR);
          org.y = (float)((org.y * cosR) + (org.x * sinR));
          org.x = (float)tmp;
          
          // calculate head target
          htarget.x = (float)(sinR * sinT);
          htarget.y = (float)(-cosR * sinT);
          htarget.z = (float)target.z;
        }
      }

      // head tilt (in rad)
      head_tilt = (float)((head_tilt - 0.5) * DOME_PI);
      
      float cT = cos(head_tilt);
      float sT = sin(head_tilt);
      tilt[0][0] = cT + htarget.x*htarget.x*(1 - cT);
      tilt[0][1] = htarget.x*htarget.y*(1 - cT) - htarget.z*sT;
      tilt[0][2] = htarget.x*htarget.z*(1 - cT) + htarget.y*sT;
      tilt[1][0] = htarget.y*htarget.x*(1 - cT) + htarget.z*sT;
      tilt[1][1] = cT + htarget.y*htarget.y*(1 - cT);
      tilt[1][2] = htarget.y*htarget.z*(1 - cT) - htarget.x*sT;
      tilt[2][0] = htarget.z*htarget.x*(1 - cT) - htarget.y*sT;
      tilt[2][1] = htarget.z*htarget.y*(1 - cT) + htarget.x*sT;
      tilt[2][2] = cT + htarget.z*htarget.z*(1 - cT);

      org = org * tilt;
      
      // Adjust org for Neck offset
      org = org + target * neck_offset;

      // Compute ray from camera to target
      target *= parallax_distance;
      ray = target - org;
      ray = normalize(ray);

    } else {

      // center cam
      ray = target;

    }
    
    // Flip the X ray direction about the Y-axis
    if(flip_x) {
      org.x = -org.x;
      ray.x = -ray.x;
    }
    
    // Flip the Y ray direction about the X-axis
    if(flip_y) {
      org.y = -org.y;
      ray.y = -ray.y;
    }

    if (rayVsOrgReturnMode == GETDIR){
      return simd::Vector3f(ray);
    }
    else {  
      // GETORG
      return simd::Vector3f(org);
    }
    
  } else {
    // Outside image circular space
    ray.x = ray.y = ray.z = 0.0f;
    return simd::Vector3f(ray);
  } 
}

int DomemasterStereoImpl::getScreenRay(
		double xs,
		double ys,
		double time,
		const float *rnds,
		int numRnds,
		TraceRay &ray,
		Ireal &mint,
		Ireal &maxt,
		RayDeriv &rayDeriv,
		ShadeCol &multResult,
		uint32 flags
) const {
	if (cameraFilmTrans) {
		const VR::VRayFrameData& fdata = vray->getFrameData();
		cameraFilmTrans->transformScreenRay(xs, ys, fdata.rgnLeft, fdata.rgnTop, fdata.imgWidth, fdata.imgHeight);
	}

  simd::Vector3f dir = getDir(xs, ys, GETDIR);   //Return the dir data from the getDir function
  if (dir.x() == 0.0f && dir.y() == 0.0f && dir.z() == 0.0f)  // outside circular image
    return false;   // [rz] Not working. Does not render as black.

  simd::Vector3f org = getDir(xs, ys, GETORG);   //Return the org data from the getDir function
  
  rayDeriv.dPdx.makeZero();
  rayDeriv.dPdy.makeZero();

  double delta=0.01f;
  rayDeriv.dDdx=(getDir(xs+delta, ys, 0)-getDir(xs-delta, ys, 0))/float(delta*2.0f);
  rayDeriv.dDdy=(getDir(xs, ys+delta, 0)-getDir(xs, ys-delta, 0))/float(delta*2.0f);
  
  const VR::VRayFrameData &fdata=vray->getFrameData();
  ray.p = fdata.camToWorld.offs + fdata.camToWorld.m*org;
  ray.dir = fdata.camToWorld.m*dir;;

  mint=0.0f;
  maxt=LARGE_FLOAT;

  return true;
}


//**************************************************
// Plugin stuff

// This structure describes the parameters of the plugin; the parameters must be of the
// exact same type and in the same order as in the DomemasterStereo_ParamsStruct structure.
struct DomemasterStereo_Params: VRayParameterListDesc {
	DomemasterStereo_Params(void) {
    addParamInt("camera", 0, -1, "Center, Left, Right Camera Views");
    addParamFloat("fov_angle", 180.0f, -1, "Field of View");
    addParamFloat("parallax_distance", 360.0f, -1, "Zero Parallax Distance");
    addParamFloat("separation", 6.5f, -1, "Camera Separation Distance");
    addParamFloat("forward_tilt", 0.0f, -1, "Forward Tilt");
    addParamBool("tilt_compensation", false, -1, "Tilt Compensation Mode");
    addParamBool("vertical_mode", false, -1, "Vertical Mode");
    addParamFloat("separation_map", 1.0f, -1, "Separation Map");
    addParamFloat("head_turn_map", 1.0f, -1, "Head Turn Map");
    addParamFloat("head_tilt_map", 0.5f, -1, "Head Tilt map");
    addParamBool("flip_x", false, -1, "Flip X");
    addParamBool("flip_y", false, -1, "Flip Y");
	addParamBool("poles_corr", true, -1, "Poles Correction");
	addParamFloat("poles_corr_start", 45.f, -1, "Poles Correction Start Angle");
	addParamFloat("poles_corr_end", 85.f, -1, "Poles Correction End Angle");
    addParamFloat("neck_offset", 0.0f, -1, "Neck Offset");

    // For the plugin parameters, they cannot be animated if rendered in chunks bigger than 1 frame.
    // The domemaster3D plugin always reads the value from the first frame in chunk
    // To be able to read the correct value for each frame in the chunk for the parameter, it needs to be
    // explicity enumerated.
    // for our needs, we had two parameters we wanted to animate: Separation and Paralax Distance.
    // To be able to get the actual frame number in chunk,
    // we had to pass the first frame in the chunk and last frame in the chunk as the arameters
    addParamInt("start_frame", 0, -1, "Frame Start");
    addParamInt("end_frame", 0, -1, "Frame End");

    // Also for each frame in the chunk we created a parameter for its Separation, and Paralax Distance
    // The Separation parameters:
    addParamFloat("separation_0", 0.0f, -1, "Separation_0");
    addParamFloat("separation_1", 0.0f, -1, "Separation_1");
    addParamFloat("separation_2", 0.0f, -1, "Separation_2");
    addParamFloat("separation_3", 0.0f, -1, "Separation_3");
    addParamFloat("separation_4", 0.0f, -1, "Separation_4");
    addParamFloat("separation_5", 0.0f, -1, "Separation_5");
    addParamFloat("separation_6", 0.0f, -1, "Separation_6");
    addParamFloat("separation_7", 0.0f, -1, "Separation_7");
    addParamFloat("separation_8", 0.0f, -1, "Separation_8");
    addParamFloat("separation_9", 0.0f, -1, "Separation_9");
    addParamFloat("separation_10", 0.0f, -1, "Separation_10");
    addParamFloat("separation_11", 0.0f, -1, "Separation_11");
    addParamFloat("separation_12", 0.0f, -1, "Separation_12");
    addParamFloat("separation_13", 0.0f, -1, "Separation_13");
    addParamFloat("separation_14", 0.0f, -1, "Separation_14");
    addParamFloat("separation_15", 0.0f, -1, "Separation_15");
    addParamFloat("separation_16", 0.0f, -1, "Separation_16");
    addParamFloat("separation_17", 0.0f, -1, "Separation_17");
    addParamFloat("separation_18", 0.0f, -1, "Separation_18");
    addParamFloat("separation_19", 0.0f, -1, "Separation_19");
    addParamFloat("separation_20", 0.0f, -1, "Separation_20");
    addParamFloat("separation_21", 0.0f, -1, "Separation_21");
    addParamFloat("separation_22", 0.0f, -1, "Separation_22");
    addParamFloat("separation_23", 0.0f, -1, "Separation_23");
    addParamFloat("separation_24", 0.0f, -1, "Separation_24");
    addParamFloat("separation_25", 0.0f, -1, "Separation_25");
    addParamFloat("separation_26", 0.0f, -1, "Separation_26");
    addParamFloat("separation_27", 0.0f, -1, "Separation_27");
    addParamFloat("separation_28", 0.0f, -1, "Separation_28");
    addParamFloat("separation_29", 0.0f, -1, "Separation_29");

    // The Parallax Distance Parameters
    addParamFloat("parallax_distance_0", 0.0f, -1, "parallax_distance_0");
    addParamFloat("parallax_distance_1", 0.0f, -1, "parallax_distance_1");
    addParamFloat("parallax_distance_2", 0.0f, -1, "parallax_distance_2");
    addParamFloat("parallax_distance_3", 0.0f, -1, "parallax_distance_3");
    addParamFloat("parallax_distance_4", 0.0f, -1, "parallax_distance_4");
    addParamFloat("parallax_distance_5", 0.0f, -1, "parallax_distance_5");
    addParamFloat("parallax_distance_6", 0.0f, -1, "parallax_distance_6");
    addParamFloat("parallax_distance_7", 0.0f, -1, "parallax_distance_7");
    addParamFloat("parallax_distance_8", 0.0f, -1, "parallax_distance_8");
    addParamFloat("parallax_distance_9", 0.0f, -1, "parallax_distance_9");
    addParamFloat("parallax_distance_10", 0.0f, -1, "parallax_distance_10");
    addParamFloat("parallax_distance_11", 0.0f, -1, "parallax_distance_11");
    addParamFloat("parallax_distance_12", 0.0f, -1, "parallax_distance_12");
    addParamFloat("parallax_distance_13", 0.0f, -1, "parallax_distance_13");
    addParamFloat("parallax_distance_14", 0.0f, -1, "parallax_distance_14");
    addParamFloat("parallax_distance_15", 0.0f, -1, "parallax_distance_15");
    addParamFloat("parallax_distance_16", 0.0f, -1, "parallax_distance_16");
    addParamFloat("parallax_distance_17", 0.0f, -1, "parallax_distance_17");
    addParamFloat("parallax_distance_18", 0.0f, -1, "parallax_distance_18");
    addParamFloat("parallax_distance_19", 0.0f, -1, "parallax_distance_19");
    addParamFloat("parallax_distance_20", 0.0f, -1, "parallax_distance_20");
    addParamFloat("parallax_distance_21", 0.0f, -1, "parallax_distance_21");
    addParamFloat("parallax_distance_22", 0.0f, -1, "parallax_distance_22");
    addParamFloat("parallax_distance_23", 0.0f, -1, "parallax_distance_23");
    addParamFloat("parallax_distance_24", 0.0f, -1, "parallax_distance_24");
    addParamFloat("parallax_distance_25", 0.0f, -1, "parallax_distance_25");
    addParamFloat("parallax_distance_26", 0.0f, -1, "parallax_distance_26");
    addParamFloat("parallax_distance_27", 0.0f, -1, "parallax_distance_27");
    addParamFloat("parallax_distance_28", 0.0f, -1, "parallax_distance_28");
    addParamFloat("parallax_distance_29", 0.0f, -1, "parallax_distance_29");
	}
};

class DomemasterStereo: public VRayRenderSettings {
	// The actual camera that will be used
	DomemasterStereoImpl camera;

	// Cached parameters
	DomemasterStereo_ParamsStruct params;
public:
	DomemasterStereo(VRayPluginDesc *pluginDesc):VRayRenderSettings(pluginDesc) {
    // We want the parameters to be cached to the params structure
    paramList->setParamCache("camera", &params.camera);
    paramList->setParamCache("fov_angle", &params.fov_angle);
    paramList->setParamCache("parallax_distance", &params.parallax_distance);
    paramList->setParamCache("separation", &params.separation);
    paramList->setParamCache("forward_tilt", &params.forward_tilt);
    paramList->setParamCache("tilt_compensation", &params.tilt_compensation);
    paramList->setParamCache("vertical_mode", &params.vertical_mode);
    paramList->setParamCache("separation_map", &params.separation_map);
    paramList->setParamCache("head_turn_map", &params.head_turn_map);
    paramList->setParamCache("head_tilt_map", &params.head_tilt_map);
    paramList->setParamCache("flip_x", &params.flip_x);
    paramList->setParamCache("flip_y", &params.flip_y);
    paramList->setParamCache("poles_corr", &params.poles_corr);
    paramList->setParamCache("poles_corr_start", &params.poles_corr_start);
    paramList->setParamCache("poles_corr_end", &params.poles_corr_end);
    paramList->setParamCache("neck_offset", &params.neck_offset);
    paramList->setParamCache("start_frame", &params.start_frame);
    paramList->setParamCache("end_frame", &params.end_frame);
    paramList->setParamCache("separation_0", &params.separation_anim[0]);
    paramList->setParamCache("separation_1", &params.separation_anim[1]);
    paramList->setParamCache("separation_2", &params.separation_anim[2]);
    paramList->setParamCache("separation_3", &params.separation_anim[3]);
    paramList->setParamCache("separation_4", &params.separation_anim[4]);
    paramList->setParamCache("separation_5", &params.separation_anim[5]);
    paramList->setParamCache("separation_6", &params.separation_anim[6]);
    paramList->setParamCache("separation_7", &params.separation_anim[7]);
    paramList->setParamCache("separation_8", &params.separation_anim[8]);
    paramList->setParamCache("separation_9", &params.separation_anim[9]);
    paramList->setParamCache("separation_10", &params.separation_anim[10]);
    paramList->setParamCache("separation_11", &params.separation_anim[11]);
    paramList->setParamCache("separation_12", &params.separation_anim[12]);
    paramList->setParamCache("separation_13", &params.separation_anim[13]);
    paramList->setParamCache("separation_14", &params.separation_anim[14]);
    paramList->setParamCache("separation_15", &params.separation_anim[15]);
    paramList->setParamCache("separation_16", &params.separation_anim[16]);
    paramList->setParamCache("separation_17", &params.separation_anim[17]);
    paramList->setParamCache("separation_18", &params.separation_anim[18]);
    paramList->setParamCache("separation_19", &params.separation_anim[19]);
    paramList->setParamCache("separation_20", &params.separation_anim[20]);
    paramList->setParamCache("separation_21", &params.separation_anim[21]);
    paramList->setParamCache("separation_22", &params.separation_anim[22]);
    paramList->setParamCache("separation_23", &params.separation_anim[23]);
    paramList->setParamCache("separation_24", &params.separation_anim[24]);
    paramList->setParamCache("separation_25", &params.separation_anim[25]);
    paramList->setParamCache("separation_26", &params.separation_anim[26]);
    paramList->setParamCache("separation_27", &params.separation_anim[27]);
    paramList->setParamCache("separation_28", &params.separation_anim[28]);
    paramList->setParamCache("separation_29", &params.separation_anim[29]);
    paramList->setParamCache("parallax_distance_0", &params.parallax_distance_anim[0]);
    paramList->setParamCache("parallax_distance_1", &params.parallax_distance_anim[1]);
    paramList->setParamCache("parallax_distance_2", &params.parallax_distance_anim[2]);
    paramList->setParamCache("parallax_distance_3", &params.parallax_distance_anim[3]);
    paramList->setParamCache("parallax_distance_4", &params.parallax_distance_anim[4]);
    paramList->setParamCache("parallax_distance_5", &params.parallax_distance_anim[5]);
    paramList->setParamCache("parallax_distance_6", &params.parallax_distance_anim[6]);
    paramList->setParamCache("parallax_distance_7", &params.parallax_distance_anim[7]);
    paramList->setParamCache("parallax_distance_8", &params.parallax_distance_anim[8]);
    paramList->setParamCache("parallax_distance_9", &params.parallax_distance_anim[9]);
    paramList->setParamCache("parallax_distance_10", &params.parallax_distance_anim[10]);
    paramList->setParamCache("parallax_distance_11", &params.parallax_distance_anim[11]);
    paramList->setParamCache("parallax_distance_12", &params.parallax_distance_anim[12]);
    paramList->setParamCache("parallax_distance_13", &params.parallax_distance_anim[13]);
    paramList->setParamCache("parallax_distance_14", &params.parallax_distance_anim[14]);
    paramList->setParamCache("parallax_distance_15", &params.parallax_distance_anim[15]);
    paramList->setParamCache("parallax_distance_16", &params.parallax_distance_anim[16]);
    paramList->setParamCache("parallax_distance_17", &params.parallax_distance_anim[17]);
    paramList->setParamCache("parallax_distance_18", &params.parallax_distance_anim[18]);
    paramList->setParamCache("parallax_distance_19", &params.parallax_distance_anim[19]);
    paramList->setParamCache("parallax_distance_20", &params.parallax_distance_anim[20]);
    paramList->setParamCache("parallax_distance_21", &params.parallax_distance_anim[21]);
    paramList->setParamCache("parallax_distance_22", &params.parallax_distance_anim[22]);
    paramList->setParamCache("parallax_distance_23", &params.parallax_distance_anim[23]);
    paramList->setParamCache("parallax_distance_24", &params.parallax_distance_anim[24]);
    paramList->setParamCache("parallax_distance_25", &params.parallax_distance_anim[25]);
    paramList->setParamCache("parallax_distance_26", &params.parallax_distance_anim[26]);
    paramList->setParamCache("parallax_distance_27", &params.parallax_distance_anim[27]);
    paramList->setParamCache("parallax_distance_28", &params.parallax_distance_anim[28]);
    paramList->setParamCache("parallax_distance_29", &params.parallax_distance_anim[29]);
	}

	// From RenderSettingsExtension
	void setupSequenceData(VR::VRaySequenceData &sdata) {
		// Note that this method is called before frameBegin(), and so parameters have not been cached
		// Therefore, cache the parameters here - computes the actual parameter values from the scene
		// description
		paramList->cacheParams();

		// Initialize the camera
		camera.init(params);

		// Set the camera into the sequence data so that VRay can use it
		sdata.cameraRaySampler=static_cast<VRayCamera*>(&camera);
	}
	
	void setupFrameData(VR::VRayFrameData &fdata) {
		paramList->cacheParams(fdata.t);
		// The field of view may be specified by a SettingsCamera plug-in, so only set it here if explicitly specified;
		//if (paramList->getParam("fov")) fdata.fov=params.fov;
	}
	void renderEnd(VR::VRayRenderer *vray) {
		VRayRenderSettings::renderEnd(vray);
		
		VRaySequenceData &sdata=const_cast<VR::VRaySequenceData&>(vray->getSequenceData());
		VR::VRayCamera *cameraSampler=static_cast<VR::VRayCamera*>(&camera);
		vray->setCameraRaySampler(NULL, 1, cameraSampler);
	}
};

#define DomemasterStereo_PluginID PluginID(LARGE_CONST(1185227))

PLUGIN_LIBRARY("Cameras", "V-Ray Cameras");
PLUGIN_DESC(DomemasterStereo_PluginID, "DomemasterStereo", "DomemasterStereo plugin for V-Ray", DomemasterStereo, DomemasterStereo_Params, EXT_RENDER_SETTINGS);
