#include "LocationEngine.h"
#include "Location.h"

void LocationEngine::Init(const char* title, ci::app::WindowRef window , int width, int height, 
						 bool fullscreen)
{
	mainWindow = window;
	isAnimation = false;

	l_MouseDown = mainWindow->getSignalMouseDown().connect( std::bind( &LocationEngine::MouseDown, this,std::placeholders::_1) );

	//mCbMouseDrag = mWindow->getSignalMouseDrag().connect( std::bind( &SquareListener::mouseDrag, this, std::_1 ) );	
}

void LocationEngine::MouseDown( MouseEvent &event )
{	
	if (isAnimation) return;
	
	mouseEvent = event;	
	states.back()->MouseEvents(this);
}	

void LocationEngine::Cleanup()
{
	// cleanup the all states
	while ( !states.empty() )
	{
		states.back()->Cleanup();
		states.pop_back();
	}	
}

void LocationEngine::ChangeState(Location* state) 
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void LocationEngine::PushState(Location* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void LocationEngine::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}

void LocationEngine::HandleEvents() 
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void LocationEngine::Update() 
{
	// let the state update the game
	states.back()->Update(this);
}

void LocationEngine::Draw() 
{
	// let the state draw the screen
	states.back()->Draw(this);
}