#ifndef BUTTON_INCLUDED
#define BUTTON_INCLUDED

#include <3ds.h>
#include <sf2d.h>

#include "Drawable.h"
#include "Texture.h"

class CButton : public CDrawable {
public:
	enum ButtonState {
		NORMAL = 0,
		SELECTED = 1,
		ACTIVE = 2,
		DISABLED = 3,
	};

private:
	CTexture** button_textures;
	CTexture** text_textures;
	u16 number_of_text_textures;
	u16 number_of_button_textures;
	ButtonState state;
	bool arrow_button;
	bool mirrored = false;
	
	u16 get_texture_index();

public:
	CButton(s16 button_y_pos, CTexture** button_textures, CTexture** text_textures, u16 number_of_textures_each, bool enabled, bool arrow_button = false, bool mirrored = false);
	bool is_at(u16 x, u16 y, s16 screen_offset_y = 0);
	void set_state(ButtonState state);
	ButtonState get_state();
	bool is_enabled();
	void set_text(CTexture** text_textures, u16 number_of_textures);
	virtual void draw(s16 screen_offset_x, s16 screen_offset_y);
	virtual void update(u16 time_steps = 1);
	virtual ~CButton();

};

#endif

