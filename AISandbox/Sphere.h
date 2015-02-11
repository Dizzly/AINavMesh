#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED
#include "Vec3.h"
class Sphere
{

public:
	Sphere(const Vec3f& pos, float rad);
	Sphere();
	Vec3f GetPos()const;
	float GetRad()const;
	void SetPos(const Vec3f& a_pos);
	void SetRad(float a_rad);
	bool Intersects(const Sphere& s)const;
private:
	Vec3f pos_;
	float radius_;
};

#endif