#include <string.h>

#include "TempoFont.h"
#include "Texture.h"
extern const RawImage TEMPO_FONT; // 300.cpp

Rect draw_string_bb(const char* string, Font font, Color color, s16 x, s16 y, Alignment alignment, bool draw, bool bb_ignore_overflow, CTexture*& created_texture);

Font create_tempo_font() {

	Font tempo = {&TEMPO_FONT, {
		// if 300.cpp is updated, the following lines must be updated, too.
		// texture_offset can be computed from texture_width and need not be set here.
		{0, 5, 0, 0, 5}, // SPACE
		{0, 6, 0, 0, 6}, // !
		{0, 7, 0, 0, 7}, // "
		{0, 9, 0, 0, 9}, // #
		{0, 9, 0, -1, 9}, // $
		{0, 15, 0, 0, 15}, // %
		{0, 14, 0, 0, 14}, // &
		{0, 3, 0, 0, 3}, // '
		{0, 6, 0, 0, 5}, // (
		{0, 6, 0, 0, 5}, // )
		{0, 9, 0, 0, 9}, // *
		{0, 10, 0, 0, 10}, // +
		{0, 5, 0, 0, 5}, // ,
		{0, 6, 0, 0, 6}, // -
		{0, 5, 0, 0, 5}, // .
		{0, 6, 0, 0, 5}, // /
		{0, 9, 0, 0, 9}, // 0
		{0, 9, 0, 0, 9}, // 1
		{0, 9, 0, 0, 9}, // 2
		{0, 9, 0, 0, 9}, // 3
		{0, 9, 0, 0, 9}, // 4
		{0, 9, 0, 0, 9}, // 5
		{0, 9, 0, 0, 9}, // 6
		{0, 9, 0, 0, 9}, // 7
		{0, 9, 0, 0, 9}, // 8
		{0, 9, 0, 0, 9}, // 9
		{0, 5, 0, 0, 5}, // :
		{0, 5, 0, 0, 5}, // ;
		{0, 10, 0, 0, 10}, // <
		{0, 10, 0, 0, 10}, // =
		{0, 10, 0, 0, 10}, // >
		{0, 8, 0, 0, 8}, // ?
		{0, 17, 0, -1, 17}, // @
		{0, 13, 0, 0, 13}, // A
		{0, 12, 0, 0, 12}, // B
		{0, 12, 0, 0, 12}, // C
		{0, 13, 0, 0, 13}, // D
		{0, 11, 0, 0, 11}, // E
		{0, 10, 0, 0, 10}, // F
		{0, 13, 0, 0, 13}, // G
		{0, 13, 0, 0, 13}, // H
		{0, 6, 0, 0, 6}, // I
		{0, 7, 0, 0, 7}, // J
		{0, 13, 0, 0, 13}, // K
		{0, 11, 0, 0, 11}, // L
		{0, 16, 0, 0, 16}, // M
		{0, 13, 0, 0, 13}, // N
		{0, 13, 0, 0, 13}, // O
		{0, 10, 0, 0, 10}, // P
		{0, 13, 0, 0, 13}, // Q
		{0, 12, 0, 0, 12}, // R
		{0, 10, 0, 0, 10}, // S
		{0, 11, 0, 0, 11}, // T
		{0, 13, 0, 0, 13}, // U
		{0, 13, 0, 0, 13}, // V
		{0, 17, 0, 0, 17}, // W
		{0, 13, 0, 0, 13}, // X
		{0, 13, 0, 0, 13}, // Y
		{0, 11, 0, 0, 11}, // Z
		{0, 6, 0, 0, 6}, // [
		{0, 8, -1, 0, 6}, // BACKSLASH 
		{0, 6, 0, 0, 6}, // ]
		{0, 8, 0, 0, 8}, // ^
		{0, 9, 0, 0, 9}, // _
		{0, 6, 0, 0, 6}, // `
		{0, 8, 0, 0, 8}, // a
		{0, 9, 0, 0, 9}, // b
		{0, 8, 0, 0, 8}, // c
		{0, 9, 0, 0, 9}, // d
		{0, 8, 0, 0, 8}, // e
		{0, 7, 0, 0, 6}, // f
		{0, 9, 0, 0, 9}, // g
		{0, 9, 0, 0, 9}, // h
		{0, 5, 0, 0, 5}, // i
		{0, 5, 0, 0, 5}, // j
		{0, 9, 0, 0, 9}, // k
		{0, 5, 0, 0, 5}, // l
		{0, 14, 0, 0, 14}, // m
		{0, 9, 0, 0, 9}, // n
		{0, 9, 0, 0, 9}, // o
		{0, 9, 0, 0, 9}, // p
		{0, 9, 0, 0, 9}, // q
		{0, 6, 0, 0, 6}, // r
		{0, 7, 0, 0, 7}, // s
		{0, 5, 0, 0, 5}, // t
		{0, 9, 0, 0, 9}, // u
		{0, 9, 0, 0, 9}, // v
		{0, 13, 0, 0, 13}, // w
		{0, 9, 0, 0, 9}, // x
		{0, 9, 0, 0, 9}, // y
		{0, 8, 0, 0, 8}, // z
		{0, 9, 0, 0, 9}, // {
		{0, 4, 0, 0, 4}, // |
		{0, 9, 0, 0, 9}, // }
		{0, 10, 0, 0, 10}, // ~		
	}};
	// fix texture_offsets
	s16 texture_offset = 0;
	for (s16 i=0;i<95;i++) {
		tempo.ascii_glyphs[i].texture_offset = texture_offset;
		texture_offset += tempo.ascii_glyphs[i].texture_width;
	}
	return tempo;
}

Rect get_string_bounding_box(const char* string, Font font, bool ignore_overflow) {
	Color color = {0,0,0};
	CTexture* created_texture;
	return draw_string_bb(string, font, color, 0, 0, Alignment::LEFT, false, ignore_overflow, created_texture);
}

CTexture* draw_string(const char* string, Font font, Color color, s16 x, s16 y, Alignment alignment) {
	CTexture* created_texture = 0;
	draw_string_bb(string, font, color, x, y, alignment, true, true, created_texture);
	return created_texture;
}

Rect draw_string_bb(const char* string, Font font, Color color, s16 x, s16 y, Alignment alignment, bool draw, bool bb_ignore_overflow, CTexture*& created_texture) {
	created_texture = 0;
	if (alignment == Alignment::JUSTIFY)
		alignment = Alignment::LEFT; // justify not supported
	Rect ret = {0,0,0,0};
	if (font.alpha_map == 0)
		return ret;
	if (font.alpha_map->pixel_data == 0 || string == 0)
		return ret;

	if (font.alpha_map->bytes_per_pixel != 1) {
		return ret; // not supported
	}

	// calculate size
	Rect bounding_box = {0,0,0,0};
	s16 x_offset = 0;
	s16 y_offset = 0;
	s16 most_right_reserved = 0;
	s16 most_right_reserved_line = 0;
	s16 most_right_line = 0;
	s16 most_right_overflow = 0;
	// most right overflow bestimmen: größte differenz zwischen reserviertem und tatsächlichem bedarf in einer zeile
	// x2-wert bestimmen: summe aus most_right_reserved und most right overflow (andernfalls droht alignment == RIGHT) in sonderfällen fehlzuschlagen!)
	const char* it = string;
	while (*it != 0) {
		if (*it >= 32 && *it <= 126) {
			// PRINTABLE ASCII
			if (x_offset + font.ascii_glyphs[(*it)-32].text_x_offset + font.ascii_glyphs[(*it)-32].texture_width > bounding_box.x2)
				bounding_box.x2 = x_offset + font.ascii_glyphs[(*it)-32].text_x_offset + font.ascii_glyphs[(*it)-32].texture_width;
			if (x_offset + font.ascii_glyphs[(*it)-32].text_x_offset + font.ascii_glyphs[(*it)-32].texture_width > most_right_line)
				most_right_line = x_offset + font.ascii_glyphs[(*it)-32].text_x_offset + font.ascii_glyphs[(*it)-32].texture_width;
			if (y_offset + (s16)font.ascii_glyphs[(*it)-32].text_y_offset + (s16)font.alpha_map->height > bounding_box.y2)
				bounding_box.y2 = y_offset + font.ascii_glyphs[(*it)-32].text_y_offset + font.alpha_map->height;
			if (x_offset + font.ascii_glyphs[(*it)-32].text_x_offset < bounding_box.x1)
				bounding_box.x1 = x_offset + font.ascii_glyphs[(*it)-32].text_x_offset;
			if (y_offset + font.ascii_glyphs[(*it)-32].text_y_offset < bounding_box.y1)
				bounding_box.y1 = y_offset + font.ascii_glyphs[(*it)-32].text_y_offset;
			
			x_offset += font.ascii_glyphs[(*it)-32].text_x_offset + font.ascii_glyphs[(*it)-32].text_reserved_width;
			if (x_offset > most_right_reserved)
				most_right_reserved = x_offset;
			if (x_offset > most_right_reserved_line)
				most_right_reserved_line = x_offset;
		} else if (*it == '\n') {
			// LINE BREAK
			y_offset += font.alpha_map->height + font.alpha_map->height/4;
			x_offset = 0;
			if (bounding_box.y2 < y_offset) {
			  bounding_box.y2 = y_offset;
			}
			if (most_right_overflow < most_right_line - most_right_reserved_line)
				most_right_overflow = most_right_line - most_right_reserved_line;
			most_right_reserved_line = 0;
			most_right_line = 0;
		}
		it++;
	}
	if (most_right_overflow < most_right_line - most_right_reserved_line)
		most_right_overflow = most_right_line - most_right_reserved_line;
	bounding_box.x2 = most_right_reserved + most_right_overflow;
	

	
	memcpy(&ret, &bounding_box, sizeof(Rect));
	if (bb_ignore_overflow == true) {
		ret.x2 = most_right_reserved;
		ret.x1 = 0;
	}
	if (!draw) {
		return ret;
	}
	
	if (bounding_box.x2 <= bounding_box.x1 || bounding_box.y2 <= bounding_box.y1)
		return ret; // nothing to do


	// create colored raw image, alpha-values = 0
	RawImage textured_string = {
			(u16)(bounding_box.x2 - bounding_box.x1), // width
			(u16)(bounding_box.y2 - bounding_box.y1), // height
			4, // bytes per pixel
			0};
	char* textured_string_data = new char[textured_string.width * textured_string.height * textured_string.bytes_per_pixel];
	if (textured_string_data == 0) {
		return ret; // not enough memory
	}

	for (u16 i=0; i<textured_string.width * textured_string.height; i++) {
		textured_string_data[4*i] = color.r;
		textured_string_data[4*i+1] = color.g;
		textured_string_data[4*i+2] = color.b;
		textured_string_data[4*i+3] = 0; // alpha
	}

	// add gylphs to alpha values
	y_offset = -bounding_box.y1;
	bool x_offset_calculated = false;
	it = string;
	while (*it != 0) {
		if (!x_offset_calculated) {
			if (alignment == Alignment::RIGHT) {
				// get current line width
				const char* it2 = it;
				s16 cur_line_width = 0;
				s16 max_line_width = 0;
				while (*it2 != 0) {
					if (*it2 == '\n')
						break;
					if (*it2 >= 32 && *it2 <= 126) {
						cur_line_width += font.ascii_glyphs[(*it2)-32].text_x_offset + font.ascii_glyphs[(*it2)-32].text_reserved_width;
						if (max_line_width < cur_line_width) {
							max_line_width = cur_line_width;
						}
					}
					it2++;
				}
				// calculate difference to max_width and get starting offset...
				x_offset = -bounding_box.x1 + most_right_reserved - max_line_width;
				// most_right_reserved - max_line_width scheint zu versagen...?
			}else{ // TODO: alignment: CENTER
				// alignment: LEFT
				x_offset = -bounding_box.x1;
			}
			x_offset_calculated = true;
		}
		if (*it >= 32 && *it <= 126) {
			// PRINTABLE ASCII
			// ADD TO ALPHA CHANNEL
			for (s16 y=0; y<(s16)font.alpha_map->height; y++) {
				for (s16 x=0; x<font.ascii_glyphs[(*it)-32].texture_width; x++) {
					// font.ascii_glyphs[(*it)-32].
					u8 pix_val = font.alpha_map->pixel_data[((x+font.ascii_glyphs[(*it)-32].texture_offset) + font.alpha_map->width*y)];
					s16 pix_pos_x = x + x_offset + font.ascii_glyphs[(*it)-32].text_x_offset;
					s16 pix_pos_y = y + y_offset + font.ascii_glyphs[(*it)-32].text_y_offset;
					char* pix = textured_string_data + 4*(pix_pos_x + textured_string.width*pix_pos_y)+3;
					if (((u16)(*pix) + (u16)pix_val) > 255)
						(*pix) = 255;
					else
						(*pix) += pix_val;
				}
			}
			x_offset += font.ascii_glyphs[(*it)-32].text_x_offset + font.ascii_glyphs[(*it)-32].text_reserved_width;
		} else if (*it == '\n') {
			// LINE BREAK
			y_offset += font.alpha_map->height + font.alpha_map->height/4;
			x_offset_calculated = false;
		}
		it++;
	}
	textured_string.pixel_data = textured_string_data;

	// create texture
	created_texture = new CTexture(textured_string);
	if (created_texture == 0) {
		// failed to create texture
		delete textured_string_data;
		return ret;
		
	}


	// draw texture
	if (alignment == Alignment::RIGHT) {
		x -= most_right_reserved;
	} else if (alignment == Alignment::CENTER) {
		x -= most_right_reserved/2;
	}
	created_texture->draw(x + bounding_box.x1, y + bounding_box.y1);
	
	// delete raw image
	delete textured_string_data;
	
	// SUCCESS!
	return ret;
}


