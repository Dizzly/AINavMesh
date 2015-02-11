#pragma once

#include "SteeringData.h"
#include "SmartPointer.h"
class GameObject;
//the pure vritaul implementation of a abstract of behaviour
//takes steering behaviour in its update function


class Behaviour :public RefCounted
{
public:
	virtual bool Update(SteeringData& data, float weight, GameObject* g=0)=0{}
protected:
	GameObject* parent_;
};

typedef SmartPointer<Behaviour> PBehaviour;