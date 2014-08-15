#include "Head3DScreen.h"

using namespace model;

void Head3D::init() 
{		
	calculateAspects();
	setUpCamera();
	headsController.initHeads();
}

void Head3D::update() 
{	
	//console()<<" is face ::  "<<kinect->isFaceDetected()<<std::endl;
}

void Head3D::draw() 
{
	detectedPeopleInFrameNum = kinect->getSkeletsInFrame();

	gl::clear();
	gl::setMatricesWindow( getWindowSize());
	gl::enableAlphaBlending();

	TextureRef colorRef =  kinect->getColorTexRef();

	if (colorRef)
	{
		gl::enable( GL_TEXTURE_2D );	

		gl::color( ColorAf::white() );
		
		gl::pushMatrices();
			gl::translate(viewShiftX, viewShiftY);	
			gl::draw( colorRef, colorRef->getBounds(), Rectf(0, 0, float(viewWidth),float(viewHeight)));	
		gl::popMatrices();		

		gl::disable( GL_TEXTURE_2D );
	}
	
	drawHeads3D();
}

void Head3D::drawHeads3D()
{	
	gl::enableDepthRead();

	for (int i = 0, maxfaces = kinect->maxFaces(); i < maxfaces; i++)
	{		
		if (kinect->isFaceDetected(i))
		{
			MsKinect::Face face = kinect->getFace(i);
			HeadObject *head	= headsController.getHeadObject(i, face);
			drawHead(head);
		}
		else
		{
			HeadObject *head	= headsController.getHeadDyingObject(i);

			if (head != NULL)
				drawHead(head);
		}
	}

	gl::disableDepthRead();
}

void Head3D::drawHead(HeadObject* head)
{
	Vec3f rotHeadAngle  = head->getModelOrientation();	
	Vec3f scaleStandart = head->getScale();	
	Vec3f scaleLeap		= head->getScaleLeapMotion();	
	Vec3f rotAngle		= head->getRotAngle();	
	ColorA alphaColor	= head->getAlphaColor();	
			
	onLightsForHead(head); 	
	
	gl::pushMatrices();
				
		set3DLensShift(head);	
		gl::setMatrices(mMayaCam.getCamera());		
		glClear(  GL_DEPTH_BUFFER_BIT );
		gl::enableDepthRead();			
	
		gl::scale(scaleStandart);
		gl::scale(scaleLeap);
	
		gl::rotate(Vec3f(270,0,0));	
		gl::rotate(rotHeadAngle);				
		gl::rotate(rotAngle);
		//gl::enableAlphaBlending();
		//gl::color(alphaColor);
		SkinningRenderer::draw( *head->getHeadMesh());
		//gl::disableAlphaBlending();

	gl::popMatrices();

	offLightsForHead(); 
}

void Head3D::onLightsForHead(HeadObject* head)
{	
	GLfloat no_mat[]		  = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat no_shininess[]    = { 0.0  };
	GLfloat mat_shininess[]	  = { 28.0 };

	Vec4f vec = head->getAmbientLight();
	GLfloat mat_ambient[]	  = {vec.x, vec.y, vec.z, vec.w};

	vec = head->getDiffuseLight();
	GLfloat mat_diffuse	[]	  = {vec.x, vec.y, vec.z, vec.w};

	vec = head->getSpecularLight();
	GLfloat mat_specular[]	  = {vec.x, vec.y, vec.z, vec.w};

	vec = head->getEmissionLight();
	GLfloat mat_emission[]	  = {vec.x, vec.y, vec.z, vec.w};

	vec = head->getLightPosition();
	GLfloat light_position[]  = {vec.x, vec.y, vec.z, vec.w};

	bool DIFFUSE = true, AMBIENT = true, SPECULAR = true, EMISSIVE = true;

	gl::enable( GL_LIGHTING );
	gl::enable( GL_NORMALIZE );
	glEnable( GL_LIGHT0 );

	if( DIFFUSE ){
		glMaterialfv( GL_FRONT, GL_DIFFUSE,	mat_diffuse );
	} else {
		glMaterialfv( GL_FRONT, GL_DIFFUSE,	no_mat );
	}
					
	if( AMBIENT )
		glMaterialfv( GL_FRONT, GL_AMBIENT,	mat_ambient );
	else
		glMaterialfv( GL_FRONT, GL_AMBIENT,	no_mat );
					
	if( SPECULAR ){
		glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
		glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess );
	} else {
		glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
		glMaterialfv( GL_FRONT, GL_SHININESS, no_shininess );
	}
				
	if( EMISSIVE )
		glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission );
	else
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );	

	glLightfv( GL_LIGHT0, GL_POSITION, light_position );	

}

void Head3D::offLightsForHead()
{
	gl::disable( GL_LIGHTING );
	glDisable( GL_LIGHT0 );
	gl::disable( GL_NORMALIZE );
	ci::gl::disable( GL_CULL_FACE );	
}

void Head3D::calculateAspects()
{
	Rectf kinectResolutionR = kinect->getColorResolutionRectf();
	float aspect =  kinectResolutionR.getWidth()/kinectResolutionR.getHeight();
			
	if( getWindowWidth() / getWindowHeight() > aspect)			
	{
		viewHeight = getWindowHeight();
		viewWidth = int(viewHeight * aspect);	
		headScale = viewHeight/ kinectResolutionR.getHeight();
	}
	else 
	{ 
		viewWidth = getWindowWidth();
		viewHeight = int(viewWidth / aspect);	
		headScale  = viewWidth/ kinectResolutionR.getWidth();
	}
	
	viewShiftX =float( 0.5 * (getWindowWidth()  - viewWidth));
	viewShiftY= float( 0.5 * (getWindowHeight() - viewHeight));		
}

void Head3D::setUpCamera()
{
	Vec3f mEye        = Vec3f( 0,0,500);
	Vec3f mCenter     = Vec3f( 0,0,0);
	Vec3f mUp         = Vec3f::yAxis();

	CameraPersp cam = mMayaCam.getCamera();
	cam.setPerspective( 60.0f, getWindowAspectRatio(), 50.0f, -1000.0f );	
	cam.setAspectRatio( getWindowAspectRatio() );
	cam.setEyePoint( mEye);
	cam.setCenterOfInterestPoint( mCenter);
	cam.setWorldUp(mUp);
	mMayaCam.setCurrentCam( cam );
}

void Head3D::set3DLensShift(HeadObject* head )
{
	Rectf worldCoords	 = Rectf(0.0f, 0.0f, float(getWindowWidth()), float(getWindowHeight()));
	Rectf kinectCoords	 = kinect->getColorResolutionRectf();	

	float _xPercent = ((head->getFaceCenter().x/kinectCoords.getWidth())*viewWidth+viewShiftX)/ worldCoords.getWidth();
	float _xInWorld = _xPercent*worldCoords.getWidth();
	float lensSdvigX;

	if (_xInWorld< worldCoords.getWidth()*0.5)
	{
		lensSdvigX = 1 -float(_xInWorld/(worldCoords.getWidth()*0.5));		
	}
	else
	{
		lensSdvigX = - float((_xInWorld- worldCoords.getWidth()*0.5)/(worldCoords.getWidth()*0.5));
	}

	float scalePercent = head->calcScalePercent();
	float _y = head->getShift(scalePercent).y;
	float _yPercent = (((head->getFaceCenter().y + _y)/kinectCoords.getHeight())*viewHeight +viewShiftY)/worldCoords.getHeight();
	float _yInWorld = _yPercent*worldCoords.getHeight();

	float lensSdvigY;

	if (_yInWorld< worldCoords.getHeight()*0.5)
	{
		lensSdvigY = float(_yInWorld/(worldCoords.getHeight()*0.5))-1;
	}
	else
	{
		lensSdvigY =  float((_yInWorld- worldCoords.getHeight()*0.5)/(worldCoords.getHeight()*0.5));
	}

	CameraPersp cam = mMayaCam.getCamera();
	cam.setLensShift(Vec2f(lensSdvigX, lensSdvigY));
	mMayaCam.setCurrentCam( cam );	
}