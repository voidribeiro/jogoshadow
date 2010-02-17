#ifndef _SKELETALMODEL_H_
#define _SKELETALMODEL_H_

/*

Skeletal human animation class

Created 2007 (modified 2008) for 3d skeletal model animations 
By "xray" on Irrlicht forums

*/

#include "irrlicht.h"
#include "Model.h"
#include "Skeleton.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;

class SkeletalModel : public Model{
public:

	// constructor
	explicit SkeletalModel();

  // node = player scene node with bones
	// setSpeed = how fast should the animation run
	// caution: you should only take numbers between 2 and 50
  explicit SkeletalModel(const int id, IAnimatedMesh* mesh, IAnimatedMeshSceneNode* node, const u32 setSpeed=12);

	// destructor
	virtual ~SkeletalModel();

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

  core::vector3df matrixRotation(core::vector3df rotation, core::vector3df vec);

private:
  IAnimatedMesh*          mesh;
	IAnimatedMeshSceneNode* skeletonNode;

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

};

#endif