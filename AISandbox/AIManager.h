#pragma once

#include "Singleton.h"
#include "NonCopyable.h"
#include "Npc.h"
#include <map>

class AIManager;
typedef Singleton<AIManager> TheAIMan;
class AIManager: public NonCopyable
{
public:
	int AddAI(Npc* np);
	Npc* GetNpc(int);
private:
	AIManager();
	friend TheAIMan;
private:
	typedef std::map<int,Npc*> NPCMap;
	NPCMap ai_;
};