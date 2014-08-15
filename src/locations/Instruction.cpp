#include "Instruction.h"
#include "MainGame.h"


using namespace ci;
using namespace ci::app;

Instruction Instruction::InstructionState;

void Instruction::Setup()
{
	

	
}

void Instruction::Init( LocationEngine* game)
{

}

void Instruction::Cleanup()
{
	
}

void Instruction::Pause()
{
	
}
void Instruction::Resume()
{
	
}

void Instruction::MouseEvents( LocationEngine* game )
{
	MouseEvent event = game->getMouseEvent();	

	if(game->isAnimationRunning()) return;

	game->ChangeState(MainGame::Instance());

	
}

void Instruction::HandleEvents( LocationEngine* game )
{
}

void Instruction::Update(LocationEngine* game) 
{

}

void Instruction::Draw(LocationEngine* game) 
{
	gl::clear();
}