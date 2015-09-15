#ifndef DRAWABLE_INCLUDED
#define DRAWABLE_INCLUDED

#include <3ds.h>

class CDrawable {
private:
	bool mirrored;
	s16 x, y;

protected:
	CDrawable(s16 start_x, s16 start_y, bool mirrored = false);
	s16 get_x();
	s16 get_y();
	void set_mirrored(bool);
	bool get_mirrored();
	virtual void add_to_position(s16 x, s16 y);

public:
	virtual void draw(s16 screen_offset_x, s16 screen_offset_y) = 0;
	virtual void update(u16 time_steps) = 0;
	virtual ~CDrawable();

};

#endif

