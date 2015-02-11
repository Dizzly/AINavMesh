#ifndef ACCELERATION_MODELS_H_INCLUDED
#define ACCELERATION_MODELS_H_INCLUDED

#include "Vec3.h"
class EulerPhysics
{
public:
	void SetPos(const Vec3f& pos);
	Vec3f GetPos()const;

	void SetVel(const Vec3f& vel);
	Vec3f GetVel()const;

protected:
	Vec3f pos_;
	Vec3f vel_;
	Vec3f oldVel_;
};

class VerletPhysics
{
public:
	void SetPos(const Vec3f& pos);
	Vec3f GetPos()const;

protected:
	Vec3f pos_;
	Vec3f oldPos_;
	Vec3f acc_;
};

#endif