#ifndef LOCATIONENGINE_H
#define LOCATIONENGINE_H

#include <vector>
#include "cinder/app/AppNative.h"

using namespace std;
using namespace ci;
using namespace ci::app;

class Location;

class LocationEngine
{
public:

	void Init(const char* title, ci::app::WindowRef window, int width=640, int height=480, 
		        bool fullscreen=false);

	void Cleanup();

	void ChangeState(Location* state);
	void PushState(Location* state);
	void PopState();

	void HandleEvents();
	void MouseDown( ci::app::MouseEvent &event );
	void Update();
	void Draw();

	bool Running() { return m_running; }
	void Quit() { m_running = false; }

	void animationRunning(bool value){isAnimation = value;}
	bool isAnimationRunning(){ return isAnimation;}
	ci::app::MouseEvent	getMouseEvent(){ return mouseEvent; }



private:
	// the stack of states
	vector<Location*> states;

	bool m_running;
	bool m_fullscreen;
	bool isAnimation;

	ci::app::WindowRef				mainWindow;
	ci::signals::scoped_connection	l_MouseDown;//, mCbMouseDrag;

	ci::app::MouseEvent				mouseEvent;
};

#endif