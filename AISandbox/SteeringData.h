#pragma once
#include "Vec3.h"

struct SteeringData
{
	SteeringData();
	SteeringData(const Vec3f& vel, float ang);
	void operator +=(const SteeringData&);
	Vec3f velocity;
	float angular;
};