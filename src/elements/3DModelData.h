#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "SkinnedMesh.h"

struct ModelData3D
{
	public:
		model::SkinnedMeshRef mesh;
		std::string			  ext;
		std::string			  name;
};