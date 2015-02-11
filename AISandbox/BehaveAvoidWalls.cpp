#include "BehaveAvoidWalls.h"
#include "Sphere.h"
#include "CollisionManager.h"
#include "GameObject.h"
BehaveAvoidWalls::BehaveAvoidWalls(GameObject* g)
{
parent_=g;
}

bool BehaveAvoidWalls::Update(SteeringData& d, float weight, GameObject* target)
{
	Sphere s(parent_->GetTransform()->GetPos(),0.18f);
	Vec3f dir=TheCollMan::Instance()->CheckWallCollisions(s);
	d.velocity=dir*parent_->GetTransform()->GetMaxSpeed()*weight;
	return false;
}