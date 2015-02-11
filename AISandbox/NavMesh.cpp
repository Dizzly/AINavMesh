#include "NavMesh.h"
#include "ObjUsefulFunctions.h"
#include <assert.h>
#include "IntersectionFuncs.h"
#include <gl/glut.h>
#include "CollisionManager.h"
#include "Plane.h"


void NavMesh::DebugDraw()
{
	int i=0;
	for(auto it=navTris_.begin();it!=navTris_.end();++it)
	{
		glBegin(GL_LINE_LOOP);
		glVertex3f(it->c.x,it->c.y,it->c.z);
		glVertex3f(it->b.x,it->b.y,it->b.z);
		glVertex3f(it->a.x,it->a.y,it->a.z);
		glEnd();
	}
}

void NavMesh::DebugDrawEdge()
{
	for(auto it=edgeLines_.begin();it!=edgeLines_.end();++it)
	{

		Vec3f start=it->line.GetStart();
		Vec3f end=it->line.GetEnd();
		Vec3f norm=it->normal;
		glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex3f(start.x,start.y,start.z);
		glVertex3f(end.x,end.y,end.z);

		glColor3f(1,0,0);
		Vec3f to=end-start;
		Vec3f mid=start+to*0.5;
		glVertex3f(mid.x,mid.y,mid.z);
		glVertex3f(mid.x+it->normal.x*0.2,
			mid.y+it->normal.y*0.2,
			mid.z+it->normal.z*0.2);

		glEnd();
	}	
}

bool NavMesh::BuildMesh(const std::string& filename,const std::string& floorName)
{
	File f;
	if(!f.OpenRead(filename))
	{
		assert(0);
		return false;
	}
	bool readMesh=false;
	std::string read;
	std::string groupName;
	Vecs points;
	navTris_.push_back(NavTriangle());
	while(f.GetString(&read))
	{
		Strings data(Split(read,' '));
		if(data[0]=="v")
		{
			points.push_back(ToVec3(data));
		}
		if(data[0]=="g")
		{
			if(floorName==data[1])
			{
				if( ReadFloorData(&f,points))
				{
					for(auto it=edgeLines_.begin();
						it!=edgeLines_.end();
						++it)
					{
						TheCollMan::Instance()->AddCollisionWall(it->line,it->normal);
					}
				}
			}
		}
		
	}
	return false;
}

void NavMesh::OptimisePath(std::vector<Vec3f>& path)
{
	std::vector<Vec3f> vec;
	vec.push_back(path.front());
	bool hit =false;
	for(int j=0;j<edgeLines_.size();++j)//check if there is LOS between start and end
	{		//we can skip more complex stuff if we can directly see where were going
		Vec3f start(path.front());
		Vec3f end(path.back());
		Vec3f edgeStart(edgeLines_[j].line.GetStart());
		Vec3f edgeEnd(edgeLines_[j].line.GetEnd());
		if(AreLinesIntersecting2D(start,end,edgeStart,edgeEnd))
		{
			hit=true;
			break;
		}
	}
	if(!hit)
	{
		vec.push_back(path.back());
		path=vec;
		return;
	}
	int i=1;
	auto it=path.begin();
	auto last=it;
	++it;
	for(;it!=path.end();++it)
	{

		Vec3f start(vec.back());
		Vec3f end(*it);
		for(int j=0;j<edgeLines_.size();++j)
		{
			Vec3f edgeStart(edgeLines_[j].line.GetStart());
			Vec3f edgeEnd(edgeLines_[j].line.GetEnd());
			if(AreLinesIntersecting2D(start,end,edgeStart,edgeEnd))
			{
				vec.push_back(*last);
				break;
			}
		}
		if((*it)==path.back())
		{
			vec.push_back(path.back());
			break;
		}
		last=it;
		++i;
	}
	path=vec;
}

int NavMesh::PositionOnMesh(const Vec3f& pos)
{
	return NodeWithPoint(pos);
}

NavTriangle NavMesh::GetTriangle(int id)
{
	assert(id>0&&id<navTris_.size());
	return navTris_[id];
}

int NavMesh::NodeWithPoint(const Vec3f& pos)
{
	for(int i=0;i<navTris_.size();++i)
	{
		if(IsPointOnTriangle(pos,navTris_[i].a,
			navTris_[i].b,navTris_[i].c))
		{
			return i;
		}
	}
	return 0;
}

bool NavMesh::ReadFloorData(File* f, Vecs& points)
{
	if(0==f)
	{
		assert(0);
		return false;
	}

	typedef std::vector<NavTriangle*> PNavTris;
	typedef std::vector<Vec3i> TriIndex;
	typedef std::pair<int, int> LineIndex;
	typedef std::vector<int> TriangleIDs;

	//make this a pair of ints, makes it much easier to find accumpanying triangles
	//the loop is going to be interesting, you probably should just loop through all keys
	LineIndex lineIndex;
	TriIndex triIndex;
	std::map<LineIndex,TriangleIDs> triLinkMap;

	std::string read;
	while(f->GetString(&read))
	{
		Strings data(Split(read,' '));
		if(data[0]=="f")
		{
			Face f =ToFace(data);
			int size=triIndex.size();

			int a=f.pointIndex_[0],
				b=f.pointIndex_[1],
				c=f.pointIndex_[2];

			triIndex.push_back(Vec3i(a,
				b,c));


			LineIndex ab(a,b);
			LineIndex bc(b,c);
			LineIndex ca(c,a);
			//reverse indexes because the line may be shared, but heading the in the other direction
			LineIndex rab(b,a);
			LineIndex rbc(c,b);
			LineIndex rca(a,c);

			if(triLinkMap.find(rab)!=triLinkMap.end())
			{
				triLinkMap[rab].push_back(size);
			}
			else
			{triLinkMap[ab].push_back(size);}

			if(triLinkMap.find(rbc)!=triLinkMap.end())
			{
				triLinkMap[rbc].push_back(size);
			}
			else
			{triLinkMap[bc].push_back(size);}

			if(triLinkMap.find(rca)!=triLinkMap.end())
			{
				triLinkMap[rca].push_back(size);
			}
			else
			{triLinkMap[ca].push_back(size);}

		}
		if(data[0]=="g")
		{
			break;
		}
	}
	navTris_.reserve(triIndex.size());//to stop the vector resizing,
	for(int i=0;i<triIndex.size();++i)
	{
		NavTriangle tri;
		tri.a=points[triIndex[i].x];
		tri.b=points[triIndex[i].y];
		tri.c=points[triIndex[i].z];
		navTris_.push_back(tri);
		Vec3f avgPos=(tri.a+tri.b+tri.c)/3;
		graph_.AddNode(NavTriNode(avgPos,&navTris_.back(),i+1));
	}
	for(auto it=triLinkMap.begin();it!=triLinkMap.end();++it)
	{
		if(it->second.size()<2)
		{
			EdgeLine e;
			int lineS =it->first.first;
			int lineE =it->first.second;
			e.line=LineSegment(points[lineS],points[lineE]);
			Vec3f to=e.line.GetEnd()-e.line.GetStart();
			e.normal=to.Cross(Vec3f(0,-1,0));
			e.normal.Normalise();
			edgeLines_.push_back(e);
			continue;
		}
		int tri1 = it->second[0],
			tri2 = it->second[1];

		graph_.AddDoubleEdge(tri1+1,
			tri2+1,1);
	}
	return true;
}

NavTriGraph& NavMesh::GetGraph()
{
	return graph_;
}

int NavMesh::NumOfTris()const
{
	return navTris_.size();	
}