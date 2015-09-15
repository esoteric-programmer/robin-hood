#include "Enemy.h"

CEnemy::CEnemy(s16 start_x, s16 start_y, CTexture* textures[], u16 number_of_textures, u16 time_per_frame, Rect bounding_box, float pixel_per_step, CLandscapeList* landscapelist, s16 left_walking_border, s16 right_walking_border, float g, CArrowList* attacklist, u16 shoot_interval, bool starts_walking_left, CSound* attack_snd)
		: CFallable(start_x, start_y, textures, number_of_textures, time_per_frame, bounding_box, pixel_per_step, landscapelist, -1, -1, g, true) {
	this->current_walking_direction_left = starts_walking_left;
	this->attacklist = attacklist;
	this->shoot_wait_time = 0;
	this->shoot_interval = shoot_interval;
	this->left_walking_border = left_walking_border;
	this->right_walking_border = right_walking_border;
	this->attack_snd = attack_snd;
}

void CEnemy::force_dying() {
	// increment y value by one => will fall down
	this->force_falling();
}


void CEnemy::update(u16 time_steps) {
	if (this->left_landscape())
		return;
	// DIRECTION...
	if (current_walking_direction_left)
		this->set_moving(-1.0f);
	else
		this->set_moving(1.0f);
	CFallable::update(time_steps);
	
	if (this->get_x() < this->left_walking_border) {
		this->add_to_position(this->left_walking_border-this->get_x(), 0);
		current_walking_direction_left = false;
	} else if (this->get_x() + this->get_drawable_size().x2 > this->right_walking_border) {
		this->add_to_position(this->right_walking_border-this->get_drawable_size().x2-this->get_x(), 0);
		current_walking_direction_left = true;
	}
	
	if (this->shoot_wait_time <= time_steps) {
		this->shoot_wait_time = 0;
	}else{
		this->shoot_wait_time -= time_steps;
	}
	if (this->shoot_interval > 0 && this->shoot_wait_time == 0) {
		if (this->attacklist != 0) {
			s16 x_pos;
			if (this->get_mirrored()) {
				x_pos = this->get_x()+ 40 - (30 + 5); // 40: ENEMY.width; 5: ENEMY_ATTACK.width
			}else{
				x_pos = this->get_x()+30;
			}
			this->attacklist->add_arrow(x_pos, this->get_y()+18, this->get_mirrored());
			if (this->attack_snd != 0) {
				IntVector position = {x_pos, this->get_y()+18};
				this->attack_snd->play_if_source_is_visible(position);
			}
		}
		this->shoot_wait_time = this->shoot_interval;
	}

	if (!this->stays_on_ground()) {
		this->stop(1);
	}else{
		this->play();
	}
}

CEnemy::~CEnemy() {
}

