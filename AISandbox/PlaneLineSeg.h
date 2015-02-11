#ifndef PLANELINESEG_H_INCLUDED
#define PLANELINESEG_H_INCLUDED

#include "Plane.h"
#include "LineSegment.h"


inline bool Intersects(const LineSegment& ls, const Plane& p)
{
	float sDist=p.Distance(ls.GetStart());
	float eDist=p.Distance(ls.GetEnd());
	if(sDist>0&&eDist<0)
	{
		return true;
	}
	else if(sDist<0&&eDist>0)
	{
		return true;
	}
	return false;
}

#endif