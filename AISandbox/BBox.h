#ifndef BBOX_H
#define BBOX_H

#include "Vec3.h"

class BBox
{
public:
  BBox(
    float xmin = -1000.0f, 
    float xmax = 1000.0f, 
    float ymin = -1000.0f, 
    float ymax = 1000.0f, 
    float zmin = -1000.0f, 
    float zmax = 1000.0f);

  void Set(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
  
  // Set values which are lower than the mins or greater than maxes.
  // I.e. enlarge the box to contain (x, y, z) if necessary.
  void SetIf(float x, float y, float z);

  void Draw() const;

  // Make an octree child.
  // Create a box which is 1/8 the volume of this box. The octant
  // parameter specifies the position of the sub-box within this one.
  // Valid values for octant are 0..7 incl.
  BBox MakeOctChild(int octant) const;

  // Returns true if the given vertex is inside this box.
  bool Contains(const Vec3f& v) const;

  bool CollidesSphere(float radius, Vec3f& pos);
  Vec3f Middle();

private:
  float m_xmin, m_xmax, m_ymin, m_ymax, m_zmin, m_zmax;
};

#endif
