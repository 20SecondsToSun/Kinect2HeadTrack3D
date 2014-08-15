#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "SkinnedMesh.h"
#include "3DModelData.h"
#include "ModelSourceAssimp.h"
#include "HeadObject.h"

namespace headDefaults
{
	const std::string	PANDA_HEAD	= "PANDA";
	const std::string	BRIDE_HEAD	= "BRIDE";
	const std::string	CAT_HEAD	= "CAT";
	const std::string	PENYA_HEAD	= "PENYA";
	const std::string	ED_HEAD		= "ED";	
	const std::string	MIKE_HEAD	= "MIKE";
	const std::string	TRANS_HEAD	= "TRANS1";
	const std::string	NINJ_HEAD	= "NINJ";
	const std::string	MICKEY_HEAD = "MICKEY";
	const std::string	BENDER_HEAD = "BENDER";	
}

class HeadHelper
{
  private: 
	static std::vector<ModelData3D>    modelsVector ;

   public:	
	
	static void initHeads(std::vector<ModelData3D>& _modelsVector)
	{
		_modelsVector = modelsVector;
	}

	static void loadHeads();
	static void setDefaultParams(HeadObject* head);
	
};