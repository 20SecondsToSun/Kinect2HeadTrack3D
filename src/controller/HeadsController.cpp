#include "HeadsController.h"

using namespace headDefaults;
using namespace model;

void HeadsController::initHeads()
{
	HeadHelper::initHeads(modelsVector);

	for (int i = 0; i < kinectDefaults::FACES_MAX; i++)
	{
		player[i] = NULL;
		playersHeadNums[i] = 0;
	}	
}

HeadObject*	HeadsController::getHeadObject(int id, MsKinect::Face face)
{	
	if (player[id] == NULL)
	{		
		player[id] = new HeadObject(face, chooseNewHead(id));	
		HeadHelper::setDefaultParams(player[id]);		
	}	
	else	
		player[id]->updateFace(face);
	
	return player[id];
}

HeadObject*	HeadsController::getHeadDyingObject(int id)
{
	if (player[id] == NULL) return NULL;

	if (player[id]->isAlive())
	{
		player[id]->addPerish();		
	}
	else
	{
		delete player[id];
		player[id] = NULL;
		console()<<"DELETE HEAD ----------------------->  "<<std::endl;
	}

	return player[id];
}

ModelData3D*	HeadsController::chooseNewHead(int id)
{
	int headID = playersHeadNums[id];

	playersHeadNums[id]++;	
	if (playersHeadNums[id] >= modelsVector.size()) playersHeadNums[id] = 0;

	return &modelsVector[headID];	
}