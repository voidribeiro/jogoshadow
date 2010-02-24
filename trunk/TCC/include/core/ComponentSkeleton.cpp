#include "ComponentSkeleton.h"

ComponentSkeleton::ComponentSkeleton():destination(NULL){
 	i=b=a=c=kTemp=k=0;
	sinAlpha=sinGamma=0;
	sinAlphaTwo=0;
	cosAlpha=0;
	interpolationCount=4;
	enableInterpolation=false;
	skeletonVelocity=core::vector3df(0,0,0);
  
}

ComponentSkeleton::ComponentSkeleton(std::string filename, u32 _speed):speed( _speed), destination(NULL){

  IrrlichtDevice* device = DeviceManager::GetDevice();
  irr::video::IVideoDriver* driver = DeviceManager::GetDriver(); 
  irr::scene::ISceneManager* sceneManager = device->getSceneManager();
  
  i=b=a=c=kTemp=k=0;
	sinAlpha=sinGamma=0;
	sinAlphaTwo=0;
	cosAlpha=0;
	interpolationCount=4;
	enableInterpolation=false;
	skeletonVelocity=core::vector3df(0,0,0);

  mesh = sceneManager->getMesh( filename.c_str() );

  if(!mesh)
    printf("Unable to load mesh!");
 
  node = sceneManager->addAnimatedMeshSceneNode( mesh );
  
  //setAnimType(CSK_ANIM_WALK);
  //node->setPosition( core::vector3df(0, 45, 0) );

  init(node, speed);

}

ComponentSkeleton::~ComponentSkeleton(){
  //TODO - Remove node from scene
}

void ComponentSkeleton::SetPosition(const core::vector3df &newpos){
  node->setPosition(newpos);
}

void ComponentSkeleton::Update(){

  node->setScale( core::vector3df(8,8,8) );

  animSkeleton();

  if(destination == NULL)
    return;

  if(destination->getDistanceFrom(node->getPosition()) < 1.0f){
    setAnimType(CSK_ANIM_STAND);
    delete destination;
    destination = NULL;
  }

}

core::vector3df ComponentSkeleton::matrixRotation(core::vector3df rotation, core::vector3df vec){
	f32 pitch=vec.X;
	f32 yaw=vec.Y;
	f32 roll=vec.Z;
	matrix4 m,t;
	m.setRotationDegrees(rotation);

	t.setRotationDegrees(core::vector3df(0,0,roll));
	m*=t;

	t.setRotationDegrees(core::vector3df(pitch,0,0));
	m*=t;

	t.setRotationDegrees(core::vector3df(0,yaw,0));
	t*=m;

	return t.getRotationDegrees();
}

void ComponentSkeleton::Draw(){
}

// Initialization
void ComponentSkeleton::init(scene::IAnimatedMeshSceneNode *node, u32 setSpeed) {

  for(unsigned int idx=0; idx < node->getMaterialCount(); idx++)
    node->getMaterial(idx).Lighting = false;

  node=node;

	if (!node)
		return;

	i=k=360;
	animType = lastAnimType = CSK_ANIM_STAND;
	speed=setSpeed;

	for (u32 n=0; n < SKT_BONE_COUNT; n++) {
		bonesOsci.push_back(core::vector3df(0,0,0));
		bonesOsciPos.push_back(core::vector3df(0,0,0));
	}

	// save bone names in boneName array
	for (u32 n=0; n < SKT_BONE_COUNT; n++) {

		switch (n) {
		// main items
		case SKT_BONE_TORSO:
			boneName.push_back((irr::c8*) "pelvis");
			break;
		case SKT_BONE_STOMACH:
			boneName.push_back((irr::c8*) "stomach");
			break;
		case SKT_BONE_BODY:
			boneName.push_back((irr::c8*) "body");
			break;
		case SKT_BONE_NECK:
			boneName.push_back((irr::c8*) "neck");
			break;
		case SKT_BONE_HEAD:
			boneName.push_back((irr::c8*) "head");
			break;

		// right arm items
		case SKT_BONE_ARM_R:
			boneName.push_back((irr::c8*) "upperArmL");
			break;
		case SKT_BONE_UARM_R:
			boneName.push_back((irr::c8*) "underArmL");
			break;
		case SKT_BONE_HAND_R:
			boneName.push_back((irr::c8*) "handL");
			break;
		case SKT_BONE_FINGER_R:
			boneName.push_back((irr::c8*) "fingerL");
			break;

		// left arm items
		case SKT_BONE_ARM_L:
			boneName.push_back((irr::c8*) "upperArmR");
			break;
		case SKT_BONE_UARM_L:
			boneName.push_back((irr::c8*) "underArmR");
			break;
		case SKT_BONE_HAND_L:
			boneName.push_back((irr::c8*) "handR");
			break;
		case SKT_BONE_FINGER_L:
			boneName.push_back((irr::c8*) "fingerR");
			break;

		// right leg items
		case SKT_BONE_LEG_R:
			boneName.push_back((irr::c8*) "legL");
			break;
		case SKT_BONE_SHIN_R:
			boneName.push_back((irr::c8*) "shinL");
			break;
		case SKT_BONE_FEET_R:
			boneName.push_back((irr::c8*) "feetL");
			break;
		case SKT_BONE_TOES_R:
			boneName.push_back((irr::c8*) "toesL");
			break;

		// left leg items
		case SKT_BONE_LEG_L:
			boneName.push_back((irr::c8*) "legR");
			break;
		case SKT_BONE_SHIN_L:
			boneName.push_back((irr::c8*) "shinR");
			break;
		case SKT_BONE_FEET_L:
			boneName.push_back((irr::c8*) "feetR");
			break;
		case SKT_BONE_TOES_L:
			boneName.push_back((irr::c8*) "toesR");
			break;
		}

	}

	// loading 3d model
	if (node) {
		node->setScale( vector3df(2,2,2) );
		node->setRotation( vector3df(0,90,0) );
		node->setFrameLoop( 0,0 );
		node->setJointMode( irr::scene::EJUOR_CONTROL );

		// get all bone scene nodes
		for (u32 n=0; n < SKT_BONE_COUNT; n++) {
			bones.push_back(node->getJointNode(boneName[n]));
		}

		// set player in stand position
		bones[SKT_BONE_ARM_R]->setRotation( vector3df(0,0,-22) );

		core::vector3df vec;
		vec = matrixRotation(bones[SKT_BONE_ARM_R]->getRotation(), core::vector3df(0,0,-144));
		bones[SKT_BONE_ARM_R]->setRotation(vec);

		vec = matrixRotation(bones[SKT_BONE_UARM_R]->getRotation(), core::vector3df(8,0,-10));
		bones[SKT_BONE_UARM_R]->setRotation(vec);

		vec = matrixRotation(bones[SKT_BONE_ARM_L]->getRotation(), core::vector3df(0,0,22));
		bones[SKT_BONE_ARM_L]->setRotation(vec);

		vec = matrixRotation(bones[SKT_BONE_UARM_L]->getRotation(), core::vector3df(8,0,10));
		bones[SKT_BONE_UARM_L]->setRotation(vec);

		// store all current bone animation for stand position
		bonesRot.clear();
		for (u32 n=0; n<SKT_BONE_COUNT; n++) {
			bonesRot.push_back( bones[n]->getRotation() );
			bonesPos.push_back( bones[n]->getPosition() );
		}

	}

}

// set the type of animation
void ComponentSkeleton::setAnimType(CSK_ANIM setAnimType) {

	if (animType != CSK_ANIM_JUMP) {

		animType=setAnimType;
		if (lastAnimType!=animType && enableInterpolation!=true) {
			enableInterpolation=true;
			interpolationCount=30;
		}

		kTemp=0;
	}

}

void ComponentSkeleton::animSkeleton() {

  core::position2di mousePos = DeviceManager::eventListener->GetMouseState().pos;

	a = k%360;
	b = (k-180)%360;
	c = (k-90)%360;

	f32 rad = (f32)3.14159/180;

	alpha = a * rad;
	gamma = c * rad;

	// oscillation functions
	sinAlpha = sin(alpha);
	sinGamma = sin(gamma);
	sinAlphaTwo = sin(2*alpha);
	cosAlpha = cos(alpha);

	skeletonVelocity=core::vector3df(0,0,0);

	if (enableInterpolation) {

		animInterpolation();
		(interpolationCount==0) ? (enableInterpolation=false) : (interpolationCount--);

	}

	if (enableInterpolation==false) {

		switch(animType) {
		// animation for standing --------------------------------------------------
		case CSK_ANIM_STAND:
			animStand();
			// to get smooth interpolation from stand to another animation
			k=360;
			break;

		// animation for jumping --------------------------------------------------
		case CSK_ANIM_JUMP:
			animJump();
			break;

		// animation for running ---------------------------------------------------
		case CSK_ANIM_RUN:
			animRun();
			break;

		// animation for walking ---------------------------------------------------
		case CSK_ANIM_WALK:
			animWalk();
			break;

		// animation for backward walking -----------------------------------------
		case CSK_ANIM_BACKWARD:
			animBackward();
			break;

		// animation for strafe walking -----------------------------------------
		case CSK_ANIM_STRAFELEFT:
			animStrafeLeft();
			break;

		// animation for strafe walking -----------------------------------------
		case CSK_ANIM_STRAFERIGHT:
			animStrafeRight();
			break;

		default:
			break;

		} // end animation type ---------------------------------------------------

	}

	// this function let the head look into mouse pointers direction
	animHead(mousePos);

	k+=speed;
	i+=4;
	// stop jump animation if kTemp run from zero to 360
	if (kTemp>360)
		animType=CSK_ANIM_STAND;

	// apply all rotations to bones
	for (int n=0; n<SKT_BONE_COUNT; n++) {
		bones[n]->setRotation(matrixRotation(bonesRot[n], bonesOsci[n]));
		bones[n]->setPosition(bonesPos[n]+ bonesOsciPos[n]);
	}

}

void ComponentSkeleton::animWalk() {

	// LEGS
	bonesOsci[SKT_BONE_LEG_R] = core::vector3df( -28.f*sinAlpha, -5.f*sinAlpha,0);
	bonesOsci[SKT_BONE_LEG_L] = core::vector3df( 28.f*sinAlpha, -5.f*sinAlpha,0);

	// SHINS
	if (a>270 || a<90) {
		bonesOsci[SKT_BONE_SHIN_L] = core::vector3df( -60.f*cosAlpha ,0,0);
		bonesOsci[SKT_BONE_SHIN_R] = core::vector3df( -10.f*cosAlpha,0,0);
	} else {
		bonesOsci[SKT_BONE_SHIN_L] = core::vector3df( -10.f*-cosAlpha,0,0 );
		bonesOsci[SKT_BONE_SHIN_R] = core::vector3df( -60.f*-cosAlpha ,0,0);
	}

	// ARMS
	bonesOsci[SKT_BONE_ARM_R] = core::vector3df( -(15.f*-sinAlpha + 5.f) ,0,0);
	bonesOsci[SKT_BONE_ARM_L] = core::vector3df( -(15.f*sinAlpha + 5.f) ,0,0);

	// UNDER ARMS
	bonesOsci[SKT_BONE_UARM_R] = core::vector3df( 11.f*sinAlpha + 15.f ,0,0);
	bonesOsci[SKT_BONE_UARM_L] = core::vector3df( 11.f*-sinAlpha + 15.f ,0,0);

	// TORSO
	bonesOsci[SKT_BONE_TORSO] = core::vector3df(0, 8.f*sinAlpha ,0);

	// BODY NECK HEAD
	bonesOsci[SKT_BONE_BODY] = core::vector3df(6.f, 15.f*-sinAlpha ,0);
	bonesOsci[SKT_BONE_HEAD] = core::vector3df( 0, 7.f *sinAlpha ,0);

	if (a < 172 || a < 352) {
		bonesOsciPos[SKT_BONE_TORSO] = core::vector3df(0,.06f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_BODY] = core::vector3df(0,.01f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_HEAD] = core::vector3df(0,.01f*sinAlphaTwo,0);
	}

	bonesOsci[SKT_BONE_NECK] = core::vector3df(0,0,0);
	bonesOsci[SKT_BONE_STOMACH] = core::vector3df(0,0,0);

	skeletonVelocity=core::vector3df(.5f,0,0);
	lastAnimType=CSK_ANIM_WALK;

}

void ComponentSkeleton::animRun() {

	f32 sinGammaNeg = sin(-gamma);

	if (b<90) {
		bonesOsci[SKT_BONE_LEG_L] = core::vector3df( (b)*-.5f, 15.f*-sinAlpha ,0 );
	} else if (b>270) {
		bonesOsci[SKT_BONE_LEG_L] = core::vector3df( (b-360)*.5f,15.f*-sinAlpha,0 );
	} else {
		bonesOsci[SKT_BONE_LEG_L] = core::vector3df( 45.f*sinAlpha,15.f*-sinAlpha,0 );
	}

	if (a<90) {
		bonesOsci[SKT_BONE_LEG_R] = core::vector3df( (a)*-.5f, 15.f*-sinAlpha ,0 );
	} else if (a>270) {
		bonesOsci[SKT_BONE_LEG_R] = core::vector3df( (a-360)*.5f,15.f*-sinAlpha,0 );
	} else {
		bonesOsci[SKT_BONE_LEG_R] = core::vector3df( -45.f*sinAlpha,15.f*-sinAlpha,0 );
	}

	// SHINS
	bonesOsci[SKT_BONE_SHIN_L] = core::vector3df( -40.f*(sinGammaNeg+1),0,0);
	bonesOsci[SKT_BONE_SHIN_R] = core::vector3df( -40.f*(sinGamma+1),0,0);

	// NECK BODY HEAD
	bonesOsci[SKT_BONE_BODY] = core::vector3df(3.f, 13.f*-sinAlpha, 0);
	bonesOsci[SKT_BONE_NECK] = core::vector3df(-10.f, 7.f*sinAlpha, 0);
	bonesOsci[SKT_BONE_HEAD] = core::vector3df( 1.5f*sinAlpha ,0,2.f*sinAlphaTwo);

	// ARMS
	bonesOsci[SKT_BONE_ARM_L] = core::vector3df( -(35.f*sinAlpha+10.f) , 0,10.f*sinAlpha);
	bonesOsci[SKT_BONE_ARM_R] = core::vector3df( -(35.f*-sinAlpha+10.f) ,0,10.f*sinAlpha);
	bonesOsciPos[SKT_BONE_ARM_L] = core::vector3df(0,.035f*sinAlpha,.035f*cosAlpha);
	bonesOsciPos[SKT_BONE_ARM_R] = core::vector3df(0,.035f*-sinAlpha,.035f*-cosAlpha);

	// UNDER ARMS
	bonesOsci[SKT_BONE_UARM_R] = core::vector3df( 30.f*sinAlpha + 50.f ,0,10.f*-sinAlpha);
	bonesOsci[SKT_BONE_UARM_L] = core::vector3df( 30.f*-sinAlpha + 50.f ,0,10.f*-sinAlpha);

	// MAIN ITEMS
	bonesOsci[SKT_BONE_TORSO] = core::vector3df(0, 15.f*sinAlpha , 1.f*sinAlpha);
	bonesOsci[SKT_BONE_STOMACH] = core::vector3df(12.f, 15.f*-sinAlpha , 0);

	if (a < 172 || b < 172) {
		bonesOsciPos[SKT_BONE_TORSO] = core::vector3df(0,.1f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_BODY] = core::vector3df(0,.03f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_HEAD] = core::vector3df(0,.03f*sinAlphaTwo,0);
	}

	skeletonVelocity=core::vector3df(1.0f,0,0);
	lastAnimType=CSK_ANIM_RUN;

}

void ComponentSkeleton::animStand() {

	f32 rad = (f32)3.14159/180;

	bonesOsci[SKT_BONE_ARM_R] = core::vector3df(5,0,0);
	bonesOsci[SKT_BONE_ARM_L] = core::vector3df(5,0,0);

	bonesOsci[SKT_BONE_BODY] = core::vector3df(-4.f*sin(i%360*rad),0,0);
	bonesOsci[SKT_BONE_NECK] = core::vector3df(0,0,0);
	bonesOsci[SKT_BONE_HEAD] = core::vector3df(0,0,0);

	bonesOsci[SKT_BONE_UARM_R] = core::vector3df(-5.f*(sin(1*i%360*rad)-1.f),0,-5);
	bonesOsci[SKT_BONE_UARM_L] = core::vector3df(-5.f*(sin(1*i%360*rad)-1.f),0,5);

	// setting bones to zero we dont need here
	bonesOsci[SKT_BONE_LEG_R] = core::vector3df(0,0,0);
	bonesOsci[SKT_BONE_LEG_L] = core::vector3df(0,0,0);
	bonesOsci[SKT_BONE_SHIN_R] = core::vector3df(0,0,0);
	bonesOsci[SKT_BONE_SHIN_L] = core::vector3df(0,0,0);

	bonesOsci[SKT_BONE_TORSO] = core::vector3df(0,0,0);
	bonesOsci[SKT_BONE_STOMACH] = core::vector3df(0,0,0);

	bonesOsciPos[SKT_BONE_BODY] = core::vector3df(0,.04f*sin(i%360*rad),0);

	lastAnimType=CSK_ANIM_STAND;

}

void ComponentSkeleton::animJump() {

	k-=speed;
	f32 sinGammaNeg = sin(-gamma);

	bonesOsci[SKT_BONE_LEG_L] = core::vector3df( -45.f*-sinAlpha,15.f*-sinAlpha,0 );
	bonesOsci[SKT_BONE_LEG_R] = core::vector3df( -45.f*sinAlpha,15.f*-sinAlpha,0 );

	// SHINS
	bonesOsci[SKT_BONE_SHIN_L] = core::vector3df( -60.f*(sinGammaNeg+1),0,0);
	bonesOsci[SKT_BONE_SHIN_R] = core::vector3df( -60.f*(sinGamma+1),0,0);

	// NECK BODY HEAD
	bonesOsci[SKT_BONE_BODY] = core::vector3df(10.f*(sinAlpha+1.f), 13.f*-sinAlpha, 0);
	bonesOsci[SKT_BONE_NECK] = core::vector3df(-10.f, 7.f*sinAlpha, 0);
	bonesOsci[SKT_BONE_HEAD] = core::vector3df( 1.5f*sinAlpha ,0,2.f*sinAlphaTwo);

	// ARMS
	bonesOsci[SKT_BONE_ARM_L] = core::vector3df( -(35.f*sinAlpha+10.f) , 0,-20.f*(sinAlpha+1.f));
	bonesOsci[SKT_BONE_ARM_R] = core::vector3df( -(35.f*-sinAlpha+10.f) ,0,20.f*(sinAlpha+1.f));
	bonesOsciPos[SKT_BONE_ARM_L] = core::vector3df(0,.035f*sinAlpha,.035f*cosAlpha);
	bonesOsciPos[SKT_BONE_ARM_R] = core::vector3df(0,.035f*-sinAlpha,.035f*-cosAlpha);

	// UNDER ARMS
	bonesOsci[SKT_BONE_UARM_R] = core::vector3df( 30.f*sinAlpha + 50.f ,0,10.f*-sinAlpha);
	bonesOsci[SKT_BONE_UARM_L] = core::vector3df( 30.f*-sinAlpha + 50.f ,0,10.f*-sinAlpha);

	// MAIN ITEMS
	bonesOsci[SKT_BONE_TORSO] = core::vector3df(0, 15.f*sinAlpha , 1.f*sinAlpha);
	bonesOsci[SKT_BONE_STOMACH] = core::vector3df(12.f, 15.f*-sinAlpha , 0);

	if (a < 172 || b < 172) {
		bonesOsciPos[SKT_BONE_TORSO] = core::vector3df(0,.1f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_BODY] = core::vector3df(0,.03f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_HEAD] = core::vector3df(0,.03f*sinAlphaTwo,0);
	}

	skeletonVelocity=core::vector3df(1.0f,0,0);
	k+=6;
	kTemp+=6;
	lastAnimType=CSK_ANIM_RUN;

}

void ComponentSkeleton::animBackward() {

	// LEGS
	bonesOsci[SKT_BONE_LEG_R] = core::vector3df( -28.f*sinAlpha, 0.f*sinAlpha,0);
	bonesOsci[SKT_BONE_LEG_L] = core::vector3df( -28.f*-sinAlpha, 0.f*sinAlpha,0);

	bonesOsci[SKT_BONE_SHIN_R] = core::vector3df( -30.f*(cosAlpha+1),0,0);
	bonesOsci[SKT_BONE_SHIN_L] = core::vector3df( -30.f*(-cosAlpha+1),0,0);

	// ARMS
	bonesOsci[SKT_BONE_ARM_R] = core::vector3df( -(15.f*-sinAlpha + 15.f) ,0,0);
	bonesOsci[SKT_BONE_ARM_L] = core::vector3df( -(15.f*sinAlpha + 15.f) ,0,0);

	// UNDER ARMS
	bonesOsci[SKT_BONE_UARM_R] = core::vector3df( 11.f*sinAlpha + 15.f ,0,0);
	bonesOsci[SKT_BONE_UARM_L] = core::vector3df( 11.f*-sinAlpha + 15.f ,0,0);

	// TORSO
	bonesOsci[SKT_BONE_TORSO] = core::vector3df(0, 8.f*sinAlpha ,0);

	// BODY NECK HEAD
	bonesOsci[SKT_BONE_BODY] = core::vector3df(6.f, 15.f*-sinAlpha ,0);
	bonesOsci[SKT_BONE_HEAD] = core::vector3df( 0, 7.f *sinAlpha ,0);

	if (a < 172 || b < 172) {
		bonesOsciPos[SKT_BONE_TORSO] = core::vector3df(0,.06f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_BODY] = core::vector3df(0,.01f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_HEAD] = core::vector3df(0,.01f*sinAlphaTwo,0);
	}

	bonesOsci[SKT_BONE_NECK] = core::vector3df(0,0,0);
	bonesOsci[SKT_BONE_STOMACH] = core::vector3df(0,0,0);

	skeletonVelocity=core::vector3df(-.5f,0,0);
	lastAnimType=CSK_ANIM_BACKWARD;

}

void ComponentSkeleton::animStrafeLeft() {

	f32 sinGammaNeg = sin(-gamma);

	if (b<90) {
		bonesOsci[SKT_BONE_LEG_L] = core::vector3df( (b)*-.5f, 15.f*-sinAlpha ,0 );
	} else if (b>270) {
		bonesOsci[SKT_BONE_LEG_L] = core::vector3df( (b-360)*.5f,15.f*-sinAlpha,0 );
	} else {
		bonesOsci[SKT_BONE_LEG_L] = core::vector3df( -45.f*-sinAlpha,15.f*-sinAlpha,0 );
	}

	if (a<90) {
		bonesOsci[SKT_BONE_LEG_R] = core::vector3df( (a)*-.5f, 15.f*-sinAlpha ,0 );
	} else if (a>270) {
		bonesOsci[SKT_BONE_LEG_R] = core::vector3df( (a-360)*.5f,15.f*-sinAlpha,0 );
	} else {
		bonesOsci[SKT_BONE_LEG_R] = core::vector3df( -45.f*sinAlpha,15.f*-sinAlpha,0 );
	}

	// SHINS
	bonesOsci[SKT_BONE_SHIN_L] = core::vector3df( -40.f*(sinGammaNeg+1),0,0);
	bonesOsci[SKT_BONE_SHIN_R] = core::vector3df( -40.f*(sinGamma+1),0,0);

	// NECK BODY HEAD
	bonesOsci[SKT_BONE_BODY] = core::vector3df(3.f, 13.f*-sinAlpha, 0);
	bonesOsci[SKT_BONE_NECK] = core::vector3df(-10.f, 7.f*sinAlpha, 0);
	bonesOsci[SKT_BONE_HEAD] = core::vector3df( 1.5f*sinAlpha ,0,2.f*sinAlphaTwo);

	// ARMS
	bonesOsci[SKT_BONE_ARM_L] = core::vector3df( -(35.f*sinAlpha+10.f) , 0,10.f*sinAlpha);
	bonesOsci[SKT_BONE_ARM_R] = core::vector3df( -(35.f*-sinAlpha+10.f) ,0,10.f*sinAlpha);
	bonesOsciPos[SKT_BONE_ARM_L] = core::vector3df(0,.035f*sinAlpha,.035f*cosAlpha);
	bonesOsciPos[SKT_BONE_ARM_R] = core::vector3df(0,.035f*-sinAlpha,.035f*-cosAlpha);

	// UNDER ARMS
	bonesOsci[SKT_BONE_UARM_R] = core::vector3df( 30.f*sinAlpha + 50.f ,0,10.f*-sinAlpha);
	bonesOsci[SKT_BONE_UARM_L] = core::vector3df( 30.f*-sinAlpha + 50.f ,0,10.f*-sinAlpha);

	// MAIN ITEMS
	bonesOsci[SKT_BONE_TORSO] = core::vector3df(0, 15.f*sinAlpha - 35.f , 1.f*sinAlpha);
	bonesOsci[SKT_BONE_STOMACH] = core::vector3df(12.f, 15.f*-sinAlpha + 35.f , 0);

	if (a < 172 || b < 172) {
		bonesOsciPos[SKT_BONE_TORSO] = core::vector3df(0,.1f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_BODY] = core::vector3df(0,.03f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_HEAD] = core::vector3df(0,.03f*sinAlphaTwo,0);
	}

	skeletonVelocity=core::vector3df(.8f,30.f,0);
	lastAnimType=CSK_ANIM_STRAFELEFT;

}

void ComponentSkeleton::animStrafeRight() {

	f32 sinGammaNeg = sin(-gamma);

	if (b<90) {
		bonesOsci[SKT_BONE_LEG_L] = core::vector3df( (b)*-.5f, 15.f*-sinAlpha ,0 );
	} else if (b>270) {
		bonesOsci[SKT_BONE_LEG_L] = core::vector3df( (b-360)*.5f,15.f*-sinAlpha,0 );
	} else {
		bonesOsci[SKT_BONE_LEG_L] = core::vector3df( -45.f*-sinAlpha,15.f*-sinAlpha,0 );
	}

	if (a<90) {
		bonesOsci[SKT_BONE_LEG_R] = core::vector3df( (a)*-.5f, 15.f*-sinAlpha ,0 );
	} else if (a>270) {
		bonesOsci[SKT_BONE_LEG_R] = core::vector3df( (a-360)*.5f,15.f*-sinAlpha,0 );
	} else {
		bonesOsci[SKT_BONE_LEG_R] = core::vector3df( -45.f*sinAlpha,15.f*-sinAlpha,0 );
	}

	// SHINS
	bonesOsci[SKT_BONE_SHIN_L] = core::vector3df( -40.f*(sinGammaNeg+1),0,0);
	bonesOsci[SKT_BONE_SHIN_R] = core::vector3df( -40.f*(sinGamma+1),0,0);

	// NECK BODY HEAD
	bonesOsci[SKT_BONE_BODY] = core::vector3df(3.f, 13.f*-sinAlpha, 0);
	bonesOsci[SKT_BONE_NECK] = core::vector3df(-10.f, 7.f*sinAlpha, 0);
	bonesOsci[SKT_BONE_HEAD] = core::vector3df( 1.5f*sinAlpha ,0,2.f*sinAlphaTwo);

	// ARMS
	bonesOsci[SKT_BONE_ARM_L] = core::vector3df( -(35.f*sinAlpha+10.f) , 0,10.f*sinAlpha);
	bonesOsci[SKT_BONE_ARM_R] = core::vector3df( -(35.f*-sinAlpha+10.f) ,0,10.f*sinAlpha);
	bonesOsciPos[SKT_BONE_ARM_L] = core::vector3df(0,.035f*sinAlpha,.035f*cosAlpha);
	bonesOsciPos[SKT_BONE_ARM_R] = core::vector3df(0,.035f*-sinAlpha,.035f*-cosAlpha);

	// UNDER ARMS
	bonesOsci[SKT_BONE_UARM_R] = core::vector3df( 30.f*sinAlpha + 50.f ,0,10.f*-sinAlpha);
	bonesOsci[SKT_BONE_UARM_L] = core::vector3df( 30.f*-sinAlpha + 50.f ,0,10.f*-sinAlpha);

	// MAIN ITEMS
	bonesOsci[SKT_BONE_TORSO] = core::vector3df(0, 15.f*sinAlpha + 35.f , 1.f*sinAlpha);
	bonesOsci[SKT_BONE_STOMACH] = core::vector3df(12.f, 15.f*-sinAlpha - 35.f , 0);

	if (a < 172 || b < 172) {
		bonesOsciPos[SKT_BONE_TORSO] = core::vector3df(0,.1f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_BODY] = core::vector3df(0,.03f*sinAlphaTwo,0);
		bonesOsciPos[SKT_BONE_HEAD] = core::vector3df(0,.03f*sinAlphaTwo,0);
	}

	skeletonVelocity=core::vector3df(.8f,-30.f,0);
	lastAnimType=CSK_ANIM_STRAFERIGHT;

}

void ComponentSkeleton::animHead(core::position2di mousePos) {

	mousePos -= core::position2di(400,300);

	bonesOsci[SKT_BONE_HEAD] = core::vector3df(.2f*mousePos.Y,.15f*mousePos.X,0);

}

void ComponentSkeleton::animInterpolation() {

	core::array<core::vector3df> bonesOsciTemp;
	core::array<core::vector3df> bonesOsciPosTemp;
	f32 mult=1.f;

	for (u32 n=0; n<SKT_BONE_COUNT; ++n) {
		bonesOsciTemp.push_back(bonesOsci[n]);
		bonesOsciPosTemp.push_back(bonesOsciPos[n]);
	}

	switch(animType) {
	// animation for standing --------------------------------------------------
	case CSK_ANIM_STAND:
		animStand();
		break;

	// animation for jumping --------------------------------------------------
	case CSK_ANIM_JUMP:
		animJump();
		break;

	// animation for running ---------------------------------------------------
	case CSK_ANIM_RUN:
		animRun();
		break;

	// animation for walking ---------------------------------------------------
	case CSK_ANIM_WALK:
		animWalk();
		break;

	// animation for backward walking -----------------------------------------
	case CSK_ANIM_BACKWARD:
		animBackward();
		break;

	// animation for strafe walking -----------------------------------------
	case CSK_ANIM_STRAFELEFT:
		animStrafeLeft();
		break;

	// animation for strafe walking -----------------------------------------
	case CSK_ANIM_STRAFERIGHT:
		animStrafeRight();
		break;

	default:
		break;

	} // end animation type ---------------------------------------------------

	for (u32 n=0; n<SKT_BONE_COUNT; ++n) {

		(bonesOsci[n].X >= bonesOsciTemp[n].X) ? (mult=-1.f) : (mult=1.f);
		bonesOsci[n].X += mult*abs_<f32>(bonesOsci[n].X - bonesOsciTemp[n].X) * (pow(2.7f,-.1f*(30-interpolationCount)));

		(bonesOsci[n].Y >= bonesOsciTemp[n].Y) ? (mult=-1.f) : (mult=1.f);
		bonesOsci[n].Y += mult*abs_<f32>(bonesOsci[n].Y - bonesOsciTemp[n].Y) * (pow(2.7f,-.1f*(30-interpolationCount)));

		(bonesOsci[n].Z >= bonesOsciTemp[n].Z) ? (mult=-1.f) : (mult=1.f);
		bonesOsci[n].Z += mult*abs_<f32>(bonesOsci[n].Z - bonesOsciTemp[n].Z) * (pow(2.7f,-.1f*(30-interpolationCount)));

	}

}

void ComponentSkeleton::WalkTo(vector3df pos){

  IrrlichtDevice* device = DeviceManager::GetDevice();
  ISceneManager* sceneManager = device->getSceneManager();

  if(destination != NULL){
    delete destination;
    destination = NULL;
  }

  pos.Y += 30;

  destination = new irr::core::vector3df(pos.X, pos.Y, pos.Z);

  scene::ISceneNodeAnimator* anim;

  setAnimType(CSK_ANIM_WALK);

  core::vector3df requiredRotation = (pos - node->getAbsolutePosition());
  requiredRotation = requiredRotation.getHorizontalAngle();

  //Doesnt require to point down... so just rotates on Y axis
  requiredRotation.X = 0;
  requiredRotation.Z = 0;

  node->setRotation(requiredRotation);

  anim =	sceneManager->createFlyStraightAnimator(
           node->getPosition(), 
           pos,
           10 * (irr::u32) pos.getDistanceFrom(node->getPosition()),
           false);

  node->addAnimator(anim);
  anim->drop();

}

int ComponentSkeleton::IsWalking(){
  if(destination != NULL)
    return 1;

  return 0;
}

/////////////////////////////////////////////////////////

int ComponentSkeletonBinder::registerFunctions(lua_State* L){
  LuaBinder binder(L);
  binder.init("ComponentSkeleton",0,componentSkeletonFunctions, bnd_DontDestroy);
  return 0;
}

int ComponentSkeletonBinder::bnd_DontDestroy(lua_State* L){
  return 0;
}


int ComponentSkeletonBinder::bnd_Instantiate(lua_State* L){
  LuaBinder binder(L);
  ComponentSkeleton* componentSkeleton = new ComponentSkeleton( lua_tostring(L,1), lua_tointeger(L,2) );
  binder.pushusertype(componentSkeleton,"ComponentSkeleton");
  return 1;
}

int ComponentSkeletonBinder::bnd_AddTo(lua_State* L){
  LuaBinder binder(L);
  ComponentSkeleton* componentSkeleton  = (ComponentSkeleton*) binder.checkusertype(1,"ComponentSkeleton");
  GameObject* gameObject = (GameObject*) binder.checkusertype(2,"GameObject");
  gameObject->AddComponent(componentSkeleton);
  return 1;
}

int ComponentSkeletonBinder::bnd_SetVisible(lua_State* L){
  LuaBinder binder(L);
  ComponentSkeleton* componentSkeleton  = (ComponentSkeleton*) binder.checkusertype(1,"ComponentSkeleton");
  componentSkeleton->SetVisible( ( lua_toboolean(L,2) != 0) );
  return 1;
}

int ComponentSkeletonBinder::bnd_WalkTo(lua_State* L){
  LuaBinder binder(L);
  irr::core::vector3df pos;

  ComponentSkeleton* componentSkeleton  = (ComponentSkeleton*) binder.checkusertype(1,"ComponentSkeleton");

  pos.X = (float) lua_tonumber(L,2);
  pos.Y = (float) lua_tonumber(L,3);
  pos.Z = (float) lua_tonumber(L,4);
  
  componentSkeleton->WalkTo( pos );

  return 1;
}

int ComponentSkeletonBinder::bnd_IsWalking(lua_State* L){
  LuaBinder binder(L);
  int walking;     
 
  ComponentSkeleton* componentSkeleton  = (ComponentSkeleton*) binder.checkusertype(1,"ComponentSkeleton");
  walking = componentSkeleton->IsWalking();

  binder.pushnumber(walking);

  return 1;
}

int ComponentSkeletonBinder::bnd_GetFrom(lua_State* L){
  LuaBinder binder(L); 
  GameObject* gameObject = GameObjectMap::Get(lua_tostring(L,1));
  binder.pushusertype(gameObject->GetComponent(CSKELETON),"ComponentSkeleton");
  return 1;  
}

int ComponentSkeletonBinder::bnd_SetPosition(lua_State* L){
  LuaBinder binder(L);
  ComponentSkeleton* componentSkeleton  = (ComponentSkeleton*) binder.checkusertype(1,"ComponentSkeleton");
  float posX = (float) lua_tonumber(L, 2);
  float posY = (float) lua_tonumber(L, 3);
  float posZ = (float) lua_tonumber(L, 4);
  componentSkeleton->SetPosition(core::vector3df(posX, posY, posZ));
  return 1;
}