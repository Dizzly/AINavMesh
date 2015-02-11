#include "BBox.h"
#include "Vec3.h"
#include <windows.h>
#include <GL/gl.h>

BBox::BBox(
  float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) :
  m_xmin(xmin), m_xmax(xmax), 
  m_ymin(ymin), m_ymax(ymax), 
  m_zmin(zmin), m_zmax(zmax)
{
}

bool BBox::CollidesSphere(float radius, Vec3f& pos)
{
	return BBox(m_xmin-radius,
		m_xmax+radius,
		m_ymin-radius,
		m_ymax+radius,
		m_zmin-radius,
		m_zmax+radius).Contains(pos);
}
void DrawLine(const Vec3f& v1, const Vec3f& v2)
{
  glDisable(GL_TEXTURE_2D);
  glBegin(GL_LINES);
  glVertex3f(v1.x, v1.y, v1.z);
  glVertex3f(v2.x, v2.y, v2.z);
  glEnd();
  glEnable(GL_TEXTURE_2D);
}

Vec3f BBox::Middle()
{
	return Vec3f((m_xmax-m_xmin)/2,
		(m_ymax-m_ymin)/2,
		(m_zmax-m_zmin)/2);

}
void BBox::Draw() const
{
  DrawLine(Vec3f(m_xmin, m_ymin, m_zmin), 
                   Vec3f(m_xmax, m_ymin, m_zmin));

  DrawLine(Vec3f(m_xmax, m_ymin, m_zmin), 
                   Vec3f(m_xmax, m_ymin, m_zmax));

  DrawLine(Vec3f(m_xmax, m_ymin, m_zmax), 
                   Vec3f(m_xmin, m_ymin, m_zmax));

  DrawLine(Vec3f(m_xmin, m_ymin, m_zmax), 
                   Vec3f(m_xmin, m_ymin, m_zmin));

  DrawLine(Vec3f(m_xmin, m_ymax, m_zmin), 
                   Vec3f(m_xmax, m_ymax, m_zmin));

  DrawLine(Vec3f(m_xmax, m_ymax, m_zmin), 
                   Vec3f(m_xmax, m_ymax, m_zmax));

  DrawLine(Vec3f(m_xmax, m_ymax, m_zmax), 
                   Vec3f(m_xmin, m_ymax, m_zmax));

  DrawLine(Vec3f(m_xmin, m_ymax, m_zmax), 
                   Vec3f(m_xmin, m_ymax, m_zmin));

  DrawLine(Vec3f(m_xmin, m_ymin, m_zmin), 
                   Vec3f(m_xmin, m_ymax, m_zmin));

  DrawLine(Vec3f(m_xmax, m_ymin, m_zmin), 
                   Vec3f(m_xmax, m_ymax, m_zmin));

  DrawLine(Vec3f(m_xmax, m_ymin, m_zmax), 
                   Vec3f(m_xmax, m_ymax, m_zmax));

  DrawLine(Vec3f(m_xmin, m_ymin, m_zmax), 
                   Vec3f(m_xmin, m_ymax, m_zmax));
}

BBox BBox::MakeOctChild(int octant) const
{
    // Centre of box
    float cx = (m_xmin + m_xmax) / 2.0f; 
    float cy = (m_ymin + m_ymax) / 2.0f; 
    float cz = (m_zmin + m_zmax) / 2.0f; 

    float xmin = m_xmin, xmax = m_xmax, ymin = m_ymin, ymax = m_ymax, zmin = m_zmin, zmax = m_zmax;
    if (octant & 1)
    {
        xmin = cx;
    }
    else
    {
        xmax = cx;
    }
    if (octant & 2)
    {
        ymin = cy;
    }
    else
    {
        ymax = cy;
    }
    if (octant & 4)
    {
        zmin = cz;
    }
    else
    {
        zmax = cz;
    }

    return BBox(xmin, xmax, ymin, ymax, zmin, zmax);
}

bool BBox::Contains(const Vec3f& v) const
{
    return (
        v.x >= m_xmin && v.x < m_xmax &&
        v.y >= m_ymin && v.y < m_ymax &&
        v.z >= m_zmin && v.z < m_zmax
    );
}

