#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/Timeline.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Timer.h"
#include "Kinect.h"

using namespace ci;
using namespace ci::app;
using namespace gl;
using namespace std;

typedef ci::Vec3f USER_HEAD[2];

namespace kinectDefaults
{
	const int  FACES_MAX					    = 2;
	const NUI_IMAGE_RESOLUTION COLOR_RESOLUTION = MsKinect::ImageResolution::NUI_IMAGE_RESOLUTION_640x480;//MsKinect::ImageResolution::NUI_IMAGE_RESOLUTION_1280x960
	const NUI_IMAGE_RESOLUTION DEPTH_RESOLUTION = MsKinect::ImageResolution::NUI_IMAGE_RESOLUTION_640x480;//MsKinect::ImageResolution::NUI_IMAGE_RESOLUTION_1280x960

	const float   MIN_DEPTH						= 0.8f;
	const float	  MAX_DEPTH						= 3.0f;
}

class KinectAdapter 
{
	public:
		void Setup();	
		void Shutdown();	

		void update();
		void draw();

		static KinectAdapter* Instance() {
			return &KinectAdapterState;
		}

		ci::gl::TextureRef getColorTexRef();
		ci::gl::TextureRef getDepthTexRef();

		bool				isFaceDetected(int i);
		int					getFacesDetectedNum();

		Rectf				getColorResolutionRectf();
		int					getSkeletsInFrame();

		float				getMinDepth(){ return kinectDefaults::MIN_DEPTH;};
		float				getMaxDepth(){ return kinectDefaults::MAX_DEPTH;};
		int					maxFaces(){ return kinectDefaults::FACES_MAX;};

		MsKinect::Face		getFace(int i);

	protected:
		KinectAdapter() { }

	private:

		static KinectAdapter		KinectAdapterState;

		MsKinect::DeviceRef			mDevice;
		MsKinect::DeviceOptions     deviceOptions;
		MsKinect::Frame				mFrame;	

		ci::gl::TextureRef			mTextureColor;
		ci::gl::TextureRef			mTextureDepth;

		int							SKELETS_IN_FRAME;
		// Face	
		MsKinect::Face				mFace[kinectDefaults::FACES_MAX];
		MsKinect::FaceTrackerRef	mFaceTracker[kinectDefaults::FACES_MAX];
		USER_HEAD					userheadPoints[kinectDefaults::FACES_MAX];

		void						kinectConnect();
		void						updateSkeletonData();	

		bool						_isFaceDetected[kinectDefaults::FACES_MAX];
		int							_facesDetectedNum;
};