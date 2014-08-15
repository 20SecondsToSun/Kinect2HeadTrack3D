#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "HeadObject.h"
#include "KinectAdapter.h"
#include "SkinnedMesh.h"
#include "HeadHelper.h"

class HeadsController
{
	public:
		void						initHeads();
		HeadObject*					getHeadObject(int id, MsKinect::Face face);
		HeadObject*					getHeadDyingObject(int id);

	private:
	
		ModelData3D*				chooseNewHead(int id);
		std::vector<ModelData3D>    modelsVector;
		HeadObject*					player[kinectDefaults::FACES_MAX];
		int							playersHeadNums[kinectDefaults::FACES_MAX];
};