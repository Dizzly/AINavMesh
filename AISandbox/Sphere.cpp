#include "Sphere.h"

Sphere::Sphere()
{
	radius_=0;
}
Sphere::Sphere(const Vec3f& pos, float radius)
{
	pos_=pos;
	radius_=radius;
}

Vec3f Sphere::GetPos()const
{
	return pos_;
}

float Sphere::GetRad()const
{
	return radius_;
}

void Sphere::SetPos(const Vec3f& pos)
{
	pos_=pos;
}

void Sphere::SetRad(float rad)
{
	radius_=rad;
}

bool Sphere::Intersects(const Sphere& s)const
{
	Vec3f vec=s.GetPos()-pos_;
	float sqrRadSum=(radius_+s.GetRad())*(radius_+s.GetRad());
	return sqrRadSum>=vec.SqrLength();
}
