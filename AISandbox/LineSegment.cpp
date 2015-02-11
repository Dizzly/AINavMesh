#include"LineSegment.h"
#include <assert.h>
LineSegment::LineSegment()
{
}
float LineSegment::SqrdDistance(Vec3f vec)const
{
	Vec3f m(end_-start_);
	Vec3f q=vec-start_;
	float mDotm=m.Dot(m);
	if(mDotm==0)
	{
		return q.SqrLength();
	}
	float f=m.Dot(q)/m.Dot(m);
	if(f<0)
	{
		return q.Length();
	}
	else if(f>1.0f)
	{
		return (vec-end_).Length();
	}
	else
	{
		return (vec-(start_+(m*f))).SqrLength();
	}
}

float LineSegment::TValFromPoint(Vec3f point)const
{
	Vec3f m(end_-start_);
	Vec3f q=point-start_;
	float mDotm =m.Dot(m);

	if(mDotm==0)
	{
		return 0;
	}
	float t=m.Dot(q)/mDotm;
	if(t<0)
	{return 0;}
	if(t>1)
	{return 1;}
	return t;
}

Vec3f LineSegment::PointFromTVal(float t)const
{
	if(t<0)
	{return start_;}
	if(t>1)
	{return end_;}

	return start_+(end_-start_)*t;
}

Vec3f LineSegment::GetStart()const
{
	return start_;
}

Vec3f LineSegment::GetEnd()const
{
	return end_;
}

Vec3f LineSegment::ClosestPoint(Vec3f point)const
{
	Vec3f m(end_-start_);
	Vec3f q=point-start_;
	float mDotm =m.Dot(m);

	if(mDotm==0)
	{
		return start_;
	}
	float t=m.Dot(q)/mDotm;
	if(t<0)
	{
		return start_;
	}
	else if(t>1.0f)
	{
		return end_;
	}
	else
	{
		return start_+(m*t);
	}
}