#pragma once
#include <vector>
#include "BehaviourTree.h"
#include "GameObject.h"
#include "Automator.h"

class Npc :public GameObject
{
public:
	Npc();
	virtual ~Npc();
	
	void Decide();
	void Draw()override;
	void Update()override;

	void SetBehaviours(PTask& t);
	int GetNPCID()const;
protected:
	int id_;
	Automator auto_;
	PTask bTree_;
};