#include "KinectAdapter.h"

using namespace kinectDefaults;

KinectAdapter KinectAdapter::KinectAdapterState;

void KinectAdapter::Setup()
{
	deviceOptions.enableColor(true);
	deviceOptions.enableDepth(true);
	deviceOptions.setDepthResolution(DEPTH_RESOLUTION);
	deviceOptions.setColorResolution(COLOR_RESOLUTION);

	mDevice = MsKinect::Device::create();

	mDevice->connectEventHandler( [ & ]( MsKinect::Frame frame )
	{
		mFrame = frame;

		for (int i = 0; i < FACES_MAX; i++)
		{
			if ( !mFaceTracker[i] )  continue;
			
			if (SKELETS_IN_FRAME > 1) // IF SKELETONES IN FRAME HINT BY PASSING HEAD POINTS
			{
				mFaceTracker[i]->update( mFrame.getColorSurface(), mFrame.getDepthChannel(), userheadPoints[i]);
			}
			else // if not skeleton hints update only one tracker
			{
				mFaceTracker[0]->update( mFrame.getColorSurface(), mFrame.getDepthChannel());
			}
		}

		if ( frame.getColorSurface() ) 
		{
			mTextureColor = gl::Texture::create( frame.getColorSurface() );
		} 
		else if ( frame.getInfraredChannel() ) 
		{
			mTextureColor = gl::Texture::create( frame.getInfraredChannel() );
		}
		if ( frame.getDepthChannel() ) 
		{
			mTextureDepth = gl::Texture::create( frame.getDepthChannel() );
		}

	} );
	
	kinectConnect();

	// ------------------------------------   INIT KINECT  FACES ---------------------------------------------

	for (int i = 0; i < FACES_MAX; i++)
	{
		// Kinect Face
		mFaceTracker[i] = MsKinect::FaceTracker::create();	
		mFaceTracker[i]->enableCalcMesh( false );
		mFaceTracker[i]->enableCalcMesh2d();
	}
		
	mFaceTracker[0]->connectEventHander( [ & ]( MsKinect::Face face )
	{
		mFace[0] = face;
	} );

	
	mFaceTracker[1]->connectEventHander( [ & ]( MsKinect::Face face )
	{
		mFace[1] = face;
	} );

	
	try
	{
		for (int i = 0; i < FACES_MAX; i++)
		{	
			mFaceTracker[i]->start(deviceOptions);
		}
		
	}
	catch(...)
	{
	}
}

void KinectAdapter::kinectConnect()
{
	try {
		mDevice->start(deviceOptions);
	} catch ( MsKinect::Device::ExcDeviceCreate ex ) {
		console() << ex.what() << endl;
	} catch ( MsKinect::Device::ExcDeviceInit ex ) {
		console() << ex.what() << endl;
	} catch ( MsKinect::Device::ExcDeviceInvalid ex ) {
		console() << ex.what() << endl;
	//} catch ( MsKinect::Device::ExcGetCoordinateMapper ex ) {
	//	console() << ex.what() << endl;
	} catch ( MsKinect::Device::ExcOpenStreamColor ex ) {
		console() << ex.what() << endl;
	} catch ( MsKinect::Device::ExcOpenStreamDepth ex ) {
		console() << ex.what() << endl;
	//} catch ( MsKinect::Device::ExcStreamStart ex ) {
	//	console() << ex.what() << endl;
	//} catch ( MsKinect::Device::ExcUserTrackingEnable ex ) {
	//	console() << ex.what() << endl;
	}
}


void KinectAdapter::update() 
{
	updateSkeletonData();
	
	_facesDetectedNum = 0;

	for (int i = 0; i < FACES_MAX; i++)
	{
		_isFaceDetected[i] = false;
	}

	for (int i = 0; i < FACES_MAX; i++)
	{		
		if ( mFace[i].getMesh2d().getNumVertices() > 0 && mFace[i].getTranslationTransform().z < 2.0f)
		{
			_isFaceDetected[i] = true;
			_facesDetectedNum++;
		}
		
	}
}

void KinectAdapter::updateSkeletonData()
{
	_NUI_SKELETON_POSITION_INDEX  headJoint = NUI_SKELETON_POSITION_HEAD;
	_NUI_SKELETON_POSITION_INDEX  neckJoint = NUI_SKELETON_POSITION_HEAD;

	SKELETS_IN_FRAME = 0;
	
	if ( mFrame.getDepthChannel() ) 
	{
		for( size_t i = 0, ilen= mFrame.getSkeletons().size(); i < ilen; i++) 
        {
			if(mFrame.getSkeletons().at(i).find(headJoint) != mFrame.getSkeletons().at(i).end())
            {
				const MsKinect::Bone& headBone = mFrame.getSkeletons().at(i).find(headJoint)->second;
				auto  startV3 = mFrame.getSkeletons().at(i).at( headBone.getStartJoint()).getPosition();
				auto  endtV3 = mFrame.getSkeletons().at(i).at( headBone.getEndJoint()).getPosition();		

				userheadPoints[SKELETS_IN_FRAME][0] = startV3;
				userheadPoints[SKELETS_IN_FRAME][1] = endtV3;

				SKELETS_IN_FRAME++;
			}
		}				
	}
}

void KinectAdapter::Shutdown()
{	
	mDevice->stop();

	for (int i = 0; i < 2; i++)		
		mFaceTracker[i]->stop();	
}

ci::gl::TextureRef KinectAdapter::getColorTexRef()
{
	return mTextureColor;
}

ci::gl::TextureRef KinectAdapter::getDepthTexRef()
{
	return mTextureDepth;
}

Rectf KinectAdapter::getColorResolutionRectf()
{
	if (MsKinect::ImageResolution::NUI_IMAGE_RESOLUTION_640x480 == COLOR_RESOLUTION)
		return Rectf(0.0f, 0.0f, 640.0f,480.0f);

	if (MsKinect::ImageResolution::NUI_IMAGE_RESOLUTION_1280x960== COLOR_RESOLUTION)
		return Rectf(0.0f, 0.0f, 1280.0f,960.0f);
}	

int KinectAdapter::getSkeletsInFrame()
{
	return SKELETS_IN_FRAME;
}

bool KinectAdapter::isFaceDetected(int i) 
{
	return _isFaceDetected[i];
}

int KinectAdapter::getFacesDetectedNum() 
{
	return _facesDetectedNum;
}

MsKinect::Face KinectAdapter::getFace(int i) 
{
	return mFace[i];
}