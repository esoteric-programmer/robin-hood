#include "Mouse.h"

CMouse::CMouse() {
	this->type = CURSOR;
	this->pos.x = 0;
	this->pos.y = 0;
}

CMouse::CMouse(Vector pos, CMouse::MouseType type) {
	this->type = type;
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

Vector CMouse::get_coordinates() {
	Vector ret = {this->pos.x, this->pos.y};
	return ret;
}

void CMouse::set_coordinates(Vector pos) {
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

CMouse::MouseType CMouse::get_type() {
	return this->type;
}

void CMouse::set_type(CMouse::MouseType type) {
	this->type = type;
}

CMouse::~CMouse() {
}

