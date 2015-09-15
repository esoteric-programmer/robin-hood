#ifndef COLLIDABLE_INCLUDED
#define COLLIDABLE_INCLUDED

#include <3ds.h>
#include <sf2d.h>

#include "Animated.h"
#include "physics.h"

class CCollidable : public CAnimated {

private:
	Rect bounding_box;

protected:
	Rect get_bounding_box();

public:
	enum ObjectArea {
		WHOLE_OBJECT,
		LEFT_EDGE,
		RIGHT_EDGE,
		TOP_EDGE,
		BOTTOM_EDGE
	};

	CCollidable(s16 start_x, s16 start_y, CTexture** textures, u16 number_of_textures, u16 time_per_frame, Rect bounding_box, bool mirrored = false);
	bool check_collision(IntVector position, Rect bounding_box, ObjectArea detection_area = ObjectArea::WHOLE_OBJECT);
	bool check_collision(CCollidable*);
	virtual void set_position(s16 x, s16 y);
	s16 get_top();
	s16 get_bottom();
	s16 get_left();
	s16 get_right();

};

#endif

