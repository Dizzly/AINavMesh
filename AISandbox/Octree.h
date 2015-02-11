#pragma once
#include <vector>

#include "BBox.h"
#include "Capsule.h"
//template octree


template<class T>
class Octant
{
public:
	virtual ~Octant();
	virtual void PointCollisionCheck(const Vec3f& point,std::vector<const T*>& vec){}
	virtual void SphereCollisionCheck(const Vec3f& point, float rad,std::vector<const T*>& vec){}
	virtual void CapsuleCollisionCheck(const Capsule& c, std::vector<const T*>& vec){}
	bool PointCollision(Vec3f point){
		return box_.Contains(point);
	}
	bool SphereCollision(Vec3f point, float rad){
		return box_.CollidesSphere(rad,point);
	}
private:
	BBox box_;
};

template<class T>
class LeafOctant :public Octant<T>
{
public:
	LeafOctant(const std::vector<const T*>& data, const BBox& box): data_(data), box_(box){}
	virtual void PointCollisionCheck(const Vec3f& point, std::vector<const T*>& vec)override{
		vec.Insert(vec.End(),data_.Begin(),data_.End());
	}
	virtual void SphereCollisionCheck(const Vec3f& point, float rad,std::vector<const T*>& vec)override{
		vec.Insert(vec.End(),data_.Begin(),data_.End());
	}
	virtual void CapsuleCollisionCheck(const Capsule& c, std::vector<const T*>& vec)override{
		vec.Insert(vec.End(),data_.Begin(),data_.End());
	}
private:
	std::vector<const T*> data_;
};

template<class T>
class ParentOctant :public Octant<T>
{
public:
	ParentOctant(const BBox& box):box_(box){}

	void AddChild(Octant* o){children_.push_back(0);}
	virtual void PointCollisionCheck(const Vec3f& point, std::vector<const T*>& vec)override{
		for(int i=0;i<children_.size();++i)
		{
			if(children_[i]->PointCollision(point))
			{
				children_[i]->PointCollisionCheck(point,vec);
			}
		}
	}
	virtual void SphereCollisionCheck(const Vec3f& point, float rad,std::vector<const T*>& vec)override{
		for(int i=0;i<children_.size();++i)
		{
			if(children_[i]->SphereCollision(point,rad))
			{
				children_[i]->SphereCollisionCheck(point,rad,vec);
			}
		}
	}
	virtual void CapsuleCollideCheck(const Capsule& c, std::vector<const T*>& vec)override{ 
		for(int i=0;i<children_.size();++i)
		{
			if(children_[i]->SphereCollision(c.GetLine().GetEnd(),c.GetRad()))
			{
				children_[i]->CapsuleCollisionCheck(c,vec);
			}
		}
	};

private:
	std::vector<Octant*> children_;
};