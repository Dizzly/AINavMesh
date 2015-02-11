#pragma once
#include "Vec2.h"
#include "Vec3.h"

bool AreLinesIntersecting2D(const Vec2f& line1S,
	const Vec2f& line1E,
	const Vec2f& line2S,
	const Vec2f& line2E);

bool AreLinesIntersecting2D(const Vec3f& line1S,
	const Vec3f& line1E,
	const Vec3f& line2S,
	const Vec3f& line2E);


bool IsPointOnTriangle(const Vec3f& point,
	const Vec3f& triA,
	const Vec3f& triB,
	const Vec3f& triC);

bool LineIntersectCapsule(const Vec3f& sl,
	const Vec3f& el,
	const Vec3f& sc,
	const Vec3f& ec,
	float rad);