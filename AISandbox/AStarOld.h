#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED
#include "Graph.h"
#include<queue>
#include <set>
class AStar_ManhattenDistance
{
public:
static int HCost(Vec2f target, Vec2f node);
};


template<class T,
		class HMethod = AStar_ManhattenDistance>
class GraphAStarSearch
{
public:
	enum SEARCH_RESULTS{SEARCH_FAILURE=0,SEARCH_NOT_DONE,SEARCH_NOT_FOUND,SEARCH_FOUND};
private:
	class CompareCostToNode;
private:
	typedef std::pair<int,int> CostToNode;
	typedef std::pair<int,int> CurToOrigin;

	typedef std::list<int> Path;
	typedef std::map<int,int>BreadCrumbMap;
	typedef std::priority_queue<CostToNode,std::vector<CostToNode>,CompareCostToNode> PriorityCostQueue;
	typedef std::map<int,int> NodeCostMap;

	typedef typename Graph<T>::EdgeList TypeEdgeList;
	typedef typename Graph<T>::GraphNode TypeNode;
public:
	GraphAStarSearch():target_(0){}

public:
	bool Init(const Graph<T>& g, int start, int target)
	{
		Reset();
		graph_=&g;
		toBeVis_.push(CostToNode(0,start));
		bread_[start]=0;
		target_=target;
		state_=SEARCH_NOT_DONE;
		return true;
	}

	int Search(const Graph<T>& g, int start, int target, int numOfNodes)
	{
		if(graph_!=&g)
		{
			Reset();
			toBeVis_.push(CostToNode(HCost(start),start));
			bread_[start]=0;
			target_=target;
			graph_=g;
		}
		if(bread_.size()>0&&bread_[start]!=0)
		{
			Reset();
			toBeVis_.push(CostToNode(0,start));
			bread_[start]=0;
			target_=target;
			graph_=g;
		}
		if(target_!=target)
		{
			NodeCostMap::iterator it=vis_.find(target);
			if(it!=vis_.end())
			{
				path_.push_front(target_);
				int crumbID=target_;
				while(bread_[crumbID]!=0)
				{
					int backtrack= bread_[crumbID];
					path_.push_front(backtrack);
					crumbID=backtrack;
				}
				state_=SEARCH_FOUND;
				return state_;
			}
			target_=target;
		}
		Search(numOfNodes);
	}

	int Search(int numOfNodes)
	{
		if(graph_==NULL)
		{
			assert(0);
			state_=SEARCH_FAILURE;
			return state_;
		}
		if(state_==SEARCH_FOUND||state_==SEARCH_NOT_FOUND)
		{
			return state_;
		}
		TypeEdgeList tempEdgeList;
		int loops=-1;
		if(numOfNodes>0)
		{
			loops=numOfNodes;
		}
		while(toBeVis_.size()!=0&&loops>0||loops==-1)
		{
			//current node Id and its F cost
			int curNode = toBeVis_.top().second;
			int curCost = toBeVis_.top().first;
			//add it to visited
			vis_[curNode]=curCost;
			//take it off the the to be vis
			toBeVis_.pop();
			//if its the target then make the path
			if(curNode==target_)
			{

				path_.push_back(target_);
				int crumbID=target_;

				while(bread_[crumbID]!=0)
				{
					int backtrack = bread_[crumbID];
					path_.push_front(backtrack);
					crumbID=backtrack;
				}
				state_=SEARCH_FOUND;
				return state_;
				//makepath
			}
			//if not then loop through its links
			for(TypeEdgeList::iterator it=tempEdgeList.begin();
				it!=tempEdgeList.end();
				++it)
			{
				//get the node ID and its g cost
				int checkNode=it->GetTo();
				int checkCost=it->GetCost();
				//figure out the total cost
				//tC = curNode.gCost+gCost
				int totalCost = vis_[curNode]+checkCost;
				//check if we've vistited it
				int fCost = totalCost+HCost(checkNode);
				NodeCostMap::iterator findIt =vis_.find(checkNode);
				if(vis_.end()==findIt)
				{
					//if not then add it, with f value
					//f cost=tC+H;
					toBeVis_.push(CostToNode(fCost,checkNode));
					//breadcrumb it
					bread_[checkNode]=curNode;
					//add its g cost to the map
					vis_[checkNode]=totalCost;
				}
				else
				{
					//check if our current tC > stored gCost
					if(findIt->second > totalCost)
					{
						findIt->second=totalCost;
						//update breadcrumbs
						bread_[checkNode]=curNode;
						//push the node back onto the toBeVisted
						toBeVis_.push(CostToNode(fCost,findIt->first));
					}
				}
			}
			tempEdgeList.clear();
			--loops;
		}
		if(toBeVis_.size()==0)
		{
			state_=SEARCH_NOT_FOUND;
			return state_;
		}
		return state_;
	}

	void Reset()
	{
		target_=0;
		state_=SEARCH_FAILURE;
		while(toBeVis_.size()>0)
		{
			toBeVis_.pop();
		}
		vis_.clear();
		graph_=NULL;
		path_.clear();
		bread_.clear();
	}

	int GetState()
	{
		return state_;
	}

	const Path* GetPath()
	{
		if(state_=SEARCH_FOUND&&path_.size()>0)
		{
			 return &path_;
		}
		return NULL;
	}

private:
	class CompareCostToNode
	{
	public:
		bool operator() (const CostToNode& lhs, const CostToNode& rhs) const
		{return (lhs.first > rhs.first);}
	};

	int HCost(int nodeID)
	{
		return HMethod.HCost(graph_->GetNode(target).GetPos(),
			graph_->GetNode(nodeID).GetPos());
	}
private:
	int target_;
	int state_;

	Path path_;
	BreadCrumbMap bread_;
	PriorityCostQueue toBeVis_;
	NodeCostMap vis_;
	const Graph<T>* graph_;

};



#endif