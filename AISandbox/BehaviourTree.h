#pragma once
#include <vector>
#include "SmartPointer.h"

//make a factory for these classes

class Task;

typedef SmartPointer<Task> PTask;
typedef std::vector<PTask> PTaskVec;
//a behaviour tree inspired from Artifical Intelligence for Games
class Task :public RefCounted
{
public:
	virtual bool Run()=0{return false;}
	void AddTask(PTask t);
	virtual const char* GetTypename()=0{}
protected:
	PTaskVec tasks_;
};

class Selector:public Task
{
public:
	bool Run()override;
	const char* GetTypename()override;
	static const char* TYPENAME;
};

class RandomSelector:public Task
{
public:
	bool Run()override;
	const char* GetTypename()override;
	static const char* TYPENAME;
};

class Sequence:public Task
{
public:
	bool Run()override;
	const char* GetTypename()override;
	static const char* TYPENAME;
};

/// the implementation of a decision tree
