#include "MainGame.h"
#include "Instruction.h"
#include "KinectAdapter.h"

using namespace ci;
using namespace ci::app;

MainGame MainGame::MainGameState;

void MainGame::Setup()
{
	
}

void MainGame::Init( LocationEngine* game)
{
	gameMode = new Head3D();
	gameMode->init();
}
void MainGame::Shutdown()
{

}

void MainGame::Cleanup()
{
	delete gameMode;
}
void MainGame::Pause()
{
	
}
void MainGame::Resume()
{
	
}

void MainGame::MouseEvents( LocationEngine* game )
{
	MouseEvent event = game->getMouseEvent();	

	if(game->isAnimationRunning()) return;
	
	game->ChangeState(Instruction::Instance());
}

void MainGame::HandleEvents( LocationEngine* game )
{
}

void MainGame::Update(LocationEngine* game) 
{	
	gameMode->update();
}

void MainGame::Draw(LocationEngine* game) 
{
	gameMode->draw();
}