#include "GameObjectManager.h"

int GameObjectManager::AddGameObject(pGameObject& p)
{
	gameObjects_[gameObjects_.size()]=p;
	return gameObjects_.size()-1;
}


pGameObject GameObjectManager::GetGameObject(int id)
{
	auto it=gameObjects_.find(id);
	if(it!=gameObjects_.end())
	{
		return gameObjects_[id];
	}
	return NULL;
}