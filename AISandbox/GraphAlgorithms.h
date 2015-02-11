#ifndef GRAPH_ALGORITHMS_H_INCLUDED
#define GRAPH_ALGORITHMS_H_INCLUDED
#include "Graph.h"
#include <stack>
#include <set>
#include <queue>
#include <assert.h>

enum SEARCH_RESULTS{SEARCH_FAILURE=0,SEARCH_NOT_DONE,SEARCH_NOT_FOUND,SEARCH_FOUND};

template
	<
		class T
	>
class GraphDepthFirstSearch
{
private:
	typedef std::stack<int> IntStack;
	typedef std::set<int> IntSet;
	typedef std::queue<int> Path;
	typedef typename Graph<T>::EdgeList TypeEdgeList;
	typedef typename Graph<T>::GraphNode TypeNode;
public:
	GraphDepthFirstSearch():target_(0){}
public:
	bool Init(const Graph<T>& g, int start, int target)
	{
		if(graph_!=&g)
		{
			Reset();
			graph_=&g;
			toBeVis_.push(start);
			target_=target;
			state_=SEARCH_NOT_DONE;
			return true;
		}
		return false;
	}
	int Search(const Graph<T>& g, int start, int target, int numOfNodes)
	{
		//member initilisation
		//if its a new graph, reset our values
		if(graph_!=&g)
		{
			Reset();
			graph_=&g;
			toBeVis_.push(start);
			target_=target;
			state_=SEARCH_NOT_DONE;
		}
		//then we call the search
		return Search(numOfNodes);
	}
	int Search(int numOfNodes){

		if(graph_==NULL)
		{
			assert(0);
			state_=SEARCH_FAILURE;
			return state_;
		}
		if(state_==SEARCH_FOUND)
		{
			return state_;
		}
		//temp list to store edges
		TypeEdgeList tempEdgeList;
		int loops=-1;
		if(numOfNodes>0)
		{
			loops=numOfNodes;
		}
		while(toBeVis_.size()!=0&&loops>0||loops==-1)
		{
			//grab the current node
			int curNode=toBeVis_.top();

			//pop our current element
			toBeVis_.pop();

			//get the edges for our current element
			tempEdgeList=graph_->GetEdgeList(curNode);

			//current element is now visited
			vis_.insert(curNode);

			//if the current element is the target, were done
			if(curNode==target_)
			{
				//return the target data
				path_.push(curNode);
				state_= SEARCH_FOUND;
				return state_;
			}

			//find every outgoing link
			bool canContinue=false;
			for(TypeEdgeList::iterator it=tempEdgeList.begin();
				it!=tempEdgeList.end();
				++it)
			{
				//store the number of where its going
				int num=it->GetTo();

				//if its not in the visited set
				if(vis_.find(num)==vis_.end())
				{
					//we should go there
					toBeVis_.push(num);
					canContinue=true;
				}
			}
			if(canContinue)
			{
				path_.push(curNode);
			}
			//clear the temp list (not sure if its more efficient)
			tempEdgeList.clear();

			//negate the loops
			--loops;
		}
		if(toBeVis_.size()>0)
		{
			state_=SEARCH_NOT_DONE;
			return state_;
		}
		state_=SEARCH_NOT_FOUND;
		return state_;
	}
	Path GetQueuePath()const
	{
		return path_;
	}
	TypeEdgeList GetEdgeListPath()const
	{
		if(graph_==NULL)
		{
			assert(0);
		}
		TypeEdgeList edgePath;
		TypeEdgeList temp;
		Path tempPath =path_;
		int start = tempPath.front();;
		do
		{
			temp=graph_->GetEdgeList(tempPath.front());
			int front=tempPath.front();
			tempPath.push(front);
			tempPath.pop();
			for(TypeEdgeList::iterator it=temp.begin();
				it!=temp.end();
				++it)
			{
				if(it->GetTo()==tempPath.front())
				{
					edgePath.push_back((*it));
					break;
				}
			}
			temp.clear();
		}
		while(tempPath.front()!=start);
		return edgePath; 
	}
	int GetState()const
	{
		return state_;
	}
	void Reset()
	{
		while(toBeVis_.size()>0)
		{
			toBeVis_.pop();
		}
		vis_.clear();
		while(path_.size()>0)
		{
			path_.pop();
		}
		target_=0;
		graph_=NULL;
		state_=SEARCH_NOT_DONE;
	}
private:
	int target_;

	int state_;

	//The target node which would remain null until the state clarifies that it has been found
	//TypeNode* targetNode_;
	IntStack toBeVis_;
	IntSet vis_;
	Path path_;
	const Graph<T>* graph_;
};





#endif