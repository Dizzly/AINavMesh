#pragma once

#include "Vec3.h"
#include "Graph.h"
#include <string>
#include "File.h"
#include "LineSegment.h"
#include "ObjUsefulFunctions.h"
#include "LineSegment.h"
#include "AStar.h"

struct NavTriangle
{
	Vec3f a,b,c;
};

struct EdgeLine
{
LineSegment line;
Vec3f normal;
};

typedef Graph<NavTriangle> NavTriGraph;
typedef NavTriGraph::GraphNode NavTriNode;
typedef std::vector<NavTriangle> NavTris;
typedef std::vector<EdgeLine> LineVec;
typedef GraphAStar<NavTriangle> NavMeshAStarSearch;

class NavMesh
{
public:
	bool BuildMesh(const std::string& filename,
		const std::string& floorName);

	NavTriGraph& GetGraph();

	int PositionOnMesh(const Vec3f& pos);

	void OptimisePath(std::vector<Vec3f>& path);

	NavTriangle GetTriangle(int id);
	int NumOfTris()const;
	void DebugDraw();
	void DebugDrawEdge();

private:
	int NodeWithPoint(const Vec3f& pos);
	bool ReadFloorData(File* file,Vecs& vec);
	bool GraphEdgeCheck(const LineSegment& line);
private:
	NavTriGraph graph_;
	NavTris navTris_;
	LineVec edgeLines_;
};

