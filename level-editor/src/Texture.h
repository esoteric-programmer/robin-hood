#ifndef TEXTURE_INCLUDED
#define TEXTURE_INCLUDED

#include <SDL2/SDL.h>

typedef struct {
  int 	 width;
  int 	 height;
  unsigned int 	 bytes_per_pixel;
  const char*	 pixel_data;
} RawImage;

class CTexture {
private:
	SDL_Surface* texture;
	unsigned int width;
	unsigned int height;

public:
	CTexture(RawImage);
	void draw(Sint32 x, Sint32 y, SDL_Surface* screen, bool mirrored = false, bool origin_top = false);
	void draw_scaled(SDL_Rect pos, SDL_Surface* screen, bool origin_top = false);
	unsigned int get_width();
	unsigned int get_height();
	Uint32 pixel_at(Sint32 x, Sint32 y); // don't use this function! it may be faulty
	~CTexture();

};

#endif

