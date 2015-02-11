#include "BitmapFontBillboard.h"


BitmapFontBillboard::BitmapFontBillboard()
{
squareSize_=0;
}

bool BitmapFontBillboard::Load(const std::string& file, int cellXNum, int cellYNum, float cellSize)
{
	cellNum_.x=cellXNum;
	cellNum_.y=cellYNum;
	cellSize_.x=1.0f/(float)cellXNum;
	cellSize_.y=1.0f/(float)cellYNum;
	squareSize_=cellSize;
	if(tex_.Load(file))
	{
		return true;
	}
	return false;
}

void BitmapFontBillboard::Draw(const std::string& words,const Vec3f& pos,float size)const
{
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	float offset=0;
	float offY=0;
	float f[16];
	glGetFloatv(GL_PROJECTION_MATRIX,f);
	Vec3f right(f[0],f[4],f[8]);
	Vec3f up(f[1],f[5],f[9]);
	right*=size;
	up*=size;


	tex_.Begin();

	for(int i=0;i<words.size();++i)
	{
		glPushMatrix();
		glTranslatef(right.x*(2*offset),right.y*(2*offset),right.z*(2*offset));
		int ascii=words[i];
		if(ascii==(int)'\n')
		{
			--offY;
			offset=0;
			continue;
		}
		float x=(ascii%cellNum_.x)*cellSize_.x;
		float y=(ascii/cellNum_.x)*cellSize_.y;
		Vec3f corners[4]=
		{
			((right))+((up)),
			((right))-((up)),
			-((right))-((up)),
			-((right))+((up))
		
		};
		glBegin(GL_QUADS);
		{
			glTexCoord2f(x+cellSize_.x,y);
			glVertex3f(corners[0].x,corners[0].y,corners[0].z);
			glTexCoord2f(x+cellSize_.x,y+cellSize_.y);
			glVertex3f(corners[1].x,corners[1].y,corners[1].z);
			glTexCoord2f(x,y+cellSize_.y);
			glVertex3f(corners[2].x,corners[2].y,corners[2].z);
			glTexCoord2f(x,y);
			glVertex3f(corners[3].x,corners[3].y,corners[3].z);
		}
		glEnd();
		offset+=1;
		glPopMatrix();
	}
	tex_.End();

	glPopMatrix();
}