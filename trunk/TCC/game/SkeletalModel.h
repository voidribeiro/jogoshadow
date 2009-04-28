#ifndef _SKELETALMODEL_H_
#define _SKELETALMODEL_H_

#include "../include/irrlicht.h"
#include "../core/BMaths.h"
#include "Model.h"

using namespace irr;
using namespace scene;
using namespace video;

// enumeration for animation types
enum CSK_ANIM {
	CSK_ANIM_STAND,
	CSK_ANIM_WALK,
	CSK_ANIM_RUN,
	CSK_ANIM_JUMP,
	CSK_ANIM_BACKWARD,
	CSK_ANIM_STRAFELEFT,
	CSK_ANIM_STRAFERIGHT,

	CSK_ANIM_COUNT
};

class SkeletalModel : public Model{
public:

	// constructor
	SkeletalModel();

  // node = player scene node with bones
	// setSpeed = how fast should the animation run
	// caution: you should only take numbers between 2 and 50
  SkeletalModel(int id, int modelType, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node, u32 setSpeed=12);

	// destructor
	~SkeletalModel();

	// set the type of animation
	void setAnimType(CSK_ANIM setAnimType);

	// get the current animation type
	CSK_ANIM getAnimType() const;

	// animates the skeleton
	void animSkeleton(core::position2di mousePos);

	// returns skeleton scene node
	scene::IAnimatedMeshSceneNode *getSkeletonSceneNode();

	// returns motion variable
	u32 getMotionVariable();

	// return the second motion variable
	u32 getSecondMotionVariable();

	// return player velocity
	core::vector3df getSkeletonVelocity() const;


private:

	scene::IAnimatedMeshSceneNode *skeletonNode;

	core::array<core::vector3df> bonesOsci;
	core::array<core::vector3df> bonesOsciPos;

	void animWalk();
	void animRun();
	void animStand();
	void animJump();
	void animBackward();
	void animStrafeLeft();
	void animStrafeRight();

	void animHead(core::position2di pos);

  void init(scene::IAnimatedMeshSceneNode *node, u32 setSpeed);

	void animInterpolation();
	bool enableInterpolation;
	u32 interpolationCount;

	CSK_ANIM animType;
	CSK_ANIM lastAnimType;

	// storing bone names
	core::array<irr::c8*> boneName;
	// storing bone scene nodes
	core::array<scene::IBoneSceneNode*> bones;
	// storing bone rotations for stand position
	core::array<core::vector3df> bonesRot;
	// storing bone positions
	core::array<core::vector3df> bonesPos;

	// motion variable
	u32 i,k,a,b,c;
	u32 kTemp;

	// oscillation functions
	f32 alpha,gamma;
	f32 sinAlpha,sinGamma;
	f32 sinAlphaTwo;
	f32 cosAlpha;

	// speed variable
	u32 speed;

	// player velocity
	core::vector3df skeletonVelocity;

	enum SKT_BONE {

		// main items
		SKT_BONE_TORSO,
		SKT_BONE_STOMACH,
		SKT_BONE_BODY,
		SKT_BONE_NECK,
		SKT_BONE_HEAD,

		// right arm items
		SKT_BONE_ARM_R,
		SKT_BONE_UARM_R,
		SKT_BONE_HAND_R,
		SKT_BONE_FINGER_R,

		// left arm items
		SKT_BONE_ARM_L,
		SKT_BONE_UARM_L,
		SKT_BONE_HAND_L,
		SKT_BONE_FINGER_L,

		// right leg items
		SKT_BONE_LEG_R,
		SKT_BONE_SHIN_R,
		SKT_BONE_FEET_R,
		SKT_BONE_TOES_R,

		// left leg items
		SKT_BONE_LEG_L,
		SKT_BONE_SHIN_L,
		SKT_BONE_FEET_L,
		SKT_BONE_TOES_L,

		// number of bones
		SKT_BONE_COUNT
	};


};

#endif