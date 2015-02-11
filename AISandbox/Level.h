#pragma once
#include "Singleton.h"
#include "NonCopyable.h"
#include "NavMesh.h"

class Level;
typedef Singleton<Level> TheLevel;
class Level: public NonCopyable
{
public:
	NavMesh& GetMesh();
private:
	Level();
	friend TheLevel;
private:
	NavMesh mesh_;
};