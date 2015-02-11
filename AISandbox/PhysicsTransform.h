#ifndef PHYSICS_PARTICLE_H_INCLUDED
#define PHYSICS_PARTICLE_H_INCLUDED
#include "Vec3.h"
#include "SmartPointer.h"
#include "AccelerationModels.h"
#include "SteeringData.h"



template <class T=EulerPhysics>
class PhysicsTransform :  public T, public RefCounted
{
public:
	PhysicsTransform(float mass=1.0f)
	{
		if(mass!=0)
		{
		invMass_=1.0f/mass;
		}
		else
		{
		invMass_=0;
		}
		friction_=0.95f;
		maxSpeed_=1000;
		maxRotation_=1000;

		orientation_=0;
		rotation_=0;
	}
	void Update();

	float GetRotation()const
	{return orientation_;}

	void SetMass(const float mass)
	{
		if(mass==0)
		{
			invMass_=0;
			return;
		}
		invMass_=1/mass;
	}

	Vec3f GetNextPos();

	float GetInvMass()const
	{return invMass_;}

	void AddSteeringData(const SteeringData& data)
	{force_+=data.velocity;
	rotation_+=data.angular;}

	void AddForce(const Vec3f& force)
	{force_+=force;}

	void SetForce(const Vec3f& force)
	{force_=force;}

	Vec3f GetForce()const
	{return force_;}

	void SetMaxSpeed(float max)
	{maxSpeed_=max;}
	float GetMaxSpeed()const
	{return maxSpeed_;}

	void SetMaxRotation(float max)
	{maxRotation_=max;}
	float GetMaxRotation()const
	{return maxRotation_;}

	void SetFriction(float frict)
	{
	friction_=frict;
	}
private:
	Vec3f force_;
	float invMass_;

	float orientation_;
	float rotation_;

	float maxSpeed_;
	float maxRotation_;

	float friction_;
};

typedef PhysicsTransform<EulerPhysics> EPhysicsParticle;
typedef PhysicsTransform<VerletPhysics> VPhysicsParticle;

typedef SmartPointer<EPhysicsParticle> PEPhysicsParticle;
typedef SmartPointer<VPhysicsParticle> PVPhysicsParticle;
#endif

