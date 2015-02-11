#include "SteeringData.h"

SteeringData::SteeringData()
{
angular=0;
}

SteeringData::SteeringData(const Vec3f& v, float an)
{
	velocity=v;
	angular =an;
}

void SteeringData::operator +=(const SteeringData& d)
{
	velocity+=d.velocity;
	angular+=d.angular;
}