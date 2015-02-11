#pragma once
#include "Graph.h"
#include <queue>
#include <set>
#include <map>
#include "Vec3.h"

template <class T>
class GraphAStar
{
private:
	class PriorityQueue
	{
	private:
		typedef std::pair<int,int> CostToNode;
	public:
		void SortIn(CostToNode& node)
		{
			if(list_.size()==0)
			{list_.push_back(node);}
			for(auto it=list_.begin();it!=list_.end();
				++it)
			{
				if(it->first<node.first)
				{
					
					list_.insert(it,node);
					return;
				}
			}
			list_.push_back(node);
		}
		CostToNode& GetTop()
		{
			return list_.back();
		}
		void PopTop(){list_.pop_back();}
		void ResortNode(CostToNode& node)
		{
			for(auto it=list_.begin();it!=list_.end();
				++it)
			{
				if(it->second==node.second)
				{
					list_.erase(it);
					SortIn(node);
				}
			}
		}
		void Clear(){list_.clear();}
		int Size(){return list_.size();}
	private:
		std::list<CostToNode> list_;
	};
public:
	enum SEARCH_RESULTS{SEARCH_FAILURE=0,SEARCH_NOT_DONE,SEARCH_NOT_FOUND,SEARCH_FOUND};
private:
	typedef std::pair<int,int> CostToNode;
	typedef std::pair<int,int> CurToOrigin;

	typedef std::vector<Vec3f> NodeIDPath;
	typedef std::vector<int> intPath;
	typedef std::map<int,int> BreadCrumbMap;
	typedef std::map<int,int> NodeCostMap;

	typedef typename Graph<T>::EdgeList TypeEdgeList;
	typedef typename Graph<T>::GraphNode TypeNode;

public:
	GraphAStar():target_(0){}
public:
	bool Init(const Graph<T>& g, int start, int target)
	{
		Reset();
		graph_=&g;
		toBeVis_.SortIn(CostToNode(0,start));
		bread_[start]=0;
		target_=target;
		state_=SEARCH_NOT_DONE;
		return true;
	}
	int Search(const Graph<T>& g, int start, int target, int numOfNodes)
	{
		Reset();
		Init(g,start,target);
		/*
		if(graph_!=&g)
		{
			Reset();
			toBeVis_.SortIn(CostToNode(0,start));
			bread_[start]=0;
			target_=target;
			graph_=&g;
		}
		if(bread_.size()>0&&bread_[start]!=0)
		{
			Reset();
			toBeVis_.SortIn(CostToNode(0,start));
			bread_[start]=0;
			target_=target;
			graph_=&g;
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
					int backtrack=bread_[crumbID];
					path_.push_front(backtrack);
					crumbID=backtrack;
				}
				state_=SEARCH_FOUND;
				return state_;
			}
			target_=target;
		}*/
		return	Search(numOfNodes);
		
	}
	int Search(int numOfNodes)
	{

		//if the graph has been initialised
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
		while(toBeVis_.Size()!=0&&loops>0||loops==-1)
		{
			int curNode=toBeVis_.GetTop().second;
			int curCost=toBeVis_.GetTop().first;

			vis_[curNode]=curCost;
			toBeVis_.PopTop();
			tempEdgeList=graph_->GetEdgeList(curNode);
			if(curNode==target_)
			{
				path_.push_back(graph_->GetNode(target_).GetPos());
				int crumbID=target_;
				while(bread_[crumbID]!=0)
				{
					int backtrack = bread_[crumbID];
					path_.push_back(graph_->GetNode(backtrack).GetPos());
					crumbID=backtrack;
				}
				std::reverse(path_.begin(),path_.end());
				state_=SEARCH_FOUND;
				return state_;
			}

			for(TypeEdgeList::iterator it=tempEdgeList.begin();
				it!=tempEdgeList.end();
				++it)
			{
				int checkNode=it->GetTo();
				int checkCost=it->GetCost();

				int totalCost=vis_[curNode]+checkCost;
				int fCost = totalCost+HCost(checkNode);
				NodeCostMap::iterator findIt = vis_.find(checkNode);
				if(vis_.end()==findIt)
				{
					toBeVis_.SortIn(CostToNode(fCost,checkNode));
					bread_[checkNode]=curNode;
					vis_[checkNode]=totalCost;
				}
				else
				{
					if(findIt->second >totalCost)
					{
						findIt->second=totalCost;
						bread_[checkNode]=curNode;
						toBeVis_.ResortNode(CostToNode(fCost,findIt->first));
					}
				}
			}
			tempEdgeList.clear();
			--loops;
		}
		if(toBeVis_.Size()==0)
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
		toBeVis_.Clear();
		vis_.clear();
		graph_=NULL;
		path_.clear();
		bread_.clear();
	}
	int GetState()
	{
		return state_;
	}
	std::vector<Vec3f> GetPath()
	{
		if(state_==SEARCH_FOUND&& path_.size()>0)
		{
		return path_;
		}
		return NodeIDPath();
	}
private:
	int HCost(int nodeId)
	{
		return abs((graph_->GetNode(nodeId).GetPos()-
			graph_->GetNode(target_).GetPos()).Length());
	}
private:
	int state_;
	int target_;

	NodeIDPath path_;
	BreadCrumbMap bread_;
	PriorityQueue toBeVis_;
	NodeCostMap vis_;
	const Graph<T>* graph_;
};