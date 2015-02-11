#include "PhysicsTransform.h"
#include "GlutTimer.h"
#include <assert.h>


template<> Vec3f PhysicsTransform<EulerPhysics>::GetNextPos()
{
	if(invMass_==0)
	{
	return pos_;
	}
	Vec3f accel = force_*invMass_;
	Vec3f tempOldVel = vel_*friction_;
	Vec3f tempVel = vel_*friction_+accel;
	Vec3f tempPos=pos_+((tempOldVel+tempVel)*0.5)*TheGlutTimer::Instance()->GetDeltaT();
	return tempPos;
}

template<> void PhysicsTransform<EulerPhysics>::Update()
{


	if(invMass_==0)
	{
		return;
	}
	Vec3f accel = force_*invMass_;
	if(vel_.SqrLength()>maxSpeed_*maxSpeed_)
	{
	vel_.Normalise();
	vel_*=maxSpeed_;
	}
	vel_*=friction_;
	oldVel_=vel_;
	vel_+=accel;
	pos_+=((oldVel_+vel_)*0.5)*TheGlutTimer::Instance()->GetDeltaT();

	if(fabs(rotation_)>maxRotation_)
	{
		if(rotation_<0)
		{rotation_=-maxRotation_;}
		else
		{rotation_=maxRotation_;}
	}
	orientation_+=rotation_;
	force_=Vec3f();
	rotation_=0;
}

template<> Vec3f PhysicsTransform<VerletPhysics>::GetNextPos()
{
	if(invMass_==0)
	{
	return pos_;
	}
	Vec3f acc = force_*invMass_;
	Vec3f diff = (pos_-oldPos_)*(friction_)+acc*TheGlutTimer::Instance()->GetDeltaT();
	return pos_+diff;
}

template<> void PhysicsTransform<VerletPhysics>::Update()
{

	if(invMass_==0)
	{
		return;
	}

	acc_= force_*invMass_;
	force_=Vec3f();

	Vec3f diff = (pos_-oldPos_)*friction_+acc_*TheGlutTimer::Instance()->GetDeltaT();//1.0f ==DT
	if(diff.SqrLength()>maxSpeed_*maxSpeed_)
	{
		diff.Normalise();
		diff*=maxSpeed_;
	}
	oldPos_=pos_;
	pos_+=diff*friction_;
	if(fabs(rotation_)>maxRotation_)
	{
		if(rotation_<0)
		{rotation_=-maxRotation_;}
		else
		{rotation_=maxRotation_;}
	}
	orientation_+=rotation_;
	rotation_=0;
}

