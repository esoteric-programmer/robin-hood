#ifndef ROBIN_INCLUDED
#define ROBIN_INCLUDED

#include <3ds.h>
#include <sf2d.h>

#include "Fallable.h"
#include "ArrowList.h"
#include "Sound.h"

class CRobin : public CFallable {

private:
	bool can_move;
	bool was_moving_right;
	bool was_moving_left;
	CArrowList* arrowlist;
	bool shooting;
	bool jumping;
	u16 shoot_wait_time;
	u16 shoot_interval;
	CLandscapeList* landscapelist_backup;
	CSound* jump_snd; 
	CSound* shoot_snd;

public:
	CRobin(s16 start_x, s16 start_y, CTexture* textures[], u16 number_of_textures, u16 time_per_frame, Rect bounding_box, float pixel_per_step, CLandscapeList* landscapelist, s16 landscape_width, s16 landscape_height, float g, CArrowList* arrowlist, u16 shoot_interval, CSound* jump, CSound* shoot);
	void walk(float direction);
	void shoot();
	void jump();
	void force_dying();
	void reset(s16 start_x, s16 start_y, s16 landscape_width, s16 landscape_height);
	void update(u16 time_steps);
	virtual ~CRobin();

};

#endif

