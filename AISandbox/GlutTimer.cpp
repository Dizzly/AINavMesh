#include "GlutTimer.h"

GlutTimer::GlutTimer()
{
oldTime_=0;
}

void GlutTimer::Upadate()
{
int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
deltaTime_=elapsedTime- oldTime_;
oldTime_=elapsedTime;
}

float GlutTimer::GetDeltaT()
{
return (float)deltaTime_/1000.0f;
}