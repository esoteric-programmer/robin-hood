#include "Texture.h"

CTexture::CTexture(RawImage img) {
	if (img.bytes_per_pixel != 4) {
		this->texture = 0; // not supported
		this->width = 0;
		this->height = 0;
	}
	this->width = img.width;
	this->height = img.height;
	this->texture = sf2d_create_texture(img.width, img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	sf2d_fill_texture_from_RGBA8(this->texture, img.pixel_data, img.width, img.height);
	sf2d_texture_tile32(this->texture);
}

void CTexture::draw(s16 x, s16 y, bool mirrored) {
	if (this->texture == 0)
		return;
	// TODO: check if inside screen
	if (!mirrored) {
		sf2d_draw_texture(this->texture, x, y);
	}else{
		sf2d_draw_texture_scale(this->texture, x + this->width, y, -1.0f, 1.0f);
	}
	// maybe sf2d_draw_texture_part ??
}

u16 CTexture::get_width() {
	if (this->texture == 0)
		return 0;
	return this->width;
}

u16 CTexture::get_height() {
	if (this->texture == 0)
		return 0;
	return this->height;
}

u32 CTexture::pixel_at(s16 x, s16 y) {
	// this function may be faulty -> TODO: fix it
	if (this->texture == 0)
		return 0;
	if (x < 0 || y < 0 || x >= this->texture->width || y >= this->texture->height)
		return 0;
	return sf2d_get_pixel(this->texture, x, y);
}

CTexture::~CTexture() {
	if (this->texture != 0) {
		sf2d_free_texture(this->texture);
	}
}

