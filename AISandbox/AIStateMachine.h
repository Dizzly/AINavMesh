#pragma once
#include "SmartPointer.h"



class Transition
{

}

class AIStateMachine;
typedef SmartPointer<AIStateMachine> pAIState;

class AIStateMachine :public RefCounted
{
public:
	void OnActive();
	void OnInActive();
	void Update();
	
private:
	pAIState currentState_;

}