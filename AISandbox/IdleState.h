#pragma once

#include "AIState.h"

class IdleState :public AIState
{
public:
	virtual const char* GetName() const override;
	virtual void Update() override;
};