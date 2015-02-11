#include "Texture.h"
#include <SDL_image.h>
#include <assert.h>
Texture::Texture()
{
	id_=0;
	width_=0;
	height_=0;
}

Texture::~Texture()
{
	FreeTexture();
}

bool Texture::Load(const std::string& file)
{
	SDL_Surface* s = IMG_Load(file.c_str());
	assert(s);
	return Load32Pixes(s);
}
bool Texture::Load32Pixes(SDL_Surface* surface)
{
	FreeTexture();
	unsigned char* data=(unsigned char*)surface->pixels;
	width_=surface->w;
	height_=surface->h;
	int bpp=surface->format->BytesPerPixel;
	int format=GL_RGB;
	if(bpp==4)
	{
	format=GL_RGBA;
	}

	glGenTextures(1,&id_);
	glBindTexture(GL_TEXTURE_2D, id_);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		format,
		width_,
		height_,
		0,
		format,
		GL_UNSIGNED_BYTE,
		data);

	gluBuild2DMipmaps(
		GL_TEXTURE_2D,
		format,
		width_,
		height_,
		format,
		GL_UNSIGNED_BYTE,
		data);


	glTexParameterf(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR);

	SDL_FreeSurface(surface);

	glBindTexture(GL_TEXTURE_2D,NULL);
	return true;
}

void Texture::FreeTexture()
{
	if(id_!=0)
	{
		glDeleteTextures(1,&id_);
		id_=0;
	}
	width_=0;
	height_=0;
}

void Texture::Begin()const
{
	if(id_!=0)
	{
	glBindTexture(GL_TEXTURE_2D,id_);
	}
}

void Texture::End()const
{
	glBindTexture(GL_TEXTURE_2D,NULL);
}
