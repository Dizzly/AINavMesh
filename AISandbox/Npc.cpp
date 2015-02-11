#include "Npc.h"
#include <assert.h>
#include "AIManager.h"
Npc::Npc() :auto_(this)
{
	id_=TheAIMan::Instance()->AddAI(this);
}

Npc::~Npc()
{

}

void Npc::Draw()
{

}

void Npc::Update()
{
	if(bTree_)
	{
	bTree_->Run();
	}
	auto_.Update();
}


void Npc::SetBehaviours(PTask& t)
{
bTree_=t;
}

int Npc::GetNPCID()const
{
return id_;
}