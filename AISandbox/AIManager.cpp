#include "AIManager.h"

int AIManager::AddAI(Npc* np)
{
	ai_[ai_.size()]=np;
	return ai_.size()-1;
}

Npc* AIManager::GetNpc(int i)
{
	auto it=ai_.find(i);
	if(it!=ai_.end())
	{
	return it->second;
	}
	return NULL;
}

AIManager::AIManager()
{}