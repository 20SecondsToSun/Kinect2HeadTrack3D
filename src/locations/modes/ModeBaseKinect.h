#pragma once

#include "KinectAdapter.h"
#include "cinder/app/AppNative.h"
#include "cinder/Timeline.h"
#include "cinder/gl/Texture.h"

class ModeBaseKinect
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void init() = 0;
protected:
	static KinectAdapter*	kinect;

};