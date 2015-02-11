#pragma once
#include "Singleton.h"
#include "NonCopyable.h"
#include "GameObject.h"
#include <map>
class GameObjectManager;
typedef Singleton<GameObjectManager> TheGameObjectMan;
class GameObjectManager: public NonCopyable
{
public:
	int AddGameObject(pGameObject& p);
	pGameObject GetGameObject(int );
private:
	GameObjectManager();
	friend TheGameObjectMan;
private:
	std::map<int,pGameObject> gameObjects_;
};
