#pragma once
#include "BehaveArrive.h"
#include "Path.h"

class BehaveFollowPath:public BehaveArrive
{
public:
	BehaveFollowPath(GameObject*,Path* p);
	bool Update(SteeringData& data, float weight, GameObject* g)override;
private:
	float predictTime_;
	Path* p_;
};
typedef SmartPointer<BehaveFollowPath> PBehaveFollowPath;