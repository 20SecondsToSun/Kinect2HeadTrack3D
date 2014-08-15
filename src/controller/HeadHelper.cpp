#include "HeadHelper.h"
using namespace ci;

std::vector<ModelData3D> HeadHelper::modelsVector = [] {
    std::vector<ModelData3D> _modelsVector;

	ModelData3D model;

	model.name = headDefaults::BRIDE_HEAD;
	model.ext = ".dae";
	_modelsVector.push_back(model);

	model.name = headDefaults::PANDA_HEAD;
	model.ext = ".3ds";
	_modelsVector.push_back(model);	

	model.name = headDefaults::CAT_HEAD;
	_modelsVector.push_back(model);

	model.name = headDefaults::PENYA_HEAD;	
	_modelsVector.push_back(model);

	model.name = headDefaults::ED_HEAD;	
	_modelsVector.push_back(model);

	model.name = headDefaults::MIKE_HEAD;	
	_modelsVector.push_back(model);

	model.name = headDefaults::TRANS_HEAD;	
	_modelsVector.push_back(model);

	model.name = headDefaults::NINJ_HEAD;	
	_modelsVector.push_back(model);

	model.name = headDefaults::MICKEY_HEAD;	
	_modelsVector.push_back(model);

	model.name = headDefaults::BENDER_HEAD;	
	_modelsVector.push_back(model);	

    return _modelsVector;

}();

void HeadHelper::loadHeads()
{	
	for (auto head = modelsVector.begin(); head != modelsVector.end(); head++)
	{
		std::string path = "heads/" + head->name + head->ext;		
		head->mesh = model::SkinnedMesh::create( model::loadModel( ci::app::getAssetPath( path))); 
	}

	std::random_shuffle(modelsVector.begin(), modelsVector.end());	
}

void HeadHelper::setDefaultParams(HeadObject* head)
{
	if ( head->name == headDefaults::PANDA_HEAD)
	{
	head->maxShift			= Vec3f(0,-17,0);
	head->minShift			= Vec3f(0,0,0);
	head->maxScale			= 1.3f;
	head->minScale			= 0.4f;
	head->leapInScale		= 1.5f;
	head->leapMaxScale		= 2.6f;
	head->rotation			= Vec3f(0,0,0);
	head->xyz				= Vec3f(-1,-1,-1);
	head->mat_diffuse		= Vec4f(0.784314f,0.784314f,0.784314f,1.f);
	head->mat_specular		= Vec4f(0.f, 0.f, 0.f, 1.f);
	head->mat_ambient		= Vec4f(0.784314f ,0.784314f, 0.784314f, 1.f);
	head->mat_emission		= Vec4f(0.f, 0.f, 0.f, 1.f);
	head->light_position	= Vec4f(260.f, -730.f, -1550.f, 1.f);
	head->light_position	= Vec4f(260.f, -730.f, -1550.f, 1.f);	
	}
	else if ( head->name == headDefaults::BRIDE_HEAD)
	{		
	head->maxShift			= Vec3f(0,0,0);
	head->minShift			= Vec3f(0,0,0);
	head->maxScale			= 2.5f;
	head->minScale			= 0.4f;
	head->leapInScale		= 1.5f;
	head->leapMaxScale		= 2.6f;
	head->rotation			= Vec3f(0,0,0);
	head->xyz				= Vec3f(-1,-1,-1);
	head->light_position	= Vec4f(260, -300, -940, 1);
	head->mat_diffuse		= Vec4f(0.784314f,0.784314f,0.784314f,1.f);
	head->mat_specular		= Vec4f(0,0,0,1);
	head->mat_ambient		= Vec4f(0.784314f, 0.784314f, 0.784314f,1.f);
	head->mat_emission		= Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
	}	
	else if ( head->name == headDefaults::CAT_HEAD)
	{
	head->maxShift			= Vec3f(0,0,0);
	head->minShift			= Vec3f(0,4,0);
	head->maxScale			= 1.5f;
	head->minScale			= 0.4f;
	head->leapInScale		= 1.4f;
	head->leapMaxScale		= 2.3f;
	head->rotation			= Vec3f(0,0,0);
	head->xyz				= Vec3f(-1,-1,-1);

	head->mat_diffuse		= Vec4f(0.784314f,0.784314f,0.784314f,1);
	head->mat_specular		= Vec4f(0.952941f,0.952941f,0.952941f,1);
	head->mat_ambient		= Vec4f(0.784314f,0.784314f,0.784314f,1);
	head->mat_emission		= Vec4f(0,0,0,1);
	head->light_position	= Vec4f(260, -730, -1550, 1);
	}
	else if ( head->name == headDefaults::PENYA_HEAD)
	{
	head->maxShift			= Vec3f(0,-15,0);
	head->minShift			= Vec3f(0,0,0);
	head->maxScale			= 1.1f;
	head->minScale			= 0.3f;
	head->leapInScale		= 1.5f;
	head->leapMaxScale		= 2.5f;
	head->rotation			= Vec3f(0,0,0);
	head->xyz				= Vec3f(-1,-1,-1);
	
	head->mat_diffuse		= Vec4f(0.784314f,0.784314f,0.784314f,1);
	head->mat_specular		= Vec4f(0,0,0,1);
	head->mat_ambient		= Vec4f(0.784314f,0.784314f,0.784314f,1);
	head->mat_emission		= Vec4f(0,0,0,1);
	head->light_position	= Vec4f(260, -730, -1550, 1);
	}
	else if ( head->name == headDefaults::ED_HEAD)
	{		
	head->maxShift			= Vec3f(0,-17,0);
	head->minShift			= Vec3f(0,0,0);
	head->maxScale			= 1.5f;
	head->minScale			= 0.4f;
	head->leapInScale		= 1.4f;
	head->leapMaxScale		= 2.0f;
	head->rotation			= Vec3f(0,0,0);
	head->xyz				= Vec3f(-1,-1,-1);

	head->mat_diffuse		= Vec4f(0.760784f,0.760784f,0.760784f,1);
	head->mat_specular		= Vec4f(0.952941f,0.952941f,0.952941f,1);
	head->mat_ambient		= Vec4f(0.760784f,0.760784f,0.760784f,1);
	head->mat_emission		= Vec4f(0,0,0,1);
	head->light_position	= Vec4f(260, -730, -1550, 1);
	}
	 
	else if ( head->name == headDefaults::MIKE_HEAD)
	{
	head->maxShift			= Vec3f(0,20,0);
	head->minShift			= Vec3f(0,20,0);
	head->maxScale			= 2.4f;
	head->minScale			= 0.5f;
	head->leapInScale		= 1.5f;
	head->leapMaxScale		= 2.5f;
	head->rotation			= Vec3f(0,0,0);
	head->xyz				= Vec3f(-1,-1,-1);
	
	head->mat_diffuse		= Vec4f(0.784314f,0.784314f,0.784314f,1.f);
	head->mat_specular		= Vec4f(0.952941f,0.952941f,0.952941f,1.f);
	head->mat_ambient		= Vec4f(0.784314f,0.784314f,0.784314f,1.f);
	head->mat_emission		= Vec4f(0,0,0,1);
	head->light_position	 = Vec4f(260, -730, -1550, 2);
	}
	else if ( head->name == headDefaults::TRANS_HEAD)
	{
	head->maxShift			= Vec3f(0,3,0);
	head->minShift			= Vec3f(0,9,0);
	head->maxScale			= 1.5f;
	head->minScale			= 0.3f;
	head->leapInScale		= 1.5f;
	head->leapMaxScale		= 2.4f;
	head->rotation			= Vec3f(0,0,0);
	head->xyz				= Vec3f(-1,-1,-1);

	head->mat_diffuse		= Vec4f(0,0.384314f,0.870588f,1.f);
	head->mat_specular		= Vec4f(0.952941f,0.952941f,0.952941f,1.f);
	head->mat_ambient		= Vec4f(0,0.384314f,0.870588f,1.f);
	head->mat_emission		= Vec4f(0,0,0,1);
	head->light_position	= Vec4f(700, 500, 350, 2);
	}
	else if ( head->name == headDefaults::NINJ_HEAD)
	{	
	head->maxShift			= Vec3f(0,-28,0);
	head->minShift			= Vec3f(0,4,0);
	head->maxScale			= 1.1f;
	head->minScale			= 0.3f;
	head->leapInScale		= 1.5f;
	head->leapMaxScale		= 2.8f;
	head->rotation			= Vec3f(0,0,0);
	head->xyz				= Vec3f(-1,-1,-1);

	head->mat_diffuse		= Vec4f(0.784314f,0.784314f,0.784314f,1.f);
	head->mat_specular		= Vec4f(0.952941f,0.952941f,0.952941f,1.f);
	head->mat_ambient		= Vec4f(0.784314f,0.784314f,0.784314f,1.f);
	head->mat_emission		= Vec4f(0,0,0,1);
	head->light_position	= Vec4f(260, -730, -1550, 1);
	}
	else if ( head->name == headDefaults::MICKEY_HEAD)
	{
	head->maxShift			= Vec3f(0,-14,0);
	head->minShift			= Vec3f(0,4,0);
	head->maxScale			= 1.3f;
	head->minScale			= 0.3f;
	head->leapInScale		= 1.6f;
	head->leapMaxScale		= 2.8f;
	head->rotation			= Vec3f(0,0,0);
	head->xyz				= Vec3f(-1,-1,-1);

	head->mat_diffuse		= Vec4f(0.784314f,0.784314f,0.784314f,1.f);
	head->mat_specular		= Vec4f(0.952941f,0.952941f,0.952941f,1.f);
	head->mat_ambient		= Vec4f(0.784314f,0.784314f,0.784314f,1.f);
	head->mat_emission		= Vec4f(0,0,0,1);
	head->light_position	= Vec4f(260, -730, -1550, 1);
	}
	else if ( head->name == headDefaults::BENDER_HEAD)
	{
	head->maxShift			= Vec3f(0,-14,0);
	head->minShift			= Vec3f(0,4,0);
	head->maxScale			= 1.5f;
	head->minScale			= 0.4f;
	head->leapInScale		= 1.4f;
	head->leapMaxScale		= 2.4f;
	head->rotation			= Vec3f(0,0,0);
	head->xyz				= Vec3f(-1,-1,-1);

	head->mat_diffuse		= Vec4f(0.784314f,0.784314f,0.784314f,1.f);
	head->mat_specular		= Vec4f(0.952941f,0.952941f,0.952941f,1.f);
	head->mat_ambient		= Vec4f(0.784314f,0.784314f,0.784314f,1.f);
	head->mat_emission		= Vec4f(0,0,0,1);
	head->light_position	= Vec4f(300, 200, -1000, 1);
	}
}