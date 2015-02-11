#include "BlueTeapot.h"

#include "BehaveAvoid.h"
#include "BehaveAvoidWalls.h"
#include "Level.h"


BlueTeapot::BlueTeapot()
{
	auto_.AddBehaviour(new BehaveAvoidWalls(this),0.4);
	auto_.AddBehaviour(new BehaveAvoid(this),0.15f);
	transform_.SetMaxSpeed(1.1f);
}

BlueTeapot::~BlueTeapot()
{

}

void BlueTeapot::SetTarget(pGameObject p)
{
auto_.SetTarget(p);
}

void BlueTeapot::Draw()
{
	glPushMatrix();
	glColor3f(0,0,1);
	glTranslatef(transform_.GetPos().x,transform_.GetPos().y,transform_.GetPos().z);
	glutSolidSphere(0.18,10,10);
	glPopMatrix();

}

void BlueTeapot::Update()
{
	Npc::Update();
	if(transform_.GetPos().y!=0)
	{
	transform_.SetPos(transform_.GetPos()*Vec3f(1,0,1));
	}
}