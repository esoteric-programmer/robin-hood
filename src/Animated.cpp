#include "Animated.h"

void CAnimated::pause() {
	this->paused = true;
}

void CAnimated::stop(u16 frame) {
	this->paused = true;
	this->current_frame = frame % this->number_of_frames;
	this->current_frame_time_gone = 0;
}

void CAnimated::play() {
	this->paused = false;
}
	

CAnimated::CAnimated(s16 start_x, s16 start_y, CTexture** textures, u16 number_of_textures, u16 time_per_frame, bool mirrored)
		: CDrawable(start_x, start_y, mirrored) {
	this->textures = textures;
	this->number_of_frames = number_of_textures;
	this->time_per_frame = time_per_frame;
	this->current_frame = 0;
	this->current_frame_time_gone = 0;
	this->paused = false;
	this->size.x1 = 0;
	this->size.y1 = 0;
	this->size.x2 = 0;
	this->size.y2 = 0;
	for (u16 i=0; i<number_of_textures; i++) {
		if (textures[i]->get_width() > this->size.x2) {
			this->size.x2 = textures[i]->get_width();
		}
		if (textures[i]->get_height() > this->size.y2) {
			this->size.y2 = textures[i]->get_height();
		}
	}
}

void CAnimated::draw(s16 screen_offset_x, s16 screen_offset_y) {
	if (this->textures != 0) {
		if (this->textures[this->current_frame] != 0) {
			this->textures[this->current_frame]->draw(this->get_x()-screen_offset_x, this->get_y()-screen_offset_y, this->get_mirrored());
		}
	}
}

Vector CAnimated::get_middle_point() {
	Vector ret;
	ret.x = this->get_x();
	ret.y = this->get_y();
	ret.x += (float)this->size.x2 * 0.5f;
	ret.y += (float)this->size.y2 * 0.5f;
	return ret;
}

void CAnimated::update(u16 time_steps) {
	if (this->paused) {
		return;
	}
	this->current_frame += time_steps / this->time_per_frame;
	this->current_frame_time_gone += time_steps % this->time_per_frame;
	if (this->current_frame_time_gone >= this->time_per_frame) {
		this->current_frame_time_gone -= this->time_per_frame;
		this->current_frame++;
	}
	this->current_frame %= this->number_of_frames;
}

Rect CAnimated::get_drawable_size() {
	return this->size;
}

CAnimated::~CAnimated() {
}

