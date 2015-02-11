#include "BehaveArrive.h"
#include "GameObject.h"

BehaveArrive::BehaveArrive(GameObject* g)
{
parent_=g;

sqrdArrivedRad=0.1f*0.1f;
sqrdSlowRad=0.8f;
}

bool BehaveArrive::Update(SteeringData& d, float weight, GameObject* target)
{
	if(target==0)
	{return false;}
	float timeToSpeed=0.1f;
	Vec3f tPos=target->GetTransform()->GetPos();
	Vec3f pPos=parent_->GetTransform()->GetPos();

	float targetSpeed;

	Vec3f dir= tPos-pPos;
	float sqrdDist=dir.SqrLength();

	if(sqrdDist<sqrdArrivedRad)
	{
		return false;
	}

	if(sqrdDist>sqrdSlowRad)
	{
		targetSpeed=1;
	}
	else
	{
		targetSpeed = 1* sqrdDist/sqrdSlowRad;
	}
	
	d.velocity=dir;
	d.velocity.SetLength(targetSpeed);
	d.velocity*=weight;

	return true;
}

bool BehaveArrive::Update(SteeringData& d, float weight,const Vec3f& point)
{
	float timeToSpeed=0.1f;
	Vec3f pPos=parent_->GetTransform()->GetPos();

	float targetSpeed;

	Vec3f dir= point-pPos;
	float sqrdDist=dir.SqrLength();

	if(sqrdDist<sqrdArrivedRad)
	{
		return false;
	}

	if(sqrdDist>sqrdSlowRad)
	{
		targetSpeed=1;
	}
	else
	{
		targetSpeed = 1* sqrdDist/sqrdSlowRad;
	}
	
	d.velocity=dir;
	d.velocity.SetLength(targetSpeed);
	d.velocity*=weight;

	return false;
}