#pragma once

#include "NonCopyable.h"
#include "Singleton.h"
#include "LineSegment.h"
#include "Sphere.h"

#include <map>
#include <vector>



class CollisionManager;
typedef Singleton<CollisionManager> TheCollMan;
class CollisionManager: public NonCopyable
{

public:
	enum COLLIDER_TYPE{NULL_TYPE=0,WALL_TYPE,AI_TYPE,ALL_TYPE};
private:
	typedef std::pair<Sphere*,int> AIColID;
	typedef std::pair<LineSegment,Vec3f> WallLineNorm;
public:
	typedef std::vector<WallLineNorm> WallVec;
	typedef std::vector<AIColID> AIVec;
public:
	//adds to the wall vec
	void AddCollisionWall(LineSegment& line, Vec3f norm);
	//adds an AI's collider and ID as 
	void AddCollisionAI(Sphere*, int id);
	//returns the average normals of any walls colliding with this sphere
	Vec3f CheckWallCollisions(Sphere& collSphere);
	//returns the IDs of all AI's colliding with sphere
	std::vector<int> CheckAICollisions(Sphere& collSphere);
private:
	CollisionManager();
	friend TheCollMan;
private:
	WallVec walls_;
	AIVec ai_;
};