#include "CollisionManager.h"

CollisionManager::CollisionManager()
{}

void CollisionManager::AddCollisionWall(LineSegment& line, Vec3f norm)
{
	walls_.push_back(std::make_pair(line,norm));
}
//adds an AI's collider and ID as 
void CollisionManager::AddCollisionAI(Sphere* s, int id)
{
	ai_.push_back(std::make_pair(s,id));
}
//returns the average normals of any walls colliding with this sphere
Vec3f CollisionManager::CheckWallCollisions(Sphere& collSphere)
{
	Vec3f avNorms;
	for(auto it=walls_.begin();it!=walls_.end();++it)
	{
		float sqrdDist=it->first.SqrdDistance(collSphere.GetPos());
		if(sqrdDist<
			collSphere.GetRad()*collSphere.GetRad())
		{
			
			avNorms+=it->second*sqrt(sqrdDist);
		}
	}
	if(avNorms!=Vec3f())
	{
		avNorms.Normalise();
	}
	return avNorms;
}
//returns the IDs of all AI's colliding with sphere
std::vector<int> CollisionManager::CheckAICollisions(Sphere& collSphere)
{
	std::vector<int> ids;
	for(auto it=ai_.begin(); it!=ai_.end();++it)
	{
		// this is a lazy method of ensuring self collision is not fully tested
		// due to floating point accuracy it is unlikely that any other spheres
		// will have the exact same position
		if(it->first->GetPos()!=collSphere.GetPos()&&it->first->Intersects(collSphere))
		{
			ids.push_back(it->second);
		}
	}
	return ids;
}