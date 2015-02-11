#pragma once
#include "PhysicsTransform.h"
#include "SmartPointer.h"
class GameObject :public RefCounted
{
public:
	GameObject(){};
	virtual ~GameObject()=0{}
	virtual void Init(){}
	virtual void Update()=0{}
	virtual void Draw()=0{}
	virtual void Destroy(){}
		void SetID(int id){id_=id;}
	int GetID(){return id_;}
	PhysicsTransform<>* GetTransform(){return &transform_;}
protected:

	int id_;
	PhysicsTransform<> transform_;
};

typedef SmartPointer<GameObject> pGameObject;