#include "IntersectionFuncs.h"
#include <algorithm>

static const float EPSILON=0.000000000000001;
/*
bool AreLinesIntersecting(const Vec3f& line1S,
	const Vec3f& line1E,
	const Vec3f& line2S,
	const Vec3f& line2E)
{
	float d=(line1S.x-line1E.x)*(line2S.y-line2E.y)-(line1S.y-line1E.y)*(line2S.x-line2E.x);
	if(d==0)
	{return false;}
	float pre=(line1S.x*line1E.y - line1S.y*line1E.x);
	float post=(line2S.x*line2E.y- line2E.y*line2S.x);
	float x=(pre*(line2S.x-line2E.x)-(line1S.x-line1E.x)*post)/d;
	float y=(pre*(line2S.y-line2E.y)-(line1S.y-line1E.y)*post)/d;
	
	if ( x < min(x1, x2) || x > max(x1, x2) ||
	x < min(x3, x4) || x > max(x3, x4) ) return NULL;
	if ( y < min(y1, y2) || y > max(y1, y2) ||
	y < min(y3, y4) || y > max(y3, y4) ) return NULL;
	
	
	if(x<std::min(line1S.x,line1E.x)+EPSILON || x > std::max(line1S.x, line1E.x)+EPSILON ||
		x < std::min(line2S.x, line2E.x)+EPSILON || x> std::max(line2S.x, line2E.x)+EPSILON)
	{return false;}
	if(y<std::min(line1S.y,line1E.y)+EPSILON || y > std::max(line1S.y, line1E.y)+EPSILON ||
		y < std::min(line2S.y, line2E.y)+EPSILON || y> std::max(line2S.y, line2E.y)+EPSILON)
	{return false;}
	return true;
}
*/
bool IsPointOnTriangle(const Vec3f& point,
	const Vec3f& triA,
	const Vec3f& triB,
	const Vec3f& triC)
{
	Vec3f AB=triB -triA;
	Vec3f AC=triC -triA;
	Vec3f AP=point-triA;

	float dotABB = AB.Dot(AB);
	float dotABC = AB.Dot(AC);
	float dotABP = AB.Dot(AP);
	float dotACC = AC.Dot(AC);
	float dotACP = AC.Dot(AP);
	float invDenom =1 /(dotABB *dotACC - dotABC *dotABC);
	float u=(dotACC* dotABP - dotABC *dotACP) * invDenom;
	float v=(dotABB * dotACP - dotABC * dotABP) * invDenom;

	return (u>=0)&& (v>=0) && (u+v <1);
}

bool AreLinesIntersecting2D(const Vec3f& line1S,
	const Vec3f& line1E,
	const Vec3f& line2S,
	const Vec3f& line2E)
{
	Vec2f s1(line1S.x,line1S.z);
	Vec2f e1(line1E.x,line1E.z);
	Vec2f s2(line2S.x,line2S.z);
	Vec2f e2(line2E.x,line2E.z);
	return AreLinesIntersecting2D(s1,e1,s2,e2);
}

//given to me by Jason Colman using simultanius equations to solve two unknown values
bool AreLinesIntersecting2D(const Vec2f& line1S,
	const Vec2f& line1E,
	const Vec2f& line2S,
	const Vec2f& line2E)
{
	const float Ax =line1S.x;
	const float Ay =line1S.y;
	const float Bx =line1E.x;
	const float By =line1E.y;
	const float Cx =line2S.x;
	const float Cy =line2S.y;
	const float Dx =line2E.x;
	const float Dy =line2E.y;

	float d =(Bx-Ax)*(Dy-Cy) - (By - Ay) * (Dx -Cx);
	if(fabs(d)<EPSILON)
	{
	
	}

	float ua = ((Ay - Cy)* (Dx - Cx) - (Ax - Cx) * (Dy - Cy))/d;
	float ub = ((Ay - Cy)* (Bx - Ax) - (Ax -Cx) * (By - Ay))/d;

	if (ua <0 ||ua >1 || ub <0 || ub >1)
	{return false;}

	return true;
}
/*
bool

const float Ax
const float Ay
const float Bx
const float By
const float Cx
const float Cy
const float Dx
const float Dy

float d = (Bx-Ax) * (Dy - Cy) - (By - Ay) * (Dx -Cx);

if(fabs(d)<SMALLEST)
{
return false;
}

float ua = ((Ay - Cy)* (Dx - Cx) - (Ax - Cx) * (Dy - Cy) /d;
float ub - ((Ay - Cy)* (Bx - Ax) - (Ax - Cx) * (By - Ay)/d;

if(ua <0 || ua >1 || ub <0 || ub >1)
{
return false
}

pResult->x = Ax + ua * (Bx -Ax);
pResult->y =Ay + ua * (By - Ay);
*/


//adapted from the simultanius equations of Dan Sunday
//http://geomalgorithms.com/a07-_distance.html
bool LineIntersectCapsule(const Vec3f& sl,
	const Vec3f& el,
	const Vec3f& sc,
	const Vec3f& ec,
	float rad)
{
	Vec3f P0=sl;
	Vec3f Q0=sc;
	Vec3f u=el-sl;
	Vec3f v=ec-sc;
	Vec3f w=P0-Q0;

	float a=u.Dot(u);
	float b=u.Dot(v);
	float c=v.Dot(v);
	float d=u.Dot(w);
	float e=v.Dot(w);

	float den=(a*c-b*b);
	if(fabs(den)<EPSILON)
	{
		float s=0;
		float t=e/c;
		float dist=fabs((P0-Q0+u*s-v*t).Length());

		return dist<=rad;
		//they are parallel
	}

	float s= (b*e - c*d)/(a*c - b*b);
	float t= (a*e-b*d)/(a*c - b*b);

	float dist=fabs(((P0-Q0)+u*s-v*t).Length());
	return dist<=rad;
}