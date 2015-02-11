#include "IdleState.h"
#include "Npc.h"
#include "TextToSpeech.h"
#include "RedTeapot.h"
#include "SteeringData.h"
const char* IdleState::GetName()const
{
	return "IdleState";
}

void IdleState::Update()
{
	AIState::Update();
	if(time_>5)
	{
		return;
	}
	SteeringData data;
	data.velocity=Vec3f(0.01f,0,0);
	RedTeapot* t=dynamic_cast<RedTeapot*>(npc_);
	if(t)
	{
		t->GetTransform()->AddSteeringData(data);
		t->GetTransform()->Update();
	}
}