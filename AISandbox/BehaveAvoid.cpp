#include "BehaveAvoid.h"
#include "GameObject.h"

BehaveAvoid::BehaveAvoid(GameObject* p)
{
parent_=p;

sqrdAvoidRad_=0.8f;
}

bool BehaveAvoid::Update(SteeringData& d, float weight, GameObject* target)
{
	if(0==target)
	{return false;}
	float timeToSpeed=0.1f;
	Vec3f tPos = target->GetTransform()->GetPos();
	Vec3f pPos = parent_->GetTransform()->GetPos();


	
	float targetSpeed;
	Vec3f dir = pPos-tPos;
	float sqrdDist=dir.SqrLength();
	if(sqrdDist==0)
	{
		d.velocity=Vec3f(0,0,1);
		d.velocity*=weight;
		return true;
	}

	if(sqrdDist<sqrdAvoidRad_)
	{
		targetSpeed= 1- sqrdDist/sqrdAvoidRad_;
	}
	else
	{return false;}

	d.velocity=dir;
	d.velocity.SetLength(targetSpeed);
	d.velocity*=weight;

	return true;
}

bool BehaveAvoid::Update(SteeringData& d, float weight, const Vec3f& point)
{
	return false;
}