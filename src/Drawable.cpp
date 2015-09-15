#include "Drawable.h"

CDrawable::CDrawable(s16 start_x, s16 start_y, bool mirrored) {
	this->mirrored = mirrored;
	this->x = start_x;
	this->y = start_y;
}

s16 CDrawable::get_x() {
	return this->x;
}

s16 CDrawable::get_y() {
	return this->y;
}

void CDrawable::add_to_position(s16 x, s16 y) {
	this->x += x;
	this->y += y;
}

void CDrawable::set_mirrored(bool value) {
	this->mirrored = value;
}
	
bool CDrawable::get_mirrored() {
	return this->mirrored;
}


CDrawable::~CDrawable() {
}

