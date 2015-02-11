#pragma once
#include "Behaviour.h"

class BehaveAvoid: public Behaviour
{
public:
	BehaveAvoid(GameObject* p);
	virtual bool Update(SteeringData& d, float weight, GameObject* g=0)override;
	
protected:
	bool Update(SteeringData& d, float weight, const Vec3f& point);
private:
	float sqrdAvoidRad_;
};
typedef SmartPointer<BehaveAvoid> PBehaveAvoid;