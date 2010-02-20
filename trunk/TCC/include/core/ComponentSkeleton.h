#ifndef _COMPONENTSKELETON_H_
#define _COMPONENTSKELETON_H_

#include "AbstractComponent.h"
#include "TextureManager.h"
#include "Skeleton.h"

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;


class ComponentSkeleton : public AbstractComponent{
  private:
    
    bool isVisible;

    IAnimatedMesh*          mesh;
	  IAnimatedMeshSceneNode* node;

 	  // speed variable
	  u32 speed;

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
	  f32 alpha, gamma;
	  f32 sinAlpha, sinGamma;
	  f32 sinAlphaTwo;
	  f32 cosAlpha;

	  // player velocity
	  core::vector3df skeletonVelocity;

    core::vector3df matrixRotation(core::vector3df rotation, core::vector3df vec);

    core::vector3df* destination;

  public:

	  // constructor
	  explicit ComponentSkeleton();

    // node = player scene node with bones
	  // setSpeed = how fast should the animation run
	  // caution: you should only take numbers between 2 and 50
    explicit ComponentSkeleton(const std::string filename, const u32 speed=8);

	  // destructor
	  virtual ~ComponentSkeleton();

	  // set the type of animation
	  void setAnimType(CSK_ANIM setAnimType);

	  // get the current animation type
    CSK_ANIM getAnimType() const{ return animType; }

	  // animates the skeleton
	  void animSkeleton();

	  // returns skeleton scene node
	  scene::IAnimatedMeshSceneNode *getSkeletonSceneNode();

	  // returns motion variable
	  u32 getMotionVariable();

    // return the second motion variable
    u32 getSecondMotionVariable();

	  // return player velocity
    core::vector3df getSkeletonVelocity() const{return skeletonVelocity;}

    virtual void Update();
    virtual void Draw();

    void WalkTo(vector3df pos);
    
    int GetType() { return CSKELETON; };
    const char* GetTypeName() { return "ComponentSkeleton"; };
    void SetVisible(bool visible){ isVisible = visible; }
  
    int IsWalking();

};

class ComponentSkeletonBinder{
  public:
    static int registerFunctions(lua_State* L);
    static int bnd_Instantiate (lua_State* L);
    static int bnd_DontDestroy (lua_State* L);
    static int bnd_AddTo (lua_State* L);
    static int bnd_SetVisible (lua_State* L);
    static int bnd_WalkTo (lua_State* L);
    static int bnd_IsWalking (lua_State* L);
    static int bnd_GetFrom (lua_State* L);
};

static const luaL_reg componentSkeletonFunctions[] = {
    {"Instantiate", ComponentSkeletonBinder::bnd_Instantiate},
    {"AddTo", ComponentSkeletonBinder::bnd_AddTo},
    {"SetVisible", ComponentSkeletonBinder::bnd_SetVisible},
    {"WalkTo", ComponentSkeletonBinder::bnd_WalkTo},
    {"IsWalking", ComponentSkeletonBinder::bnd_IsWalking},
    {"GetFrom", ComponentSkeletonBinder::bnd_GetFrom},
    {NULL, NULL}
};

 
#endif 