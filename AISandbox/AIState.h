#pragma once
#include "SmartPointer.h"
#include <string>

class Npc;
class GameObject;

class AIState:public RefCounted
{
public:
	AIState():npc_(NULL),target_(NULL),time_(0),rank_(0){}
	virtual ~AIState()=0{};

	virtual void Update()=0{time_+=0.1f;}//need an actual timer here for real time.

	virtual void OnActive(){time_=0;}
	virtual void OnInactive(){};

	virtual float GetRank(){return rank_;}

	virtual const char* GetName()const=0{};

	virtual void SetNPC(Npc& npc){
		npc_=&npc;
	}
	virtual void SetTarget(GameObject& obj){target_=&obj;}
protected:
	Npc * npc_;
	GameObject* target_;
	float time_;
	float rank_;
};

typedef SmartPointer<AIState> pAIState;