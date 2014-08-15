#include "HeadObject.h"
#include "KinectAdapter.h"

using namespace ci;
using namespace ci::app;
using namespace gl;
using namespace std;

ci::Vec3f HeadObject::getScale()
{	
	float scalePercent  = calcScalePercent(face.getTranslationTransform().z);
	float a = minScale +scalePercent*( maxScale - minScale);
	return ci::Vec3f(a,a,a);
}

float HeadObject::calcScalePercent(float z )
{
	if (z > kinectDefaults::MAX_DEPTH) return 0 ;
	else if (z < kinectDefaults::MIN_DEPTH) return 1 ;
	else return (kinectDefaults::MAX_DEPTH - z)/(kinectDefaults::MAX_DEPTH - kinectDefaults::MIN_DEPTH);
}

float HeadObject::calcScalePercent( )
{
	float z = face.getTranslationTransform().z;
	if (z > kinectDefaults::MAX_DEPTH) return 0 ;
	else if (z < kinectDefaults::MIN_DEPTH) return 1 ;
	else return (kinectDefaults::MAX_DEPTH - z)/(kinectDefaults::MAX_DEPTH - kinectDefaults::MIN_DEPTH);
}

ci::ColorA HeadObject::getAlphaColor()
{
	return ColorA(1, 1, 1, currentAlpha);
}

ci::Vec3f HeadObject::getRotAngle()
{
	float _x = getXYZ().x* face.getRotationTransform()[0];
	float _z = getXYZ().y* face.getRotationTransform()[1];
	float _y = getXYZ().z* face.getRotationTransform()[2];
	return Vec3f(floor(_x), floor(_y),floor(_z));
}

model::SkinnedMeshRef* HeadObject::getHeadMesh()
{
	return mesh;
}

ci::Vec2f HeadObject::getFaceCenter()
{
	return face.getBounds().getCenter();
}

ci::Vec3f HeadObject::getScaleLeapMotion()
{
	return Vec3f( 1.f, 1.f, 1.f);
}

ci::Vec4f HeadObject::getAmbientLight()
{
	return mat_ambient;
}

ci::Vec4f HeadObject::getDiffuseLight()
{
	return mat_diffuse;	
}

ci::Vec4f HeadObject::getSpecularLight()
{	
	return mat_specular;	
}

ci::Vec4f HeadObject::getEmissionLight()
{	
	return mat_emission;	
}

ci::Vec4f HeadObject::getLightPosition()
{
	return light_position;	
}

ci::Vec3f HeadObject::getShift(float percent)
{
	return minShift+percent*( maxShift - minShift);
}

ci::Vec3f HeadObject::getModelOrientation()
{
	return rotation;	
}

ci::Vec3f HeadObject::getXYZ()
{
	return xyz;	
}

void HeadObject::setScaleLeap(Vec3f& scaleL, string grow)
{
	float param = 0.025f;
	if (grow == "BIGGER")
	{
		if (scaleL.x>= leapMaxScale) scaleL = Vec3f(leapMaxScale,leapMaxScale,leapMaxScale);
		else scaleL += Vec3f(param,param, param);
	}
	else if (grow == "SMALLER")
	{
		if (scaleL.x<= 1) scaleL = Vec3f(1,1,1);
		else scaleL -= Vec3f(param,param, param);
	}
}

ci::Vec3f HeadObject::getScaleLeapDefault()
{
	return Vec3f(leapInScale,leapInScale,leapInScale);
}

std::string HeadObject::getName()
{
	return name;
}