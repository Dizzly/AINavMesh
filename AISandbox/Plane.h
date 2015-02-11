#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED
#include "Vec3.h"

enum PointType {INFRONT_PLANE, BEHIND_PLANE, ON_PLANE};

class Plane
{
public:
	Plane();
	Plane(Vec3f& normal,float);
	Plane(Vec3f& axisA, Vec3f& axisB,float);
	Plane(Vec3f& pointA, Vec3f& pointB, Vec3f& pointC);
	bool OnPlane(const Vec3f& point)const;
	void Normalise();
	float Distance(const Vec3f& point)const;
	PointType ClassifyPoint(const Vec3f& q)const;
private:
	Vec3f normal_;
	float d_;
};


#endif