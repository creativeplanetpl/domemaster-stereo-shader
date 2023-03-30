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

  //

  int start_frame;
  int end_frame;
  float separation_0;
  float separation_1;
  float separation_2;
  float separation_3;
  float separation_4;
  float separation_5;
  float separation_6;
  float separation_7;
  float separation_8;
  float separation_9;
  float separation_10;
  float separation_11;
  float separation_12;
  float separation_13;
  float separation_14;
  float separation_15;
  float separation_16;
  float separation_17;
  float separation_18;
  float separation_19;
  float separation_20;
  float separation_21;
  float separation_22;
  float separation_23;
  float separation_24;
  float separation_25;
  float separation_26;
  float separation_27;
  float separation_28;
  float separation_29;
  float separation_30;
  float separation_31;
  float separation_32;
  float separation_33;
  float separation_34;
  float separation_35;
  float separation_36;
  float separation_37;
  float separation_38;
  float separation_39;
  float separation_40;
  float separation_41;
  float separation_42;
  float separation_43;
  float separation_44;
  float separation_45;
  float separation_46;
  float separation_47;
  float separation_48;
  float separation_49;
  float separation_50;
  float separation_51;
  float separation_52;
  float separation_53;
  float separation_54;
  float separation_55;
  float separation_56;
  float separation_57;
  float separation_58;
  float separation_59;
  float separation_60;
  float separation_61;
  float separation_62;
  float separation_63;
  float separation_64;
  float separation_65;
  float separation_66;
  float separation_67;
  float separation_68;
  float separation_69;
  float separation_70;
  float separation_71;
  float separation_72;
  float separation_73;
  float separation_74;
  float separation_75;
  float separation_76;
  float separation_77;
  float separation_78;
  float separation_79;
  float separation_80;
  float separation_81;
  float separation_82;
  float separation_83;
  float separation_84;
  float separation_85;
  float separation_86;
  float separation_87;
  float separation_88;
  float separation_89;
  float separation_90;
  float separation_91;
  float separation_92;
  float separation_93;
  float separation_94;
  float separation_95;
  float separation_96;
  float separation_97;
  float separation_98;
  float separation_99;

  float parallax_distance_0;
  float parallax_distance_1;
  float parallax_distance_2;
  float parallax_distance_3;
  float parallax_distance_4;
  float parallax_distance_5;
  float parallax_distance_6;
  float parallax_distance_7;
  float parallax_distance_8;
  float parallax_distance_9;
  float parallax_distance_10;
  float parallax_distance_11;
  float parallax_distance_12;
  float parallax_distance_13;
  float parallax_distance_14;
  float parallax_distance_15;
  float parallax_distance_16;
  float parallax_distance_17;
  float parallax_distance_18;
  float parallax_distance_19;
  float parallax_distance_20;
  float parallax_distance_21;
  float parallax_distance_22;
  float parallax_distance_23;
  float parallax_distance_24;
  float parallax_distance_25;
  float parallax_distance_26;
  float parallax_distance_27;
  float parallax_distance_28;
  float parallax_distance_29;
  float parallax_distance_30;
  float parallax_distance_31;
  float parallax_distance_32;
  float parallax_distance_33;
  float parallax_distance_34;
  float parallax_distance_35;
  float parallax_distance_36;
  float parallax_distance_37;
  float parallax_distance_38;
  float parallax_distance_39;
  float parallax_distance_40;
  float parallax_distance_41;
  float parallax_distance_42;
  float parallax_distance_43;
  float parallax_distance_44;
  float parallax_distance_45;
  float parallax_distance_46;
  float parallax_distance_47;
  float parallax_distance_48;
  float parallax_distance_49;
  float parallax_distance_50;
  float parallax_distance_51;
  float parallax_distance_52;
  float parallax_distance_53;
  float parallax_distance_54;
  float parallax_distance_55;
  float parallax_distance_56;
  float parallax_distance_57;
  float parallax_distance_58;
  float parallax_distance_59;
  float parallax_distance_60;
  float parallax_distance_61;
  float parallax_distance_62;
  float parallax_distance_63;
  float parallax_distance_64;
  float parallax_distance_65;
  float parallax_distance_66;
  float parallax_distance_67;
  float parallax_distance_68;
  float parallax_distance_69;
  float parallax_distance_70;
  float parallax_distance_71;
  float parallax_distance_72;
  float parallax_distance_73;
  float parallax_distance_74;
  float parallax_distance_75;
  float parallax_distance_76;
  float parallax_distance_77;
  float parallax_distance_78;
  float parallax_distance_79;
  float parallax_distance_80;
  float parallax_distance_81;
  float parallax_distance_82;
  float parallax_distance_83;
  float parallax_distance_84;
  float parallax_distance_85;
  float parallax_distance_86;
  float parallax_distance_87;
  float parallax_distance_88;
  float parallax_distance_89;
  float parallax_distance_90;
  float parallax_distance_91;
  float parallax_distance_92;
  float parallax_distance_93;
  float parallax_distance_94;
  float parallax_distance_95;
  float parallax_distance_96;
  float parallax_distance_97;
  float parallax_distance_98;
  float parallax_distance_99;
};

#define CENTERCAM    0
#define LEFTCAM      1
#define RIGHTCAM     2

#define DOME_PI  3.141592653589793238
#define DOME_DTOR  0.0174532925199433 
#define DOME_PIOVER2 1.57079632679489661923
#define DOME_PIOVER4 0.785398163397445 
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

    // == in the frameBegin, we count the actual frame number in the chunk
    int separation_var_number = vray->getFrameData().t - params->start_frame;

    // == so we could use the correct separation and parallax:
    float separation_value = 0;
    float parallax_distance_value = 0;
    if (separation_var_number == 0)
    {
        separation_value = params->separation_0;
        parallax_distance_value = params->parallax_distance_0;
    }
    if (separation_var_number == 1)
    {
        separation_value = params->separation_1;
        parallax_distance_value = params->parallax_distance_1;
    }
    if (separation_var_number == 2)
    {
        separation_value = params->separation_2;
        parallax_distance_value = params->parallax_distance_2;
    }
    if (separation_var_number == 3)
    {
        separation_value = params->separation_3;
        parallax_distance_value = params->parallax_distance_3;
    }
    if (separation_var_number == 4)
    {
        separation_value = params->separation_4;
        parallax_distance_value = params->parallax_distance_4;
    }
    if (separation_var_number == 5)
    {
        separation_value = params->separation_5;
        parallax_distance_value = params->parallax_distance_5;
    }
    if (separation_var_number == 6)
    {
        separation_value = params->separation_6;
        parallax_distance_value = params->parallax_distance_6;
    }
    if (separation_var_number == 7)
    {
        separation_value = params->separation_7;
        parallax_distance_value = params->parallax_distance_7;
    }
    if (separation_var_number == 8)
    {
        separation_value = params->separation_8;
        parallax_distance_value = params->parallax_distance_8;
    }
    if (separation_var_number == 9)
    {
        separation_value = params->separation_9;
        parallax_distance_value = params->parallax_distance_9;
    }
    if (separation_var_number == 10)
    {
        separation_value = params->separation_10;
        parallax_distance_value = params->parallax_distance_10;
    }
    if (separation_var_number == 11)
    {
        separation_value = params->separation_11;
        parallax_distance_value = params->parallax_distance_11;
    }
    if (separation_var_number == 12)
    {
        separation_value = params->separation_12;
        parallax_distance_value = params->parallax_distance_12;
    }
    if (separation_var_number == 13)
    {
        separation_value = params->separation_13;
        parallax_distance_value = params->parallax_distance_13;
    }
    if (separation_var_number == 14)
    {
        separation_value = params->separation_14;
        parallax_distance_value = params->parallax_distance_14;
    }
    if (separation_var_number == 15)
    {
        separation_value = params->separation_15;
        parallax_distance_value = params->parallax_distance_15;
    }
    if (separation_var_number == 16)
    {
        separation_value = params->separation_16;
        parallax_distance_value = params->parallax_distance_16;
    }
    if (separation_var_number == 17)
    {
        separation_value = params->separation_17;
        parallax_distance_value = params->parallax_distance_17;
    }
    if (separation_var_number == 18)
    {
        separation_value = params->separation_18;
        parallax_distance_value = params->parallax_distance_18;
    }
    if (separation_var_number == 19)
    {
        separation_value = params->separation_19;
        parallax_distance_value = params->parallax_distance_19;
    }
    if (separation_var_number == 20)
    {
        separation_value = params->separation_20;
        parallax_distance_value = params->parallax_distance_20;
    }
    if (separation_var_number == 21)
    {
        separation_value = params->separation_21;
        parallax_distance_value = params->parallax_distance_21;
    }
    if (separation_var_number == 22)
    {
        separation_value = params->separation_22;
        parallax_distance_value = params->parallax_distance_22;
    }
    if (separation_var_number == 23)
    {
        separation_value = params->separation_23;
        parallax_distance_value = params->parallax_distance_23;
    }
    if (separation_var_number == 24)
    {
        separation_value = params->separation_24;
        parallax_distance_value = params->parallax_distance_24;
    }
    if (separation_var_number == 25)
    {
        separation_value = params->separation_25;
        parallax_distance_value = params->parallax_distance_25;
    }
    if (separation_var_number == 26)
    {
        separation_value = params->separation_26;
        parallax_distance_value = params->parallax_distance_26;
    }
    if (separation_var_number == 27)
    {
        separation_value = params->separation_27;
        parallax_distance_value = params->parallax_distance_27;
    }
    if (separation_var_number == 28)
    {
        separation_value = params->separation_28;
        parallax_distance_value = params->parallax_distance_28;
    }
    if (separation_var_number == 29)
    {
        separation_value = params->separation_29;
        parallax_distance_value = params->parallax_distance_29;
    }
    if (separation_var_number == 30)
    {
        separation_value = params->separation_30;
        parallax_distance_value = params->parallax_distance_30;
    }
    if (separation_var_number == 31)
    {
        separation_value = params->separation_31;
        parallax_distance_value = params->parallax_distance_31;
    }
    if (separation_var_number == 32)
    {
        separation_value = params->separation_32;
        parallax_distance_value = params->parallax_distance_32;
    }
    if (separation_var_number == 33)
    {
        separation_value = params->separation_33;
        parallax_distance_value = params->parallax_distance_33;
    }
    if (separation_var_number == 34)
    {
        separation_value = params->separation_34;
        parallax_distance_value = params->parallax_distance_34;
    }
    if (separation_var_number == 35)
    {
        separation_value = params->separation_35;
        parallax_distance_value = params->parallax_distance_35;
    }
    if (separation_var_number == 36)
    {
        separation_value = params->separation_36;
        parallax_distance_value = params->parallax_distance_36;
    }
    if (separation_var_number == 37)
    {
        separation_value = params->separation_37;
        parallax_distance_value = params->parallax_distance_37;
    }
    if (separation_var_number == 38)
    {
        separation_value = params->separation_38;
        parallax_distance_value = params->parallax_distance_38;
    }
    if (separation_var_number == 39)
    {
        separation_value = params->separation_39;
        parallax_distance_value = params->parallax_distance_39;
    }
    if (separation_var_number == 40)
    {
        separation_value = params->separation_40;
        parallax_distance_value = params->parallax_distance_40;
    }
    if (separation_var_number == 41)
    {
        separation_value = params->separation_41;
        parallax_distance_value = params->parallax_distance_41;
    }
    if (separation_var_number == 42)
    {
        separation_value = params->separation_42;
        parallax_distance_value = params->parallax_distance_42;
    }
    if (separation_var_number == 43)
    {
        separation_value = params->separation_43;
        parallax_distance_value = params->parallax_distance_43;
    }
    if (separation_var_number == 44)
    {
        separation_value = params->separation_44;
        parallax_distance_value = params->parallax_distance_44;
    }
    if (separation_var_number == 45)
    {
        separation_value = params->separation_45;
        parallax_distance_value = params->parallax_distance_45;
    }
    if (separation_var_number == 46)
    {
        separation_value = params->separation_46;
        parallax_distance_value = params->parallax_distance_46;
    }
    if (separation_var_number == 47)
    {
        separation_value = params->separation_47;
        parallax_distance_value = params->parallax_distance_47;
    }
    if (separation_var_number == 48)
    {
        separation_value = params->separation_48;
        parallax_distance_value = params->parallax_distance_48;
    }
    if (separation_var_number == 49)
    {
        separation_value = params->separation_49;
        parallax_distance_value = params->parallax_distance_49;
    }
    if (separation_var_number == 50)
    {
        separation_value = params->separation_50;
        parallax_distance_value = params->parallax_distance_50;
    }
    if (separation_var_number == 51)
    {
        separation_value = params->separation_51;
        parallax_distance_value = params->parallax_distance_51;
    }
    if (separation_var_number == 52)
    {
        separation_value = params->separation_52;
        parallax_distance_value = params->parallax_distance_52;
    }
    if (separation_var_number == 53)
    {
        separation_value = params->separation_53;
        parallax_distance_value = params->parallax_distance_53;
    }
    if (separation_var_number == 54)
    {
        separation_value = params->separation_54;
        parallax_distance_value = params->parallax_distance_54;
    }
    if (separation_var_number == 55)
    {
        separation_value = params->separation_55;
        parallax_distance_value = params->parallax_distance_55;
    }
    if (separation_var_number == 56)
    {
        separation_value = params->separation_56;
        parallax_distance_value = params->parallax_distance_56;
    }
    if (separation_var_number == 57)
    {
        separation_value = params->separation_57;
        parallax_distance_value = params->parallax_distance_57;
    }
    if (separation_var_number == 58)
    {
        separation_value = params->separation_58;
        parallax_distance_value = params->parallax_distance_58;
    }
    if (separation_var_number == 59)
    {
        separation_value = params->separation_59;
        parallax_distance_value = params->parallax_distance_59;
    }
    if (separation_var_number == 60)
    {
        separation_value = params->separation_60;
        parallax_distance_value = params->parallax_distance_60;
    }
    if (separation_var_number == 61)
    {
        separation_value = params->separation_61;
        parallax_distance_value = params->parallax_distance_61;
    }
    if (separation_var_number == 62)
    {
        separation_value = params->separation_62;
        parallax_distance_value = params->parallax_distance_62;
    }
    if (separation_var_number == 63)
    {
        separation_value = params->separation_63;
        parallax_distance_value = params->parallax_distance_63;
    }
    if (separation_var_number == 64)
    {
        separation_value = params->separation_64;
        parallax_distance_value = params->parallax_distance_64;
    }
    if (separation_var_number == 65)
    {
        separation_value = params->separation_65;
        parallax_distance_value = params->parallax_distance_65;
    }
    if (separation_var_number == 66)
    {
        separation_value = params->separation_66;
        parallax_distance_value = params->parallax_distance_66;
    }
    if (separation_var_number == 67)
    {
        separation_value = params->separation_67;
        parallax_distance_value = params->parallax_distance_67;
    }
    if (separation_var_number == 68)
    {
        separation_value = params->separation_68;
        parallax_distance_value = params->parallax_distance_68;
    }
    if (separation_var_number == 69)
    {
        separation_value = params->separation_69;
        parallax_distance_value = params->parallax_distance_69;
    }
    if (separation_var_number == 70)
    {
        separation_value = params->separation_70;
        parallax_distance_value = params->parallax_distance_70;
    }
    if (separation_var_number == 71)
    {
        separation_value = params->separation_71;
        parallax_distance_value = params->parallax_distance_71;
    }
    if (separation_var_number == 72)
    {
        separation_value = params->separation_72;
        parallax_distance_value = params->parallax_distance_72;
    }
    if (separation_var_number == 73)
    {
        separation_value = params->separation_73;
        parallax_distance_value = params->parallax_distance_73;
    }
    if (separation_var_number == 74)
    {
        separation_value = params->separation_74;
        parallax_distance_value = params->parallax_distance_74;
    }
    if (separation_var_number == 75)
    {
        separation_value = params->separation_75;
        parallax_distance_value = params->parallax_distance_75;
    }
    if (separation_var_number == 76)
    {
        separation_value = params->separation_76;
        parallax_distance_value = params->parallax_distance_76;
    }
    if (separation_var_number == 77)
    {
        separation_value = params->separation_77;
        parallax_distance_value = params->parallax_distance_77;
    }
    if (separation_var_number == 78)
    {
        separation_value = params->separation_78;
        parallax_distance_value = params->parallax_distance_78;
    }
    if (separation_var_number == 79)
    {
        separation_value = params->separation_79;
        parallax_distance_value = params->parallax_distance_79;
    }
    if (separation_var_number == 80)
    {
        separation_value = params->separation_80;
        parallax_distance_value = params->parallax_distance_80;
    }
    if (separation_var_number == 81)
    {
        separation_value = params->separation_81;
        parallax_distance_value = params->parallax_distance_81;
    }
    if (separation_var_number == 82)
    {
        separation_value = params->separation_82;
        parallax_distance_value = params->parallax_distance_82;
    }
    if (separation_var_number == 83)
    {
        separation_value = params->separation_83;
        parallax_distance_value = params->parallax_distance_83;
    }
    if (separation_var_number == 84)
    {
        separation_value = params->separation_84;
        parallax_distance_value = params->parallax_distance_84;
    }
    if (separation_var_number == 85)
    {
        separation_value = params->separation_85;
        parallax_distance_value = params->parallax_distance_85;
    }
    if (separation_var_number == 86)
    {
        separation_value = params->separation_86;
        parallax_distance_value = params->parallax_distance_86;
    }
    if (separation_var_number == 87)
    {
        separation_value = params->separation_87;
        parallax_distance_value = params->parallax_distance_87;
    }
    if (separation_var_number == 88)
    {
        separation_value = params->separation_88;
        parallax_distance_value = params->parallax_distance_88;
    }
    if (separation_var_number == 89)
    {
        separation_value = params->separation_89;
        parallax_distance_value = params->parallax_distance_89;
    }
    if (separation_var_number == 90)
    {
        separation_value = params->separation_90;
        parallax_distance_value = params->parallax_distance_90;
    }
    if (separation_var_number == 91)
    {
        separation_value = params->separation_91;
        parallax_distance_value = params->parallax_distance_91;
    }
    if (separation_var_number == 92)
    {
        separation_value = params->separation_92;
        parallax_distance_value = params->parallax_distance_92;
    }
    if (separation_var_number == 93)
    {
        separation_value = params->separation_93;
        parallax_distance_value = params->parallax_distance_93;
    }
    if (separation_var_number == 94)
    {
        separation_value = params->separation_94;
        parallax_distance_value = params->parallax_distance_94;
    }
    if (separation_var_number == 95)
    {
        separation_value = params->separation_95;
        parallax_distance_value = params->parallax_distance_95;
    }
    if (separation_var_number == 96)
    {
        separation_value = params->separation_96;
        parallax_distance_value = params->parallax_distance_96;
    }
    if (separation_var_number == 97)
    {
        separation_value = params->separation_97;
        parallax_distance_value = params->parallax_distance_97;
    }
    if (separation_var_number == 98)
    {
        separation_value = params->separation_98;
        parallax_distance_value = params->parallax_distance_98;
    }
    if (separation_var_number == 99)
    {
        separation_value = params->separation_99;
        parallax_distance_value = params->parallax_distance_99;
    }

    // == here we store the final version of parameters of for this frame, so we could use this later in other metods

    this->separation_final = separation_value;
    this->parallax_distance_final = parallax_distance_value;
	
	const VR::VRayFrameData &_fdata=vray->getFrameData();
	VR::VRayFrameData &fdata=const_cast<VR::VRayFrameData&>(_fdata);

	VR::VRayFrameDataCameraFilmTrans* filmTrans = static_cast<VR::VRayFrameDataCameraFilmTrans*>(fdata.newInterface(EXT_FRAME_DATA_CAMERA_FILM_TRANS));

	if (filmTrans && filmTrans->params.enabled) {
		cameraFilmTrans = filmTrans;
	}
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
  //float parallax_distance = params->parallax_distance;
  float parallax_distance = this->parallax_distance_final; // this is keyable
  //float separation = params->separation;
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
      
      float separation_mult = 1.0f;
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
            if (poles_corr_end > 89.0f * DOME_DTOR) {  // if separation goes through zenith, we use different function to calculate fade, to get straight lines through zenith instead of the "S" shape
                separation_mult_auto = cos(fadePos * DOME_PIOVER2);
            }
            else {
                separation_mult_auto = (cos(fadePos * DOME_PI) + 1.0f) / 2.0f;
            }
          }
          else
            separation_mult_auto = 0.0f;
        }
      }
      // combine both separation values
      separation_mult *= separation_mult_auto;
    
      // camera selection and initial position
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

    addParamInt("start_frame", 0, -1, "Frame Start");
    addParamInt("end_frame", 0, -1, "Frame End");

    // == Also for each frame in the chunk we created a parameter for its Separation, and Paralax Distance
    // == Here are the Separation parameters:
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
    addParamFloat("separation_30", 0.0f, -1, "Separation_30");
    addParamFloat("separation_31", 0.0f, -1, "Separation_31");
    addParamFloat("separation_32", 0.0f, -1, "Separation_32");
    addParamFloat("separation_33", 0.0f, -1, "Separation_33");
    addParamFloat("separation_34", 0.0f, -1, "Separation_34");
    addParamFloat("separation_35", 0.0f, -1, "Separation_35");
    addParamFloat("separation_36", 0.0f, -1, "Separation_36");
    addParamFloat("separation_37", 0.0f, -1, "Separation_37");
    addParamFloat("separation_38", 0.0f, -1, "Separation_38");
    addParamFloat("separation_39", 0.0f, -1, "Separation_39");
    addParamFloat("separation_40", 0.0f, -1, "Separation_40");
    addParamFloat("separation_41", 0.0f, -1, "Separation_41");
    addParamFloat("separation_42", 0.0f, -1, "Separation_42");
    addParamFloat("separation_43", 0.0f, -1, "Separation_43");
    addParamFloat("separation_44", 0.0f, -1, "Separation_44");
    addParamFloat("separation_45", 0.0f, -1, "Separation_45");
    addParamFloat("separation_46", 0.0f, -1, "Separation_46");
    addParamFloat("separation_47", 0.0f, -1, "Separation_47");
    addParamFloat("separation_48", 0.0f, -1, "Separation_48");
    addParamFloat("separation_49", 0.0f, -1, "Separation_49");
    addParamFloat("separation_50", 0.0f, -1, "Separation_50");
    addParamFloat("separation_51", 0.0f, -1, "Separation_51");
    addParamFloat("separation_52", 0.0f, -1, "Separation_52");
    addParamFloat("separation_53", 0.0f, -1, "Separation_53");
    addParamFloat("separation_54", 0.0f, -1, "Separation_54");
    addParamFloat("separation_55", 0.0f, -1, "Separation_55");
    addParamFloat("separation_56", 0.0f, -1, "Separation_56");
    addParamFloat("separation_57", 0.0f, -1, "Separation_57");
    addParamFloat("separation_58", 0.0f, -1, "Separation_58");
    addParamFloat("separation_59", 0.0f, -1, "Separation_59");
    addParamFloat("separation_60", 0.0f, -1, "Separation_60");
    addParamFloat("separation_61", 0.0f, -1, "Separation_61");
    addParamFloat("separation_62", 0.0f, -1, "Separation_62");
    addParamFloat("separation_63", 0.0f, -1, "Separation_63");
    addParamFloat("separation_64", 0.0f, -1, "Separation_64");
    addParamFloat("separation_65", 0.0f, -1, "Separation_65");
    addParamFloat("separation_66", 0.0f, -1, "Separation_66");
    addParamFloat("separation_67", 0.0f, -1, "Separation_67");
    addParamFloat("separation_68", 0.0f, -1, "Separation_68");
    addParamFloat("separation_69", 0.0f, -1, "Separation_69");
    addParamFloat("separation_70", 0.0f, -1, "Separation_70");
    addParamFloat("separation_71", 0.0f, -1, "Separation_71");
    addParamFloat("separation_72", 0.0f, -1, "Separation_72");
    addParamFloat("separation_73", 0.0f, -1, "Separation_73");
    addParamFloat("separation_74", 0.0f, -1, "Separation_74");
    addParamFloat("separation_75", 0.0f, -1, "Separation_75");
    addParamFloat("separation_76", 0.0f, -1, "Separation_76");
    addParamFloat("separation_77", 0.0f, -1, "Separation_77");
    addParamFloat("separation_78", 0.0f, -1, "Separation_78");
    addParamFloat("separation_79", 0.0f, -1, "Separation_79");
    addParamFloat("separation_80", 0.0f, -1, "Separation_80");
    addParamFloat("separation_81", 0.0f, -1, "Separation_81");
    addParamFloat("separation_82", 0.0f, -1, "Separation_82");
    addParamFloat("separation_83", 0.0f, -1, "Separation_83");
    addParamFloat("separation_84", 0.0f, -1, "Separation_84");
    addParamFloat("separation_85", 0.0f, -1, "Separation_85");
    addParamFloat("separation_86", 0.0f, -1, "Separation_86");
    addParamFloat("separation_87", 0.0f, -1, "Separation_87");
    addParamFloat("separation_88", 0.0f, -1, "Separation_88");
    addParamFloat("separation_89", 0.0f, -1, "Separation_89");
    addParamFloat("separation_90", 0.0f, -1, "Separation_90");
    addParamFloat("separation_91", 0.0f, -1, "Separation_91");
    addParamFloat("separation_92", 0.0f, -1, "Separation_92");
    addParamFloat("separation_93", 0.0f, -1, "Separation_93");
    addParamFloat("separation_94", 0.0f, -1, "Separation_94");
    addParamFloat("separation_95", 0.0f, -1, "Separation_95");
    addParamFloat("separation_96", 0.0f, -1, "Separation_96");
    addParamFloat("separation_97", 0.0f, -1, "Separation_97");
    addParamFloat("separation_98", 0.0f, -1, "Separation_98");
    addParamFloat("separation_99", 0.0f, -1, "Separation_99");

    // here are the Parallax Distance Parameters
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
    addParamFloat("parallax_distance_30", 0.0f, -1, "parallax_distance_30");
    addParamFloat("parallax_distance_31", 0.0f, -1, "parallax_distance_31");
    addParamFloat("parallax_distance_32", 0.0f, -1, "parallax_distance_32");
    addParamFloat("parallax_distance_33", 0.0f, -1, "parallax_distance_33");
    addParamFloat("parallax_distance_34", 0.0f, -1, "parallax_distance_34");
    addParamFloat("parallax_distance_35", 0.0f, -1, "parallax_distance_35");
    addParamFloat("parallax_distance_36", 0.0f, -1, "parallax_distance_36");
    addParamFloat("parallax_distance_37", 0.0f, -1, "parallax_distance_37");
    addParamFloat("parallax_distance_38", 0.0f, -1, "parallax_distance_38");
    addParamFloat("parallax_distance_39", 0.0f, -1, "parallax_distance_39");
    addParamFloat("parallax_distance_40", 0.0f, -1, "parallax_distance_40");
    addParamFloat("parallax_distance_41", 0.0f, -1, "parallax_distance_41");
    addParamFloat("parallax_distance_42", 0.0f, -1, "parallax_distance_42");
    addParamFloat("parallax_distance_43", 0.0f, -1, "parallax_distance_43");
    addParamFloat("parallax_distance_44", 0.0f, -1, "parallax_distance_44");
    addParamFloat("parallax_distance_45", 0.0f, -1, "parallax_distance_45");
    addParamFloat("parallax_distance_46", 0.0f, -1, "parallax_distance_46");
    addParamFloat("parallax_distance_47", 0.0f, -1, "parallax_distance_47");
    addParamFloat("parallax_distance_48", 0.0f, -1, "parallax_distance_48");
    addParamFloat("parallax_distance_49", 0.0f, -1, "parallax_distance_49");
    addParamFloat("parallax_distance_50", 0.0f, -1, "parallax_distance_50");
    addParamFloat("parallax_distance_51", 0.0f, -1, "parallax_distance_51");
    addParamFloat("parallax_distance_52", 0.0f, -1, "parallax_distance_52");
    addParamFloat("parallax_distance_53", 0.0f, -1, "parallax_distance_53");
    addParamFloat("parallax_distance_54", 0.0f, -1, "parallax_distance_54");
    addParamFloat("parallax_distance_55", 0.0f, -1, "parallax_distance_55");
    addParamFloat("parallax_distance_56", 0.0f, -1, "parallax_distance_56");
    addParamFloat("parallax_distance_57", 0.0f, -1, "parallax_distance_57");
    addParamFloat("parallax_distance_58", 0.0f, -1, "parallax_distance_58");
    addParamFloat("parallax_distance_59", 0.0f, -1, "parallax_distance_59");
    addParamFloat("parallax_distance_60", 0.0f, -1, "parallax_distance_60");
    addParamFloat("parallax_distance_61", 0.0f, -1, "parallax_distance_61");
    addParamFloat("parallax_distance_62", 0.0f, -1, "parallax_distance_62");
    addParamFloat("parallax_distance_63", 0.0f, -1, "parallax_distance_63");
    addParamFloat("parallax_distance_64", 0.0f, -1, "parallax_distance_64");
    addParamFloat("parallax_distance_65", 0.0f, -1, "parallax_distance_65");
    addParamFloat("parallax_distance_66", 0.0f, -1, "parallax_distance_66");
    addParamFloat("parallax_distance_67", 0.0f, -1, "parallax_distance_67");
    addParamFloat("parallax_distance_68", 0.0f, -1, "parallax_distance_68");
    addParamFloat("parallax_distance_69", 0.0f, -1, "parallax_distance_69");
    addParamFloat("parallax_distance_70", 0.0f, -1, "parallax_distance_70");
    addParamFloat("parallax_distance_71", 0.0f, -1, "parallax_distance_71");
    addParamFloat("parallax_distance_72", 0.0f, -1, "parallax_distance_72");
    addParamFloat("parallax_distance_73", 0.0f, -1, "parallax_distance_73");
    addParamFloat("parallax_distance_74", 0.0f, -1, "parallax_distance_74");
    addParamFloat("parallax_distance_75", 0.0f, -1, "parallax_distance_75");
    addParamFloat("parallax_distance_76", 0.0f, -1, "parallax_distance_76");
    addParamFloat("parallax_distance_77", 0.0f, -1, "parallax_distance_77");
    addParamFloat("parallax_distance_78", 0.0f, -1, "parallax_distance_78");
    addParamFloat("parallax_distance_79", 0.0f, -1, "parallax_distance_79");
    addParamFloat("parallax_distance_80", 0.0f, -1, "parallax_distance_80");
    addParamFloat("parallax_distance_81", 0.0f, -1, "parallax_distance_81");
    addParamFloat("parallax_distance_82", 0.0f, -1, "parallax_distance_82");
    addParamFloat("parallax_distance_83", 0.0f, -1, "parallax_distance_83");
    addParamFloat("parallax_distance_84", 0.0f, -1, "parallax_distance_84");
    addParamFloat("parallax_distance_85", 0.0f, -1, "parallax_distance_85");
    addParamFloat("parallax_distance_86", 0.0f, -1, "parallax_distance_86");
    addParamFloat("parallax_distance_87", 0.0f, -1, "parallax_distance_87");
    addParamFloat("parallax_distance_88", 0.0f, -1, "parallax_distance_88");
    addParamFloat("parallax_distance_89", 0.0f, -1, "parallax_distance_89");
    addParamFloat("parallax_distance_90", 0.0f, -1, "parallax_distance_90");
    addParamFloat("parallax_distance_91", 0.0f, -1, "parallax_distance_91");
    addParamFloat("parallax_distance_92", 0.0f, -1, "parallax_distance_92");
    addParamFloat("parallax_distance_93", 0.0f, -1, "parallax_distance_93");
    addParamFloat("parallax_distance_94", 0.0f, -1, "parallax_distance_94");
    addParamFloat("parallax_distance_95", 0.0f, -1, "parallax_distance_95");
    addParamFloat("parallax_distance_96", 0.0f, -1, "parallax_distance_96");
    addParamFloat("parallax_distance_97", 0.0f, -1, "parallax_distance_97");
    addParamFloat("parallax_distance_98", 0.0f, -1, "parallax_distance_98");
    addParamFloat("parallax_distance_99", 0.0f, -1, "parallax_distance_99");
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
    // paramList->setParamCache("separation_json", &params.separation_json);
    paramList->setParamCache("separation_0", &params.separation_0);
    paramList->setParamCache("separation_1", &params.separation_1);
    paramList->setParamCache("separation_2", &params.separation_2);
    paramList->setParamCache("separation_3", &params.separation_3);
    paramList->setParamCache("separation_4", &params.separation_4);
    paramList->setParamCache("separation_5", &params.separation_5);
    paramList->setParamCache("separation_6", &params.separation_6);
    paramList->setParamCache("separation_7", &params.separation_7);
    paramList->setParamCache("separation_8", &params.separation_8);
    paramList->setParamCache("separation_9", &params.separation_9);
    paramList->setParamCache("separation_10", &params.separation_10);
    paramList->setParamCache("separation_11", &params.separation_11);
    paramList->setParamCache("separation_12", &params.separation_12);
    paramList->setParamCache("separation_13", &params.separation_13);
    paramList->setParamCache("separation_14", &params.separation_14);
    paramList->setParamCache("separation_15", &params.separation_15);
    paramList->setParamCache("separation_16", &params.separation_16);
    paramList->setParamCache("separation_17", &params.separation_17);
    paramList->setParamCache("separation_18", &params.separation_18);
    paramList->setParamCache("separation_19", &params.separation_19);
    paramList->setParamCache("separation_20", &params.separation_20);
    paramList->setParamCache("separation_21", &params.separation_21);
    paramList->setParamCache("separation_22", &params.separation_22);
    paramList->setParamCache("separation_23", &params.separation_23);
    paramList->setParamCache("separation_24", &params.separation_24);
    paramList->setParamCache("separation_25", &params.separation_25);
    paramList->setParamCache("separation_26", &params.separation_26);
    paramList->setParamCache("separation_27", &params.separation_27);
    paramList->setParamCache("separation_28", &params.separation_28);
    paramList->setParamCache("separation_29", &params.separation_29);
    paramList->setParamCache("separation_30", &params.separation_30);
    paramList->setParamCache("separation_31", &params.separation_31);
    paramList->setParamCache("separation_32", &params.separation_32);
    paramList->setParamCache("separation_33", &params.separation_33);
    paramList->setParamCache("separation_34", &params.separation_34);
    paramList->setParamCache("separation_35", &params.separation_35);
    paramList->setParamCache("separation_36", &params.separation_36);
    paramList->setParamCache("separation_37", &params.separation_37);
    paramList->setParamCache("separation_38", &params.separation_38);
    paramList->setParamCache("separation_39", &params.separation_39);
    paramList->setParamCache("separation_40", &params.separation_40);
    paramList->setParamCache("separation_41", &params.separation_41);
    paramList->setParamCache("separation_42", &params.separation_42);
    paramList->setParamCache("separation_43", &params.separation_43);
    paramList->setParamCache("separation_44", &params.separation_44);
    paramList->setParamCache("separation_45", &params.separation_45);
    paramList->setParamCache("separation_46", &params.separation_46);
    paramList->setParamCache("separation_47", &params.separation_47);
    paramList->setParamCache("separation_48", &params.separation_48);
    paramList->setParamCache("separation_49", &params.separation_49);
    paramList->setParamCache("separation_50", &params.separation_50);
    paramList->setParamCache("separation_51", &params.separation_51);
    paramList->setParamCache("separation_52", &params.separation_52);
    paramList->setParamCache("separation_53", &params.separation_53);
    paramList->setParamCache("separation_54", &params.separation_54);
    paramList->setParamCache("separation_55", &params.separation_55);
    paramList->setParamCache("separation_56", &params.separation_56);
    paramList->setParamCache("separation_57", &params.separation_57);
    paramList->setParamCache("separation_58", &params.separation_58);
    paramList->setParamCache("separation_59", &params.separation_59);
    paramList->setParamCache("separation_60", &params.separation_60);
    paramList->setParamCache("separation_61", &params.separation_61);
    paramList->setParamCache("separation_62", &params.separation_62);
    paramList->setParamCache("separation_63", &params.separation_63);
    paramList->setParamCache("separation_64", &params.separation_64);
    paramList->setParamCache("separation_65", &params.separation_65);
    paramList->setParamCache("separation_66", &params.separation_66);
    paramList->setParamCache("separation_67", &params.separation_67);
    paramList->setParamCache("separation_68", &params.separation_68);
    paramList->setParamCache("separation_69", &params.separation_69);
    paramList->setParamCache("separation_70", &params.separation_70);
    paramList->setParamCache("separation_71", &params.separation_71);
    paramList->setParamCache("separation_72", &params.separation_72);
    paramList->setParamCache("separation_73", &params.separation_73);
    paramList->setParamCache("separation_74", &params.separation_74);
    paramList->setParamCache("separation_75", &params.separation_75);
    paramList->setParamCache("separation_76", &params.separation_76);
    paramList->setParamCache("separation_77", &params.separation_77);
    paramList->setParamCache("separation_78", &params.separation_78);
    paramList->setParamCache("separation_79", &params.separation_79);
    paramList->setParamCache("separation_80", &params.separation_80);
    paramList->setParamCache("separation_81", &params.separation_81);
    paramList->setParamCache("separation_82", &params.separation_82);
    paramList->setParamCache("separation_83", &params.separation_83);
    paramList->setParamCache("separation_84", &params.separation_84);
    paramList->setParamCache("separation_85", &params.separation_85);
    paramList->setParamCache("separation_86", &params.separation_86);
    paramList->setParamCache("separation_87", &params.separation_87);
    paramList->setParamCache("separation_88", &params.separation_88);
    paramList->setParamCache("separation_89", &params.separation_89);
    paramList->setParamCache("separation_90", &params.separation_90);
    paramList->setParamCache("separation_91", &params.separation_91);
    paramList->setParamCache("separation_92", &params.separation_92);
    paramList->setParamCache("separation_93", &params.separation_93);
    paramList->setParamCache("separation_94", &params.separation_94);
    paramList->setParamCache("separation_95", &params.separation_95);
    paramList->setParamCache("separation_96", &params.separation_96);
    paramList->setParamCache("separation_97", &params.separation_97);
    paramList->setParamCache("separation_98", &params.separation_98);
    paramList->setParamCache("separation_99", &params.separation_99);

    paramList->setParamCache("parallax_distance_0", &params.parallax_distance_0);
    paramList->setParamCache("parallax_distance_1", &params.parallax_distance_1);
    paramList->setParamCache("parallax_distance_2", &params.parallax_distance_2);
    paramList->setParamCache("parallax_distance_3", &params.parallax_distance_3);
    paramList->setParamCache("parallax_distance_4", &params.parallax_distance_4);
    paramList->setParamCache("parallax_distance_5", &params.parallax_distance_5);
    paramList->setParamCache("parallax_distance_6", &params.parallax_distance_6);
    paramList->setParamCache("parallax_distance_7", &params.parallax_distance_7);
    paramList->setParamCache("parallax_distance_8", &params.parallax_distance_8);
    paramList->setParamCache("parallax_distance_9", &params.parallax_distance_9);
    paramList->setParamCache("parallax_distance_10", &params.parallax_distance_10);
    paramList->setParamCache("parallax_distance_11", &params.parallax_distance_11);
    paramList->setParamCache("parallax_distance_12", &params.parallax_distance_12);
    paramList->setParamCache("parallax_distance_13", &params.parallax_distance_13);
    paramList->setParamCache("parallax_distance_14", &params.parallax_distance_14);
    paramList->setParamCache("parallax_distance_15", &params.parallax_distance_15);
    paramList->setParamCache("parallax_distance_16", &params.parallax_distance_16);
    paramList->setParamCache("parallax_distance_17", &params.parallax_distance_17);
    paramList->setParamCache("parallax_distance_18", &params.parallax_distance_18);
    paramList->setParamCache("parallax_distance_19", &params.parallax_distance_19);
    paramList->setParamCache("parallax_distance_20", &params.parallax_distance_20);
    paramList->setParamCache("parallax_distance_21", &params.parallax_distance_21);
    paramList->setParamCache("parallax_distance_22", &params.parallax_distance_22);
    paramList->setParamCache("parallax_distance_23", &params.parallax_distance_23);
    paramList->setParamCache("parallax_distance_24", &params.parallax_distance_24);
    paramList->setParamCache("parallax_distance_25", &params.parallax_distance_25);
    paramList->setParamCache("parallax_distance_26", &params.parallax_distance_26);
    paramList->setParamCache("parallax_distance_27", &params.parallax_distance_27);
    paramList->setParamCache("parallax_distance_28", &params.parallax_distance_28);
    paramList->setParamCache("parallax_distance_29", &params.parallax_distance_29);
    paramList->setParamCache("parallax_distance_30", &params.parallax_distance_30);
    paramList->setParamCache("parallax_distance_31", &params.parallax_distance_31);
    paramList->setParamCache("parallax_distance_32", &params.parallax_distance_32);
    paramList->setParamCache("parallax_distance_33", &params.parallax_distance_33);
    paramList->setParamCache("parallax_distance_34", &params.parallax_distance_34);
    paramList->setParamCache("parallax_distance_35", &params.parallax_distance_35);
    paramList->setParamCache("parallax_distance_36", &params.parallax_distance_36);
    paramList->setParamCache("parallax_distance_37", &params.parallax_distance_37);
    paramList->setParamCache("parallax_distance_38", &params.parallax_distance_38);
    paramList->setParamCache("parallax_distance_39", &params.parallax_distance_39);
    paramList->setParamCache("parallax_distance_40", &params.parallax_distance_40);
    paramList->setParamCache("parallax_distance_41", &params.parallax_distance_41);
    paramList->setParamCache("parallax_distance_42", &params.parallax_distance_42);
    paramList->setParamCache("parallax_distance_43", &params.parallax_distance_43);
    paramList->setParamCache("parallax_distance_44", &params.parallax_distance_44);
    paramList->setParamCache("parallax_distance_45", &params.parallax_distance_45);
    paramList->setParamCache("parallax_distance_46", &params.parallax_distance_46);
    paramList->setParamCache("parallax_distance_47", &params.parallax_distance_47);
    paramList->setParamCache("parallax_distance_48", &params.parallax_distance_48);
    paramList->setParamCache("parallax_distance_49", &params.parallax_distance_49);
    paramList->setParamCache("parallax_distance_50", &params.parallax_distance_50);
    paramList->setParamCache("parallax_distance_51", &params.parallax_distance_51);
    paramList->setParamCache("parallax_distance_52", &params.parallax_distance_52);
    paramList->setParamCache("parallax_distance_53", &params.parallax_distance_53);
    paramList->setParamCache("parallax_distance_54", &params.parallax_distance_54);
    paramList->setParamCache("parallax_distance_55", &params.parallax_distance_55);
    paramList->setParamCache("parallax_distance_56", &params.parallax_distance_56);
    paramList->setParamCache("parallax_distance_57", &params.parallax_distance_57);
    paramList->setParamCache("parallax_distance_58", &params.parallax_distance_58);
    paramList->setParamCache("parallax_distance_59", &params.parallax_distance_59);
    paramList->setParamCache("parallax_distance_60", &params.parallax_distance_60);
    paramList->setParamCache("parallax_distance_61", &params.parallax_distance_61);
    paramList->setParamCache("parallax_distance_62", &params.parallax_distance_62);
    paramList->setParamCache("parallax_distance_63", &params.parallax_distance_63);
    paramList->setParamCache("parallax_distance_64", &params.parallax_distance_64);
    paramList->setParamCache("parallax_distance_65", &params.parallax_distance_65);
    paramList->setParamCache("parallax_distance_66", &params.parallax_distance_66);
    paramList->setParamCache("parallax_distance_67", &params.parallax_distance_67);
    paramList->setParamCache("parallax_distance_68", &params.parallax_distance_68);
    paramList->setParamCache("parallax_distance_69", &params.parallax_distance_69);
    paramList->setParamCache("parallax_distance_70", &params.parallax_distance_70);
    paramList->setParamCache("parallax_distance_71", &params.parallax_distance_71);
    paramList->setParamCache("parallax_distance_72", &params.parallax_distance_72);
    paramList->setParamCache("parallax_distance_73", &params.parallax_distance_73);
    paramList->setParamCache("parallax_distance_74", &params.parallax_distance_74);
    paramList->setParamCache("parallax_distance_75", &params.parallax_distance_75);
    paramList->setParamCache("parallax_distance_76", &params.parallax_distance_76);
    paramList->setParamCache("parallax_distance_77", &params.parallax_distance_77);
    paramList->setParamCache("parallax_distance_78", &params.parallax_distance_78);
    paramList->setParamCache("parallax_distance_79", &params.parallax_distance_79);
    paramList->setParamCache("parallax_distance_80", &params.parallax_distance_80);
    paramList->setParamCache("parallax_distance_81", &params.parallax_distance_81);
    paramList->setParamCache("parallax_distance_82", &params.parallax_distance_82);
    paramList->setParamCache("parallax_distance_83", &params.parallax_distance_83);
    paramList->setParamCache("parallax_distance_84", &params.parallax_distance_84);
    paramList->setParamCache("parallax_distance_85", &params.parallax_distance_85);
    paramList->setParamCache("parallax_distance_86", &params.parallax_distance_86);
    paramList->setParamCache("parallax_distance_87", &params.parallax_distance_87);
    paramList->setParamCache("parallax_distance_88", &params.parallax_distance_88);
    paramList->setParamCache("parallax_distance_89", &params.parallax_distance_89);
    paramList->setParamCache("parallax_distance_90", &params.parallax_distance_90);
    paramList->setParamCache("parallax_distance_91", &params.parallax_distance_91);
    paramList->setParamCache("parallax_distance_92", &params.parallax_distance_92);
    paramList->setParamCache("parallax_distance_93", &params.parallax_distance_93);
    paramList->setParamCache("parallax_distance_94", &params.parallax_distance_94);
    paramList->setParamCache("parallax_distance_95", &params.parallax_distance_95);
    paramList->setParamCache("parallax_distance_96", &params.parallax_distance_96);
    paramList->setParamCache("parallax_distance_97", &params.parallax_distance_97);
    paramList->setParamCache("parallax_distance_98", &params.parallax_distance_98);
    paramList->setParamCache("parallax_distance_99", &params.parallax_distance_99);
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
