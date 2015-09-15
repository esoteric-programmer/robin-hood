#ifndef FALLABLE_INCLUDED
#define FALLABLE_INCLUDED

#include <3ds.h>
#include <sf2d.h>

#include "Movable.h"
#include "LandscapeList.h"

class CFallable : public CMovable {

private:
	CLandscapeList* landscapelist;
	float current_fallspeed;
	float g;
	float y_float;
	bool staying_on_ground;
	bool fallen_down;
	s16 landscape_height;
	bool ghost;

protected:
	void set_current_fallspeed(float speed);
	bool stays_on_ground();
	void force_falling();
	void set_landscapelist(CLandscapeList* landscapelist);

public:
	CFallable(s16 start_x, s16 start_y, CTexture* textures[], u16 number_of_textures, u16 time_per_frame, Rect bounding_box, float pixel_per_step, CLandscapeList* landscapelist, s16 landscape_width, s16 landscape_height, float g, bool ghost = false);
	bool left_landscape();
	virtual void set_position(s16 x, s16 y);
	virtual void update(u16 time_steps);
	virtual void reset(s16 landscape_width, s16 landscape_height);
	virtual ~CFallable();

};

#endif

