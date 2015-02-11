#include "RedTeapot.h"
#include "IdleState.h"
#include <gl/glut.h>
#include "CollisionManager.h"
#include "BehaveArrive.h"
#include "BehaveAvoidWalls.h"
#include "BehaveFollowPath.h"
#include "Level.h"
#include "OpenGLGraphDrawAlgorithms.h"

int g_oldTri=0;
int g_lastRobotID=0;


RedTeapot::RedTeapot()
{
	auto_.AddBehaviour(new BehaveAvoidWalls(this),0.1);
	auto_.AddBehaviour(new BehaveFollowPath(this,&p_),0.3);

	search_.Init(TheLevel::Instance()->GetMesh().GetGraph(),1,1);
	transform_.SetMaxSpeed(1.0f);
}

RedTeapot::~RedTeapot()
{}

void RedTeapot::SetTarget(pGameObject p)
{
	auto_.SetTarget(p);
}

void RedTeapot::Draw()
{
	glPushMatrix();
	glTranslatef(transform_.GetPos().x,transform_.GetPos().y,transform_.GetPos().z);
	glutSolidSphere(0.18,10,10);
	
	glPopMatrix();
	DrawPath(p_.GetPath());
}

void RedTeapot::Update()
{
	int triId=-1;
	triId=TheLevel::Instance()->GetMesh().PositionOnMesh(auto_.GetTarget()->
		GetTransform()->GetPos());

	if(triId!=g_oldTri&&triId!=0)
	{
		int robotID=TheLevel::Instance()->GetMesh().PositionOnMesh(transform_.GetPos());
		if(robotID!=0)
		{
		g_lastRobotID=robotID;
		}
		else
		{
		robotID=g_lastRobotID;
		}
		search_.Search(TheLevel::Instance()->GetMesh().GetGraph(),robotID,triId,1000);
		p_.SetPath(search_.GetPath());
		TheLevel::Instance()->GetMesh().OptimisePath(p_.GetPath());
	}
	g_oldTri=triId;
	

	Npc::Update();
}