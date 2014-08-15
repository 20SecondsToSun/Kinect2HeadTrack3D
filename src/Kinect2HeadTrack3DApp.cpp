#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "LocationEngine.h"
#include "MainGame.h"
#include "KinectAdapter.h"
#include "HeadHelper.h"

#define DEBUGMODE

using namespace ci;
using namespace ci::app;
using namespace std;

class Kinect2HeadTrack3DApp : public AppNative {
  public:
	void setup();	
	void keyDown( ci::app::KeyEvent event );
	void update();
	void draw();
	void shutdown();

private:
	LocationEngine			 game;
};

void Kinect2HeadTrack3DApp::setup()
{	
	setWindowSize(640*2, 480*2);

	HeadHelper::loadHeads();

	MainGame::Instance()->Setup();
	KinectAdapter::Instance()->Setup();

	game.Init("init",getWindow());
	game.ChangeState(MainGame::Instance());	
}

void Kinect2HeadTrack3DApp::update()
{
	game.Update();
	KinectAdapter::Instance()->update();
}

void Kinect2HeadTrack3DApp::draw()
{
	game.Draw();
}

void Kinect2HeadTrack3DApp::keyDown( KeyEvent event )
{
	switch ( event.getCode() ) {
	case KeyEvent::KEY_f:
		setFullScreen( !isFullScreen() );
		break;
	case KeyEvent::KEY_q:
		quit();
		break;
	}
}
void Kinect2HeadTrack3DApp::shutdown(  )
{
	KinectAdapter::Instance()->Shutdown();
}

CINDER_APP_NATIVE( Kinect2HeadTrack3DApp, RendererGl )