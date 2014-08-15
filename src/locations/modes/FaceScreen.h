#pragma once
#include "ModeBaseKinect.h"


using namespace ci;
using namespace ci::app;
using namespace gl;
using namespace std;

class Face : public ModeBaseKinect
{
public :
	void draw() = 0;
	void update() = 0;
	void init() = 0;
};