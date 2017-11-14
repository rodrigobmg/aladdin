﻿#ifndef __ALADDIN_PHYSICS_PHYSICS_MARCOS_H__
#define __ALADDIN_PHYSICS_PHYSICS_MARCOS_H__

enum
{
  ALA_BODY_TYPE_DYNAMIC,
  ALA_BODY_TYPE_KINEMATIC,
  ALA_BODY_TYPE_STATIC
};

#ifndef GRAVITY_ACCELERATION 
#define GRAVITY_ACCELERATION Vec2 (0, -100.f)
#endif

#endif //!__ALADDIN_PHYSICS_PHYSICS_MARCOS_H__
