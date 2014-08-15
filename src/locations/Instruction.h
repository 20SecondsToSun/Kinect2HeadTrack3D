#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/Timeline.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Timer.h"

#include "Location.h"

using namespace ci;
using namespace ci::app;
using namespace gl;
using namespace std;

class Instruction : public Location
{

public:
	void Setup();
	void Init( LocationEngine* game);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(LocationEngine* game);
	void Update(LocationEngine* game);
	void Draw(LocationEngine* game);

	static Instruction* Instance() {
		return &InstructionState;
	}

protected:
	Instruction() { }

private:
	void					 MouseEvents( LocationEngine* game );

	LocationEngine*			_game;
	static Instruction		InstructionState;
	int						state, currentSec;
};