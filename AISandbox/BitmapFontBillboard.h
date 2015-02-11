#ifndef BITMAP_FONT_BILLBOARD_H_INCLUDED
#define BITMAP_FONT_BILLBOARD_H_INCLUDED
#include "Texture.h"
#include "Vec3.h"
class BitmapFontBillboard
{
public:
	BitmapFontBillboard();
	bool Load(const std::string& file, int cellW, int cellH, float sqrS);
	void Draw(const std::string& words,const Vec3f& pos,float size)const;
private:
	Texture tex_;
	Vec2i cellNum_;
	Vec2f cellSize_;
	float squareSize_;
};



#endif