#ifndef TEXTURE_INCLUDED
#define TEXTURE_INCLUDED

#include <3ds.h>
#include <sf2d.h>

typedef struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel;
  const char*	 pixel_data;
} RawImage;

class CTexture {
private:
	sf2d_texture* texture;
	unsigned int width;
	unsigned int height;

public:
	CTexture(RawImage);
	void draw(s16 x, s16 y, bool mirrored = false);
	u16 get_width();
	u16 get_height();
	u32 pixel_at(s16 x, s16 y); // don't use this function! it may be faulty
	~CTexture();

};

#endif

