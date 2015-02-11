#ifndef GLUT_TIMER_H_INCLUDED
#define GLUT_TIMER_H_INCLUDED

#include "Singleton.h"
#include <gl/glut.h>
#include "NonCopyable.h"

class GlutTimer;
typedef Singleton<GlutTimer> TheGlutTimer;
class GlutTimer :public NonCopyable
{
public:
	float GetDeltaT();
	void Upadate();
private:
		GlutTimer();
		friend TheGlutTimer;
private:
int oldTime_;
int deltaTime_;
};

#endif