#pragma once
#include "Behaviour.h"

class BehaveAvoidWalls:public Behaviour
{
public:
	BehaveAvoidWalls(GameObject* g);
	bool Update(SteeringData& d, float weight, GameObject* g)override;
private:
};
typedef SmartPointer<BehaveAvoidWalls> PBehaveAvoidWalls;