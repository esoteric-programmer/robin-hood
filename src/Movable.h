#ifndef MOVABLE_INCLUDED
#define MOVABLE_INCLUDED

#include <3ds.h>
#include <sf2d.h>

#include "Collidable.h"
#include "LandscapeList.h"

class CMovable : public CCollidable {

private:
	float pixel_per_step;
	float moving_percentage;
	float x_change_residue;
	CLandscapeList* landscapelist;
	s16 landscape_width;

protected:
	void set_moving(float percentage); //-1.0: move left; 0.0: stop; 1.0: move right; values between: move slow

public:
	CMovable(s16 start_x, s16 start_y, CTexture* textures[], u16 number_of_textures, u16 time_per_frame, Rect bounding_box, float pixel_per_step, bool mirrored = false, float start_moving_percentage = 0.0f, CLandscapeList* landscapelist = 0, s16 landscape_width = -1);
	virtual void update(u16 time_steps);
	virtual void set_position(s16 x, s16 y);
	void reset(s16 landscape_width);
	virtual ~CMovable();


};

#endif

