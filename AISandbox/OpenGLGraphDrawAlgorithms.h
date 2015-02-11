#ifndef OPEN_GL_GRAPH_DRAW_ALGORITHMS_H_INCLUDED
#define OPEN_GL_GRAPH_DRAW_ALGORITHMS_H_INCLUDED
#include "Graph.h"
#include <gl/glut.h>
#include <queue>
#include "BitmapFontBillboard.h"


void DrawPath(std::vector<Vec3f>& path,bool drawLines=true);


template <class T>
void DrawGraph(const Graph<T>& g,const BitmapFontBillboard* font,bool drawLines=true)
{
	typedef typename Graph<T>::Nodes Nodes;
	typedef typename Graph<T>::EdgeList EdgeList;
	typedef typename std::pair<int,Vec3f> CostPos;
	typedef typename std::list<CostPos> ToDrawList;
	ToDrawList paths;
	ToDrawList points;

	const Graph<T>::Nodes nodes=g.GetNodeMap();
	for(Nodes::const_iterator it=nodes.begin();
		it!=nodes.end();
		++it)
	{
		if(drawLines)
		{
			EdgeList edges=g.GetEdgeList(it->second.GetID());
			glColor3f(1,0,0);
			for(EdgeList::const_iterator ity=edges.begin();
				ity!=edges.end();
				++ity)
			{
				int cost=ity->GetCost();
				Vec3f start(it->second.GetPos().x,
					it->second.GetPos().y,
					it->second.GetPos().z);

				Vec3f end(nodes.at(ity->GetTo()).GetPos().x,
					nodes.at(ity->GetTo()).GetPos().y,
					nodes.at(ity->GetTo()).GetPos().z);

				glBegin(GL_LINES);
				{
					glVertex3f(start.x,start.y,start.z);

					glVertex3f(end.x,end.y,end.z);
				}
				glEnd();
				Vec3f startToEnd= end-start;
				Vec3f textPos= start+(startToEnd/2);
				paths.push_back(CostPos(cost,textPos));
			}
		}
		glColor3f(0,0,1);
		glPushMatrix();
		{
			glTranslatef(it->second.GetPos().x,it->second.GetPos().y,it->second.GetPos().z);
			points.push_back(CostPos(it->second.GetID(),it->second.GetPos()));
			glutSolidCube(0.1);
		}
		glPopMatrix();
	}
	if(font)
	{
		glColor3f(0,1,0);
		for(ToDrawList::iterator it=points.begin();
			it!=points.end();
			++it)
		{
			std::string str = std::to_string((long double)it->first);
			font->Draw(str,it->second+Vec3f(0,0,0.3),0.1);
		}
		glColor3f(1,0,1);
		for(ToDrawList::iterator it=paths.begin();
			it!=paths.end();
			++it)
		{
			std::string str = std::to_string((long double)it->first);
			font->Draw(str,it->second+Vec3f(0,0,0.1),0.1);
		}
	}
}

#endif