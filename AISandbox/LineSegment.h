#ifndef LINESEGMENT_H_INCLUDED
#define LINESEGMENT_H_INCLUDED
#include "Vec3.h"
class LineSegment
{
public:
	LineSegment();
	LineSegment(const Vec3f& start, const Vec3f& end):start_(start), end_(end){};
	Vec3f GetStart()const;
	Vec3f GetEnd()const;
	float TValFromPoint(Vec3f point)const;
	Vec3f PointFromTVal(float f)const;
	Vec3f ClosestPoint(Vec3f point)const;
	float SqrdDistance(Vec3f)const;
private:
	Vec3f start_,end_;
};

#endif