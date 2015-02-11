#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include "Vec2.h"
#include <SDL.h>
#include <gl/glut.h>
#include <string>
class Texture
{
public:
	Texture();
	~Texture();
	bool Load(const std::string& file);
	bool Load32Pixes(SDL_Surface*);
	void FreeTexture();
	void Begin()const;
	void End()const;
	int GetID();
	Vec2f GetSize();
private:
	GLuint id_;
	int width_, height_;
};

#endif