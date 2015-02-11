#pragma once
#include "GameObject.h"

class Player:public GameObject
{
public:
	Player();
	~Player();
	virtual void Draw()override;
	virtual void Update()override;
};
typedef SmartPointer<Player> pPlayer;