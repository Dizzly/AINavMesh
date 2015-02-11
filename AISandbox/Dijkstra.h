#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
#include "Graph.h"
#include <queue>
#include <set>

enum SEARCH_RESULTS{SEARCH_FAILURE=0,SEARCH_NOT_DONE,SEARCH_NOT_FOUND,SEARCH_FOUND};
template <class T>
class GraphDijkstraSearch
{
private:

	class CompareCostToNode;
private:
	typedef std::pair<int,int> CostToNode;
	typedef std::pair<int,int> CurToOrigin;


	typedef std::list<int> Path;
	typedef std::map<int,int> BreadCrumbMap;
	typedef std::priority_queue<CostToNode,std::vector<CostToNode>,CompareCostToNode> PriorityCostQueue;
	typedef std::map<int,int> NodeCostMap;

	typedef typename Graph<T>::EdgeList TypeEdgeList;
	typedef typename Graph<T>::GraphNode TypeNode;
public:
	GraphDijkstraSearch():target_(0){}

public:
	bool Init(const Graph<T>& g, int start, int target)
	{
		//reset our variables, but dont start the search
		Reset();
		graph_=&g;
		toBeVis_.push(CostToNode(0,start));
		bread_[start]=0;
		target_=target;
		state_=SEARCH_NOT_DONE;
		return true;
	}
	int Search(const Graph<T>& g,int start, int target, int numOfNodes)
	{
		//if its a new graph, then 
		if(graph_!=&g)
		{
			Reset();
			toBeVis_.push(CostToNode(0,start));
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
			//get the current node Id and cost
			int curNode = toBeVis_.top().second;
			int curCost = toBeVis_.top().first;
			//add it to the visited set
			vis_[curNode]=curCost;
			//pop it off the to be vis
			toBeVis_.pop();
			if(curNode==target_)
			{
				//make the path
				//the last element in our list is the final element
				path_.push_front(target_);
				//starting with the target node
				int crumbID=target_;
				//while we cant find our first node, default to ID 0
				while(bread_[crumbID]!=0)
				{
					//how did we get to our current node
					int backtrack= bread_[crumbID];
					//push how we found that node
					path_.push_front(backtrack);
					//and make that our current
					crumbID=backtrack;
				}
				state_=SEARCH_FOUND;
				return state_;
			}
			tempEdgeList=graph_->GetEdgeList(curNode);
			for(TypeEdgeList::iterator it=tempEdgeList.begin();
				it!=tempEdgeList.end();
				++it)
			{
				//get the cost to, and node ID of the target node
				int node=it->GetTo();
				int cost=it->GetCost();
				//add the cost to get to our current position, 
				//with the cost to get to the target node
				int totalCost= cost+curCost;
				//check if we've visited it
				NodeCostMap::iterator findIt =vis_.find(node);
				if(findIt==vis_.end())
				{
					//if we havent visited it, then its to be visited
					toBeVis_.push(CostToNode(totalCost,node));
					//store the cost of getting there
					vis_[node]=totalCost;
					//and how we got to this node for the breadcrumbs
					bread_[node]=curNode;
				}
				else
				{
					// if we've already visited this
					// and we've found this node at a lower cost
					if(findIt->second > totalCost)
					{
						//update the total cost to the cheaper alternative
						findIt->second=totalCost;
						//update the breadcrumbs
						bread_[node]=curNode;
						toBeVis_.push(CostToNode(findIt->second,findIt->first));
					}
				}
			}
			//clear the temp edge list for reuse
			tempEdgeList.clear();
			//and we've finished one of our assigned loops
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

	const Path& GetPath()
	{
		if(state_=SEARCH_FOUND&&path_.size()>0)
		{
			return path_;
		}
		return NULL;
	}

private:
	class CompareCostToNode
	{
	public:
		bool operator() (const CostToNode& lhs, const CostToNode& rhs) const
		{

			return (lhs.first > rhs.first);
		}
	};

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