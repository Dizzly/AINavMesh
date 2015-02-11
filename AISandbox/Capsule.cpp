#include "Capsule.h"

Capsule::Capsule(Sphere& s, Vec3f end): middle_(s.GetPos(),end)
{
	radius_=s.GetRad();
}

Capsule::Capsule(LineSegment& l, float radius):middle_(l)
{
	radius_=radius;
}

Capsule::Capsule(Vec3f& start, Vec3f& end, float rad):middle_(start,end)
{
	radius_=rad;
}

bool Capsule::Intersects(const Sphere& s)const
{
	float sqrDist = middle_.SqrdDistance(s.GetPos());
	float sumR= radius_+s.GetRad();
	float sumRSq = sumR*sumR;

	return sqrDist<=sumRSq;
}

LineSegment Capsule::GetLine()const
{
	return middle_;
}

float Capsule::GetRad()const
{
	return radius_;
}
