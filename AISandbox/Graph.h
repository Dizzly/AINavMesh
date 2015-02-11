#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <map>
#include <list>
#include <vector>
#include "Vec3.h"
#include <assert.h>
#include "Vec2.h"
template <class T>

class Graph
{

public:
	class GraphNode
	{
	public:
		GraphNode(Vec3f pos, T* data, int ID):pos_(pos)
		{
		data_=data;
		ID_=ID;
		}
		GraphNode(Vec3f pos, T* data):pos_(pos)
		{
		pos_=pos;
		data_=0;
		}
		GraphNode(){
		data_=0;
		ID_=0;
		}
		void SetPos(const Vec3f& pos){pos_=pos;}
		Vec3f GetPos()const{return pos_;}

		void SetID(int ID){ID_=ID;}
		int GetID()const{return ID_;}

		const T* GetData()const {return data_;}
		T* AccessData(){return data_;}
	private:
		Vec3f pos_;
		int ID_;
		T* data_;
	};
public:
	class GraphEdge
	{
	public:
		GraphEdge(){from_=0,to_=0,cost_=0;}
		GraphEdge(int from, int to, int cost):from_(from), to_(to), cost_(cost){}
		GraphEdge(int from, int to):from_(from),to_(to){cost_=0;}

		void SetTo(int to){to_=to;}
		int GetTo()const{return to_;}

		void SetFrom(int from){from_=from;}
		int GetFrom()const{return from_;}

		void SetCost(int cost){cost_=cost;}
		int GetCost()const{return cost_;}

	private:
		int from_;
		int to_;
		int cost_;

	};
public:
	typedef std::map<int, GraphNode> Nodes;
	typedef std::list<GraphEdge> EdgeList;
	typedef std::map<int, EdgeList> EdgeListMap;

public:
	void AddNode(GraphNode n)
	{
		//ID 0 is an error, cannot have node zero
		assert(n.GetID()!=0);
		//see if there is already a node with this ID in the map
		Nodes::iterator it= nodes_.find(n.GetID());
		//and make sure there isnt
		assert(it==nodes_.end());
		//if so, intilise node and the edges for that node
		nodes_[n.GetID()]=n;
		//this is necessary for intilisation, were not adding any edges,
		//just announcing that there is a node that may have edges
		edges_[n.GetID()];
	}
public:
	void AddEdge(GraphEdge e)
	{
		//if its a valid edge
		if(e.GetFrom()==0||e.GetTo()==0)
		{
			return;
		}
		//add the edge
		//it doesnt matter if the nodes dont exist yet
		//if it's from and to are not valid node ID's then its a floating edge
		edges_[e.GetFrom()].push_back(e);
	}
	const Nodes& GetNodeMap()const
	{
		return nodes_;
	}
	const EdgeList& GetEdgeList(int nodeID)const
	{
		return edges_.at(nodeID);
	}
	const GraphNode& GetNode(int nodeID)const
	{
		return nodes_.at(nodeID);
	}
	const T* GetData(int nodeID)const
	{
		return nodes_.at(nodeID).GetData();
	}
	T* AccessData(int nodeID)
	{
		return nodes_.at(nodeID).AccessData();
	}
	void AddEdge(int fromNodeID, int toNodeID,int cost=0)
	{
		if(fromNodeID!=0&&toNodeID!=0)
		{
			Nodes::iterator it,ity;
			it=nodes_.find(fromNodeID);
			ity=nodes_.find(toNodeID);
			if(it!=nodes_.end()&&ity!=nodes_.end())
			{
				edges_[fromNodeID].push_back(GraphEdge(fromNodeID,toNodeID,cost));
			}
		}
	}
	void AddDoubleEdge(int fromNodeID, int toNodeID, int cost=0)
	{
		AddEdge(fromNodeID,toNodeID,cost);
		AddEdge(toNodeID,fromNodeID,cost);
	}
private:
	int GetFreeID()
	{
		return nodes_.size()+1;
	}
private:
	Nodes nodes_;
	EdgeListMap edges_;
	static int freeID_;
};

#endif