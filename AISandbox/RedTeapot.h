#pragma once
#include "Npc.h"
#include "PhysicsTransform.h"
#include "Sphere.h"
#include "Path.h"
#include "NavMesh.h"
class RedTeapot:public Npc
{
public:
	RedTeapot();
	~RedTeapot();
	void SetTarget(pGameObject);
	virtual void Draw()override;
	virtual void Update()override;
private:
	NavMeshAStarSearch search_;
	Path p_;
	Sphere s_;
};