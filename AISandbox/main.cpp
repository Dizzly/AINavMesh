#include <time.h>
#include <random>
#include <iostream>


#include <gl/glut.h>

#include "AngleConvert.h"

#include "AIState.h"
#include "RedTeapot.h"
#include "BlueTeapot.h"

#include "NavMesh.h"
#include "OpenGLGraphDrawAlgorithms.h"
#include "Octree.h"
#include "Automator.h"
#include "IntersectionFuncs.h"

#include "CollisionManager.h"
#include "GlutTimer.h"
#include "Player.h"

#include "Level.h"
#undef main

static NavMeshAStarSearch g_search;
static std::list<int> g_path;

static bool g_paused=false;
static float g_rot=0;


static pPlayer g_player;
static RedTeapot g_myNpc;
static BlueTeapot* g_runAway;
static BlueTeapot* g_runAway2;
static BlueTeapot* g_runAway3;

char* getMAC();

static enum DRAW_STATES{POLY_DRAW=0,GRAPH_DRAW,ENDOF_DRAW};
static int g_state=GRAPH_DRAW;


Vec3f g_pos;
bool g_optimize =true;
void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.4277777777777777777, 1.0, 1000.0);

	float x=sin(DegToRad(g_rot));
	float z=cos(DegToRad(g_rot));
	x*=10;
	z*=10;
	g_pos=g_player->GetTransform()->GetPos();
	gluLookAt(g_pos.x,10,g_pos.z,
		g_pos.x,0,g_pos.z,
		0,0,1);

	if(g_state==POLY_DRAW)
	{
		glColor3f(1,1,1);
		TheLevel::Instance()->GetMesh().DebugDraw();
		DrawGraph<NavTriangle>(TheLevel::Instance()->GetMesh().GetGraph(),NULL,true);
	}
	if(g_state==GRAPH_DRAW)
	{
		glColor3f(1,1,1);
		TheLevel::Instance()->GetMesh().DebugDraw();
	}



	glColor3f(1,0,0);
	if(!g_paused)
	g_myNpc.Update();

	g_myNpc.Draw();
		if(!g_paused)
	g_player->Update();

	g_player->Draw();
		if(!g_paused)
	g_runAway->Update();

	g_runAway->Draw();
		if(!g_paused)
	g_runAway2->Update();

	g_runAway2->Draw();
		if(!g_paused)
	g_runAway3->Update();

	g_runAway3->Draw();


	glColor3f(1,1,1);
	TheGlutTimer::Instance()->Upadate();

	glutSwapBuffers();
	glutPostRedisplay();
}


void KeyboardFunc(unsigned char key, int x, int y)
{
	if(key==' ')
	{
		g_state+=1;
		if(g_state==ENDOF_DRAW)
		{
			g_state=POLY_DRAW;
		}
	}
	if(key==27)
	{
		exit(0);
	}
	if(key=='e'||key=='E')
	{
		g_myNpc.GetTransform()->SetPos(g_player->GetTransform()->GetPos());
	}
	if(key=='w'||key=='W')
	{
		g_player->GetTransform()->AddForce(Vec3f(0,0,1));
	}
	if(key=='s'||key=='S')
	{
		g_player->GetTransform()->AddForce(Vec3f(0,0,-1));
	}
	if(key=='a'||key=='A')
	{
		g_player->GetTransform()->AddForce(Vec3f(1,0,0));
	}
	if(key=='d'||key=='D')
	{
		g_player->GetTransform()->AddForce(Vec3f(-1,0,0));
	}
	if(key=='q'||key=='q')
	{
		g_paused=!g_paused;
	}
}

void SpecialFunc(int key, int x, int y)
{

	if(key==GLUT_KEY_LEFT)
	{
		g_rot+=2;
	}
	if(key==GLUT_KEY_RIGHT)
	{
		g_rot-=2;
	}
}


void MouseMotion(int button,int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		double startX, startY, startZ;
		double model[16];
		double proj[16];
		int viewport[4];
		glGetDoublev(GL_MODELVIEW_MATRIX,model);
		glGetDoublev(GL_PROJECTION_MATRIX,proj);
		glGetIntegerv(GL_VIEWPORT,viewport);
		gluUnProject(x,viewport[3]-y,0.901f,
			model,proj,
			viewport,
			&startX,&startY,&startZ);

		g_player->GetTransform()->SetPos(Vec3f(startX,startY,startZ));


	}
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1028, 720);
	glutCreateWindow("Hello");
	glutDisplayFunc(Draw); 

	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutMouseFunc(MouseMotion);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.4277777777777777777, 1.0, 1000.0);


	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	g_player=new Player();
	g_myNpc.SetTarget(g_player.DynamicCast<GameObject>());
	g_runAway=new BlueTeapot();
	g_runAway2= new BlueTeapot();
	g_runAway3= new BlueTeapot();
	g_runAway->GetTransform()->SetPos(Vec3f(0,0,0.1));
	g_runAway2->GetTransform()->SetPos(Vec3f(0.1,0,0));
	g_runAway3->GetTransform()->SetPos(Vec3f(-0.1,0,0));
	g_runAway->SetTarget(pGameObject(&g_myNpc));
	g_runAway2->SetTarget(pGameObject(&g_myNpc));
	g_runAway3->SetTarget(pGameObject(&g_myNpc));
	glLineWidth(3);

	TheLevel::Instance()->GetMesh().BuildMesh("floor3.obj","floor1");
	g_search.Init(TheLevel::Instance()->GetMesh().GetGraph(),1,2);
	g_search.Search(1000);

	glutMainLoop();

	return 0;
}
