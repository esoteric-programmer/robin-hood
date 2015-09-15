#include "Collidable.h"

CCollidable::CCollidable(s16 start_x, s16 start_y, CTexture** textures, u16 number_of_textures, u16 time_per_frame, Rect bounding_box, bool mirrored)
		: CAnimated(start_x, start_y, textures, number_of_textures, time_per_frame, mirrored) {
	this->bounding_box.x1 = bounding_box.x1;
	this->bounding_box.y1 = bounding_box.y1;
	this->bounding_box.x2 = bounding_box.x2;
	this->bounding_box.y2 = bounding_box.y2;
}

bool CCollidable::check_collision(IntVector position, Rect bounding_box, ObjectArea detection_area) {
	switch (detection_area) {
		case ObjectArea::LEFT_EDGE:
			return (position.x + bounding_box.x1 <= this->get_x() + this->bounding_box.x1
				&& position.x + bounding_box.x2 > this->get_x() + this->bounding_box.x1
				&& position.y + bounding_box.y1 < this->get_y() + this->bounding_box.y2
				&& position.y + bounding_box.y2 > this->get_y() + this->bounding_box.y1);
		case ObjectArea::RIGHT_EDGE:
			return (position.x + bounding_box.x1 < this->get_x() + this->bounding_box.x2
				&& position.x + bounding_box.x2 >= this->get_x() + this->bounding_box.x2
				&& position.y + bounding_box.y1 < this->get_y() + this->bounding_box.y2
				&& position.y + bounding_box.y2 > this->get_y() + this->bounding_box.y1);
		case ObjectArea::TOP_EDGE:
			return (position.x + bounding_box.x1 < this->get_x() + this->bounding_box.x2
				&& position.x + bounding_box.x2 > this->get_x() + this->bounding_box.x1
				&& position.y + bounding_box.y1 <= this->get_y() + this->bounding_box.y1
				&& position.y + bounding_box.y2 > this->get_y() + this->bounding_box.y1);
		case ObjectArea::BOTTOM_EDGE:
			return (position.x + bounding_box.x1 < this->get_x() + this->bounding_box.x2
				&& position.x + bounding_box.x2 > this->get_x() + this->bounding_box.x1
				&& position.y + bounding_box.y1 < this->get_y() + this->bounding_box.y2
				&& position.y + bounding_box.y2 >= this->get_y() + this->bounding_box.y2);
		case ObjectArea::WHOLE_OBJECT:
		default:
			return (position.x + bounding_box.x1 <= this->get_x() + this->bounding_box.x2
				&& position.x + bounding_box.x2 >= this->get_x() + this->bounding_box.x1
				&& position.y + bounding_box.y1 <= this->get_y() + this->bounding_box.y2
				&& position.y + bounding_box.y2 >= this->get_y() + this->bounding_box.y1);
	}
}

bool CCollidable::check_collision(CCollidable* collision) {
	return (collision->get_x() + collision->bounding_box.x1 <= this->get_x() + this->bounding_box.x2
		&& collision->get_x() + collision->bounding_box.x2 >= this->get_x() + this->bounding_box.x1
		&& collision->get_y() + collision->bounding_box.y1 <= this->get_y() + this->bounding_box.y2
		&& collision->get_y() + collision->bounding_box.y2 >= this->get_y() + this->bounding_box.y1);
}

Rect CCollidable::get_bounding_box() {
	return this->bounding_box;
}

s16 CCollidable::get_top() {
	return this->get_y()+this->bounding_box.y1;
}

s16 CCollidable::get_bottom() {
	return this->get_y()+this->bounding_box.y2;
}

s16 CCollidable::get_left() {
	return this->get_x()+this->bounding_box.x1;
}

s16 CCollidable::get_right() {
	return this->get_x()+this->bounding_box.x2;
}

void CCollidable::set_position(s16 x, s16 y) {
		this->add_to_position(x-this->get_x(),y-this->get_y());
}

