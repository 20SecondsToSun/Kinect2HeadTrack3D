#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "SkinnedMesh.h"
#include "Kinect.h"
#include "3DModelData.h"

class HeadObject
{
	public:
		HeadObject(MsKinect::Face _face, ModelData3D*  _model)
		{
			face = _face;
			mesh = &_model->mesh;
			name =  _model->name;
			currentAlpha = 1.f;
		};

		void updateFace(MsKinect::Face _face)
		{
			face = _face;
			currentAlpha = 1.f;
		};

		bool isAlive()
		{			
			return currentAlpha> 0.f;
		}

		void addPerish()
		{
			currentAlpha -= 0.02f;
		}
		ci::Vec3f shift; 
		ci::Vec3f maxShift;
		ci::Vec3f minShift;
		ci::Vec3f xyz;

		float maxScale;
		float minScale;

		float leapInScale;
		float leapMaxScale;

		


		ci::Vec3f rotation;
		ci::Vec3f getScale();
		ci::Vec3f getRotAngle();
		ci::Vec3f getScaleLeapMotion();
		
		model::SkinnedMeshRef* getHeadMesh();


		ci::Vec4f  getAmbientLight();
		ci::Vec4f  getDiffuseLight();
		ci::Vec4f  getSpecularLight();
		ci::Vec4f  getEmissionLight();
		ci::Vec4f  getLightPosition();

		ci::Vec4f  mat_ambient;
		ci::Vec4f  mat_diffuse;
		ci::Vec4f  mat_specular;
		ci::Vec4f  mat_emission;
		ci::Vec4f  light_position;


		ci::Vec3f getShift(float percent);
		ci::Vec3f getModelOrientation();
		ci::Vec3f getXYZ();
		void setScaleLeap(ci::Vec3f& scaleL, std::string grow);
		ci::Vec3f getScaleLeapDefault();

		std::string getName();
		std::string name;

		float calcScalePercent(float z );
		float calcScalePercent( );
		ci::Vec2f getFaceCenter();
		ci::ColorA getAlphaColor();

	private :
		
		MsKinect::Face face;
		model::SkinnedMeshRef* mesh;

		float		currentAlpha;
};