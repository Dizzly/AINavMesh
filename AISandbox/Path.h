#pragma once

#include "Vec3.h"
#include <vector>
class Path
{
public:
	typedef std::vector<Vec3f> PosVec;
public:
	Path();
	Path(const PosVec&);
	void SetPath(const PosVec&);

	Vec3f GetPointFromProgress(float f=-1);
	Vec3f ClosestPointOnPath(Vec3f point);
	float GetProgressFromPoint(Vec3f point);
	void SetProgress(float);

	PosVec& GetPath();
private:
	PosVec path_;
	float progress_;
};