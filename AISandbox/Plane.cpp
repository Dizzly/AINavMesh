#include "Plane.h"

Plane::Plane()
{
d_=0;
}

Plane::Plane(Vec3f& normal,float d)
{
normal_=normal;
d_=d;
}

Plane::Plane(Vec3f& axisA, Vec3f& axisB,float d)
{
normal_=axisA.Cross(axisB);
d_=d;
}

Plane::Plane(Vec3f& pointA, Vec3f& pointB, Vec3f& pointC)
{
	normal_=(pointB-pointA).Cross(pointC-pointA);
	normal_.Normalise();
	d_=normal_.Dot(pointC);
}

void Plane::Normalise()
{
	float div=1.0f/normal_.Length();
	normal_*=div;
	d_*=div;
}

float Plane::Distance(const Vec3f& point)const
{
	return point.Dot(normal_)-d_;
}

PointType Plane::ClassifyPoint(const Vec3f& q)const
{
	float f=Distance(q);
	if(f>0)
	{
		return INFRONT_PLANE;
	}
	else if(f<0)
	{
		return BEHIND_PLANE;
	}
	else
	{
		return ON_PLANE;
	}
}



bool Plane::OnPlane(const Vec3f& point)const
{
	if(point.Dot(normal_)==d_)
	{
		return true;
	}	
	return false;
}