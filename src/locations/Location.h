#ifndef LOCATION_H
#define LOCATION_H

#include "LocationEngine.h"
#include "cinder/app/AppNative.h"


class Location
{
public:
	virtual void Init(LocationEngine* game) = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(LocationEngine* game) = 0;
	virtual void MouseEvents( LocationEngine* game ) = 0;

	virtual void Update(LocationEngine* game) = 0;
	virtual void Draw(LocationEngine* game) = 0;

	void ChangeState(LocationEngine* game, Location* state) {
		game->ChangeState(state);
	}

protected:
	Location() { }
};

#endif