#include "Path.h"
#include <assert.h>
#include "LineSegment.h"

Path::Path()
{
	progress_=-1;
}

Path::Path(const PosVec& v)
{
	path_=v;
	progress_=-1;
}

void Path::SetPath(const PosVec& p)
{
path_=p;
progress_=-1;
}

Path::PosVec& Path::GetPath()
{
return path_;
}

Vec3f Path::GetPointFromProgress(float f)
{
	if(f+1>path_.size())
	{
	return path_.back();
	}
	//get the integer section of the progress
	//eg the number of nodes passed
	int intProg;
	float fracProg;
	if(-1==f)
	{
		intProg=(int)progress_;
		fracProg=progress_-intProg;
	}
	else
	{
		intProg=(int)f;
		fracProg=f-intProg;
	}
	assert(intProg+1<(int)path_.size());
	Vec3f start=path_[intProg];
	Vec3f end=path_[intProg+1];
	assert(fracProg<1);
	Vec3f progressPoint = start+((end-start)*fracProg);
	return progressPoint;
}

Vec3f Path::ClosestPointOnPath(Vec3f point)
{
	if(path_.size()==1)
	{
	return path_[0];
	}
	int i=0;
	if(-1!=progress_)
	{
		i=(int)progress_;
	}
	float min=10000.0f;
	int line=-1;
	for(;i<(int)path_.size()-1;++i)
	{
		LineSegment l(path_[i],path_[i+1]);
		float sqrdDist=l.SqrdDistance(point);
		if(sqrdDist<min)
		{
			min=sqrdDist;
			line=i;
		}
	}
	assert(line!=-1);
	return LineSegment(path_[line],path_[line+1]).ClosestPoint(point);
}

float Path::GetProgressFromPoint(Vec3f point)
{
	if(path_.size()==1)
	{
		return 0.0f;
	}
	int i=0;
	if(-1!=progress_)
	{
		i=(int)progress_;
	}
	float min=10000.0f;
	int intProg=-1;
	float fracProg=-1.0f;
	for(;i<(int)path_.size()-1;++i)
	{
		LineSegment l(path_[i],path_[i+1]);
		float sqrdDist=l.SqrdDistance(point);
		if(sqrdDist<min)
		{
			intProg=i;
			fracProg=l.TValFromPoint(point);
			min=sqrdDist;
		}
	}
	return fracProg+intProg;
}

