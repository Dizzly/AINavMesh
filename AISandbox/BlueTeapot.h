#pragma once

#include"Npc.h"
#include "PhysicsTransform.h"
#include "Sphere.h"


class BlueTeapot:public Npc
{
public:
	BlueTeapot();
	~BlueTeapot();
	void SetTarget(pGameObject);
	virtual void Draw()override;
	virtual void Update()override;
private:
	Sphere s_;
};