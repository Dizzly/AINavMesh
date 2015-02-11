#pragma once
#include <vector>
#include "Vec3.h"
#include <gl/glut.h>
#include "PhysicsTransform.h"
#include "SteeringData.h"
#include "Behaviour.h"
#include "GameObject.h"

class Npc;

class Automator
{
public:
	typedef std::pair<PBehaviour,float> BehaviourWeight;
	typedef std::vector<BehaviourWeight> SteeringBehaviours;

public:
	Automator(Npc* p);
	~Automator();
	int AddBehaviour(PBehaviour b,float weight);
	Behaviour* GetBehaviour(int id);
	void Update();
	void SetTarget(pGameObject t);
	GameObject* GetTarget();
private:
	Npc* parent_;
	pGameObject target_;

	SteeringBehaviours beh_;
};
/*template <class T>
class Automator :public Npc
{
public:
	Automator(): s_(pos_.GetPos(),0.18)
	{
	int id=TheAIMan::Instance()->AddAI(this);
	TheCollMan::Instance()->AddCollisionAI(&s_,id);
	}
	~Automator()
	{}
	void SetPath(const std::list<int>* path,const Graph<T>* g)
	{
		sleep_=false;
		path_.clear();
		path_.insert(path_.end(),path->begin(),path->end());
		graph_=g;
		currNode_=0;
	}
	void Update(float speed)
	{
		if(sleep_)
		{return;}
		if(currNode_+1>=(int)path_.size())
		{return;}
		Vec3f to=graph_->GetNode(path_[currNode_+1]).GetPos()-pos_.GetPos();
		if(to.Length()<0.05)
		{
			++currNode_;
			if(currNode_>=(int)path_.size())
			{sleep_=true;}
			return;
		}

		Vec3f f=TheCollMan::Instance()->CheckWallCollisions(s_);
		//collect up all the AI vecs and move away from them

		to+=f;
		to.Normalise();
		SteeringData str;
		str.velocity=to*speed;
		pos_.Update(str);
		s_.SetPos(pos_.GetPos());
	}
	void Draw()
	{
		glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(pos_.GetPos().x,pos_.GetPos().y,pos_.GetPos().z);
		glutSolidSphere(0.1,10,10);
		glutSolidSphere(s_.GetRad(),10,10);
		glPopMatrix();
	}
	Vec3f GetPos(){return pos_.GetPos();}
private:
	bool sleep_;
	int currNode_;
	const Graph<T>* graph_;
	std::vector<int> path_;
	PhysicsTransform pos_;
	Sphere s_;
};*/

