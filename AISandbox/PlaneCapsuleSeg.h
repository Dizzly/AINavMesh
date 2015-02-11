#ifndef PLANECAPSULESEG_H_INCLUDED
#define PLANECAPSULESEG_H_INCLUDED

#include "Capsule.h"
#include "Plane.h"


inline bool Intersects(const Capsule& c, const Plane& p)
{
	float sDist=abs(p.Distance(c.GetLine().GetStart()));
	float eDist=abs(p.Distance(c.GetLine().GetEnd()));


	if(sDist>0&&eDist<0)
	{
		return true;
	}
	else if(sDist<0&&eDist>0)
	{
		return true; 
	}
	//the radius doesnt matter, since the line is through the plane
	float rad=c.GetRad();
	if(rad>sDist||rad>eDist)
	{
		return true;
	}
	else
	{
		return false;
	}

}


#endif