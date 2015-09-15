#ifndef ENEMY_INCLUDED
#define ENEMY_INCLUDED

#include <3ds.h>
#include <sf2d.h>

#include "Fallable.h"
#include "ArrowList.h"
#include "Sound.h"

class CEnemy : public CFallable {

private:
	bool current_walking_direction_left;
	CArrowList* attacklist;
	u16 shoot_wait_time;
	u16 shoot_interval; // 0 -> is not shooting
	s16 left_walking_border; 
	s16 right_walking_border;
	CSound* attack_snd;

public:
	CEnemy(s16 start_x, s16 start_y, CTexture* textures[], u16 number_of_textures, u16 time_per_frame, Rect bounding_box, float pixel_per_step, CLandscapeList* landscapelist, s16 left_walking_border, s16 right_walking_border, float g, CArrowList* attacklist, u16 shoot_interval, bool starts_walking_left, CSound* attack_snd);
	void force_dying();
	void update(u16 time_steps);
	virtual ~CEnemy();

};

#endif

