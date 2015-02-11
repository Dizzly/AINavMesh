#include "BehaviourTree.h"
#include <algorithm>
// TASK FUNCTIONS
void Task::AddTask(PTask t)
{
	tasks_.push_back(t);
}
//END 

//SELECTOR FUNCTIONS
const char* Selector::TYPENAME="SELECTOR";

bool Selector::Run()
{
	for(auto it=tasks_.begin();
		it!=tasks_.end();
		++it)
	{
		if((*it)->Run())
		{
			return true;
		}
	}
	return false;
}

const char* Selector::GetTypename(){return TYPENAME;}
//END

//SEQUENCE FUNCTIONS
const char* Sequence::TYPENAME="SEQUENCE";

bool Sequence::Run()
{
	for(auto it=tasks_.begin();
		it!=tasks_.end();
		++it)
	{
		if(!(*it)->Run())
		{
			return false;
		}
	}
	return true;
}

const char* Sequence::GetTypename(){return TYPENAME;}
//END

//RANDOM SELECTOR FUNCS
const char* RandomSelector::TYPENAME="RAND_SELECTOR";

bool RandomSelector::Run()
{
	std::random_shuffle(tasks_.begin(),tasks_.end());
	for(auto it=tasks_.begin();
		it!=tasks_.end();
		++it)
	{
		if((*it)->Run())
		{
			return true;
		}
	}
	return false;
}

const char* RandomSelector::GetTypename(){return TYPENAME;}

//END

