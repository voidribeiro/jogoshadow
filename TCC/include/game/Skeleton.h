#ifndef _SKELETON_H_
#define _SKELETON_H_

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


#endif