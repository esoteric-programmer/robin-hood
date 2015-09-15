#include "Robin.h"

CRobin::CRobin(s16 start_x, s16 start_y, CTexture* textures[], u16 number_of_textures, u16 time_per_frame, Rect bounding_box, float pixel_per_step, CLandscapeList* landscapelist, s16 landscape_width, s16 landscape_height, float g, CArrowList* arrowlist, u16 shoot_interval, CSound* jump, CSound* shoot)
		: CFallable(start_x, start_y, textures, number_of_textures, time_per_frame, bounding_box, pixel_per_step, landscapelist, landscape_width, landscape_height, g) {
	this->can_move = true;
	this->was_moving_right = false;
	this->was_moving_left = false;
	this->arrowlist = arrowlist;
	this->shooting = false;
	this->jumping = false;
	this->shoot_wait_time = 0;
	this->shoot_interval = shoot_interval;
	this->landscapelist_backup = landscapelist;
	this->jump_snd = jump;
	this->shoot_snd = shoot;
}

void CRobin::walk(float direction) {
	if (direction < 0.4f && direction > -0.4f) {
		this->set_moving(0.0f);
		this->stop();
		this->was_moving_right = false;
		this->was_moving_left = false;
	} else {
		if (can_move) {
			if (!((direction > 0.0f && this->was_moving_right) || (direction < 0.0f && this->was_moving_left))) {
				this->stop(1);
				this->play();
			}
			this->was_moving_right = false;
			this->was_moving_left = false;
			if (direction > 0.0f)
				this->was_moving_right = true;
			else
				this->was_moving_left = true;
			this->set_moving(direction);
		} else {
			this->set_moving(direction);
			this->set_moving(0.0f);
			this->stop(1);
		}
	}
}

void CRobin::force_dying() {
	this->can_move = false;
	this->set_landscapelist(0);
}

void CRobin::reset(s16 start_x, s16 start_y, s16 landscape_width, s16 landscape_height) {
	this->set_position(start_x, start_y);
	CFallable::reset(landscape_width, landscape_height);
	this->set_moving(1.0f); // look right
	this->set_moving(0.0f);
	this->stop();
	this->can_move = true;
	this->set_landscapelist(this->landscapelist_backup);
	this->was_moving_right = false;
	this->was_moving_left = false;
	this->shooting = false;
	this->jumping = false;
	this->shoot_wait_time = 0;
}

void CRobin::shoot() {
	this->shooting = true;
}

void CRobin::jump() {
	this->jumping = true;
}

void CRobin::update(u16 time_steps) {
	if (this->left_landscape())
		return;
	CFallable::update(time_steps);
	if (this->jumping && this->stays_on_ground()) {
		this->set_current_fallspeed(-4.5f);
		if (this->jump_snd != 0)
			this->jump_snd->play();
	}
	if (this->shoot_wait_time <= time_steps) {
		this->shoot_wait_time = 0;
	}else{
		this->shoot_wait_time -= time_steps;
	}
	if (this->shooting && this->shoot_wait_time == 0) {
		if (this->arrowlist != 0) {
			s16 x_pos;
			if (this->get_mirrored()) {
				x_pos = this->get_x()+ 48 - (32 + 14); // 48: ROBIN.width; 14: ARROW.width
			}else{
				x_pos = this->get_x()+32;
			}
			this->arrowlist->add_arrow(x_pos, this->get_y()+27, this->get_mirrored());
			if (this->shoot_snd != 0)
				this->shoot_snd->play();
		}
		this->shoot_wait_time = this->shoot_interval;
	}
	this->shooting = false;
	this->jumping = false;
	if (!this->stays_on_ground() && (this->was_moving_right || this->was_moving_left)) {
		this->stop(1);
	}else if (this->stays_on_ground() && can_move && (this->was_moving_right || this->was_moving_left)) {
		this->play();
	}
}

CRobin::~CRobin() {
}

