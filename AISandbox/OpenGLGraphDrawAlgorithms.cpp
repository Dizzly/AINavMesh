#include "OpenGLGraphDrawAlgorithms.h"


void DrawPath(std::vector<Vec3f>& path,bool drawLines)
{
	Vec3f v;
	for(auto it=path.begin();
		it!=path.end();
		++it)
	{
		glPushMatrix();
		glTranslatef(it->x,it->y,it->z);
		glutSolidCube(0.1);
		glPopMatrix();

		if(drawLines&&v!=Vec3f())
		{
			glBegin(GL_LINES);
			{
				glVertex3f(it->x,it->y,it->z);
				glVertex3f(v.x,v.y,v.z);
			}
			glEnd();
		}
		v=*it;
	}
}