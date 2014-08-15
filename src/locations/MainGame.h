#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/Timeline.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Timer.h"
#include "Location.h"

#include "Head3DScreen.h"
#include "ModeBaseKinect.h"

using namespace ci;
using namespace ci::app;
using namespace gl;
using namespace std;

class MainGame : public Location
{

public:
	void Setup();
	void Init( LocationEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void Shutdown();

	void HandleEvents(LocationEngine* game);
	void Update(LocationEngine* game);
	void Draw(LocationEngine* game);

	static MainGame* Instance() {
		return &MainGameState;
	}

protected:
	MainGame() { }

private:
	void					 MouseEvents( LocationEngine* game );

	LocationEngine*			_game;
	static MainGame			 MainGameState;

	ModeBaseKinect*			 gameMode;	
};