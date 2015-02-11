#include "Player.h"
#include <gl/glut.h>
Player::Player()
{}

Player::~Player()
{}

void Player::Draw()
{
	glPushMatrix();
	glTranslatef(transform_.GetPos().x,
		transform_.GetPos().y
		,transform_.GetPos().z);
	glutSolidCube(0.3);
	glPopMatrix();
}

void Player::Update()
{
transform_.Update();
}
