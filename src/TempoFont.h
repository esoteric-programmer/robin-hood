#ifndef TEMPO_FONT_INCLUDED
#define TEMPO_FONT_INCLUDED

#include <3ds.h>
#include <sf2d.h>
#include "Texture.h"
#include "physics.h" // Rect

typedef struct {
	s16 texture_offset;
	s16 texture_width;
	s16 text_x_offset;
	s16 text_y_offset;
	s16 text_reserved_width;
} Glyph;

typedef struct {
	const RawImage* alpha_map;
	Glyph ascii_glyphs[95];
} Font;

typedef struct {
	u8 r;
	u8 g;
	u8 b;
} Color;

enum Alignment {
	LEFT,
	RIGHT,
	CENTER,
	JUSTIFY, // not implemented yet
};

Font create_tempo_font();
// returned CTexture* contains the string. It may be deleted when the scene is drawn completely.
// TODO: create (static) list and delete it automatically (next time a string should be drawn and by cleanup method)
CTexture* draw_string(const char* string, Font font, Color color, s16 x, s16 y, Alignment alignment = Alignment::LEFT);
Rect get_string_bounding_box(const char* string, Font font, bool ignore_overflow = false);

#endif

