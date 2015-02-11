#include "BehaveFollowPath.h"
#include "GameObject.h"
BehaveFollowPath::BehaveFollowPath(GameObject* g,Path* p) :BehaveArrive(g)
{
predictTime_=0.1f;
p_=p;
sqrdSlowRad=0.8*0.8f;
}
bool BehaveFollowPath::Update(SteeringData& data, float weight, GameObject* g)
{
	if(p_->GetPath().size()<2)
	{return false;}
	float pathOffset=0.5f;
	Vec3f pos=parent_->GetTransform()->GetPos();

	float pathPos=p_->GetProgressFromPoint(pos);
	//possible problems when reaching end of path.
	pathPos+=pathOffset;
	Vec3f target=p_->GetPointFromProgress(pathPos);
	return BehaveArrive::Update(data,weight,target);
}