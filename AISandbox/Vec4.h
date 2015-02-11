#ifndef VEC4_H_INCLUDED
#define VEC4_H_INCLUDED
#include "Vec3.h"
template<class T>
struct Vec4
{
	T x,y,z,w;
	Vec4()
	{
		x,y,z,w=0;
	}
	Vec4(const Vec4& vec)
	{
		x=vec.x;
		y=vec.y;
		z=vec.z;
		w=vec.w;
	}
	Vec4(const Vec3<T>& vec, const T& loneW)
	{
		x=vec.x;
		y=vec.y;
		z=vec.z;
		w=loneW;
	}
};
typedef Vec4<float> Vec4f;

#endif