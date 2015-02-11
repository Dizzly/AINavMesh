#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED
#include "Vec3.h"
struct Transform
{
	Transform(Vec3f& posA, Vec3f& rotA, Vec3f& scaleA):pos(posA),rot(rotA),scale(scaleA){};
	Transform(){scale=Vec3f(1,1,1);};
	Vec3f pos;
	Vec3f rot;
	Vec3f scale;
};

#endif