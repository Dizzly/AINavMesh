#pragma once
#include "Behaviour.h"

class BehaveArrive:public Behaviour
{
public:
	BehaveArrive(GameObject* p);
	virtual bool Update(SteeringData& d, float weight, GameObject* g=0)override;

	float sqrdArrivedRad;
	float sqrdSlowRad;
protected:
	bool Update(SteeringData& d, float weight,const Vec3f& point);
};
typedef SmartPointer<BehaveArrive> PBehaveArrive;