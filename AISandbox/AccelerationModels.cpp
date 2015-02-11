#include "AccelerationModels.h"


Vec3f EulerPhysics::GetPos()const
{return pos_;}

Vec3f EulerPhysics::GetVel()const
{return vel_;}

void EulerPhysics::SetPos(const Vec3f& pos)
{pos_=pos;}

void EulerPhysics::SetVel(const Vec3f& vel)
{vel_=vel;}

void VerletPhysics::SetPos(const Vec3f& pos)
{
Vec3f diff=pos-pos_;
pos_+=diff;
oldPos_+=diff;
}

Vec3f VerletPhysics::GetPos()const
{
	return pos_;
}