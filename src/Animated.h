#ifndef ANIMATED_INCLUDED
#define ANIMATED_INCLUDED

#include <3ds.h>
#include <sf2d.h>

#include "Drawable.h"
#include "Texture.h"
#include "physics.h"

class CAnimated : public CDrawable {

private:
	CTexture** textures;
	u16 current_frame;
	u16 number_of_frames;
	u16 time_per_frame;
	u16 current_frame_time_gone;
	bool paused;
	Rect size;

protected:
	void pause();
	void stop(u16 frame = 0);
	void play();
	Rect get_drawable_size();
	

public:
	CAnimated(s16 start_x, s16 start_y, CTexture** textures, u16 number_of_textures, u16 time_per_frame, bool mirrored = false);
	virtual void draw(s16 screen_offset_x, s16 screen_offset_y);
	virtual void update(u16 time_steps);
	Vector get_middle_point();
	virtual ~CAnimated();

};

#endif

