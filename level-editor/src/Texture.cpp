#include "Texture.h"
#include "tools.h"

CTexture::CTexture(RawImage img) {
	if (img.bytes_per_pixel != 4) {
		this->texture = 0; // not supported
		this->width = 0;
		this->height = 0;
	}
	this->width = img.width;
	this->height = img.height;
	this->texture = rgba_sf(this->width, this->height);
	if (this->texture == NULL) {
		this->width = 0;
		this->height = 0;
	}
	memcpy(this->texture->pixels, img.pixel_data, 4*img.width*img.height);
}

void CTexture::draw(Sint32 x, Sint32 y, SDL_Surface* screen, bool mirrored, bool origin_top) {
	if (this->texture == 0)
		return;
	// TODO: check if inside screen
	
	SDL_Rect pos;
	pos.x = x;
	pos.y = (origin_top?y:screen->h-y-this->height);
	if (!mirrored) {
		SDL_BlitSurface(this->texture, 0, screen, &pos);
	}else{
		pos.x += this->width;
		pos.w = -this->width;
		pos.h = this->height;
		SDL_BlitScaled(this->texture, 0, screen, &pos);
	}
}

void CTexture::draw_scaled(SDL_Rect pos, SDL_Surface* screen, bool origin_top) {
	if (this->texture == 0)
		return;
	// TODO: check if inside screen
	
	pos.y = (origin_top?pos.y:screen->h-pos.y-pos.h);
	SDL_BlitScaled(this->texture, 0, screen, &pos);
}

unsigned int CTexture::get_width() {
	if (this->texture == 0)
		return 0;
	return this->width;
}

unsigned int CTexture::get_height() {
	if (this->texture == 0)
		return 0;
	return this->height;
}

Uint32 CTexture::pixel_at(Sint32  x, Sint32 y) {
	// this function may be faulty -> TODO: fix it
	/*if (this->texture == 0)
		return 0;
	if (this->texture->data == 0)
		return 0;
	if (x < 0 || y < 0 || x >= this->texture->width || y >= this->texture->height)
		return 0;
	return ((u32 *)this->texture->data)[y*this->texture->pow2_w + x];*/
	return false;
}

CTexture::~CTexture() {
	if (this->texture != 0) {
		SDL_FreeSurface(this->texture);
	}
}

