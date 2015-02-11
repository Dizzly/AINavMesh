#ifndef CAPSULE_H_INCLUDED
#define CAPSULE_H_INCLUDED

#include "LineSegment.h"
#include "Sphere.h"
class Capsule
{
public:
	Capsule(Sphere& s, Vec3f endLoc);
	Capsule(LineSegment& l, float radius);
	Capsule(Vec3f& start, Vec3f& end, float radius);
	bool Intersects(const Sphere& s)const;
	LineSegment GetLine()const;
	float GetRad()const;
private:
	LineSegment middle_;
	float radius_;
};

#endif