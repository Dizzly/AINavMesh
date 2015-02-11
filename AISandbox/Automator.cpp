#include "Automator.h"
#include "Npc.h"

Automator::Automator(Npc* p): parent_(p), target_(nullptr)
{
}

Automator::~Automator()
{}

int Automator::AddBehaviour(PBehaviour b, float w)
{

	beh_.push_back(std::make_pair(b,w));
	return beh_.size()-1;
}

Behaviour* Automator::GetBehaviour(int i)
{
	return beh_[i].first;
}

void Automator::Update()
{
	SteeringData total;

	for (auto it=beh_.begin();it!=beh_.end();++it)
	{
		SteeringData dat;
		it->first->Update(dat,it->second,target_);
		total+=dat;
	}
	parent_->GetTransform()->AddSteeringData(total);
	parent_->GetTransform()->Update();
}

GameObject* Automator::GetTarget()
{
return target_;
}


void Automator::SetTarget(pGameObject t)
{
	target_=t;
}