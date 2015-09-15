#include "ArrowList.h"


CArrowList::CArrowList(u16 max_age, CTexture** textures, u16 number_of_textures, u16 time_per_frame, Rect bounding_box, float speed)
	: CDrawable(0,0,false), textures(textures) {
	this->root.next = 0;
	this->root.arrow = 0;
	this->root.age = 0;
	this->last = &(this->root);
	this->max_age = max_age;
	this->speed = speed;
	this->number_of_textures = number_of_textures;
	this->time_per_frame = time_per_frame;
	this->bounding_box.x1 = bounding_box.x1;
	this->bounding_box.y1 = bounding_box.y1;
	this->bounding_box.x2 = bounding_box.x2;
	this->bounding_box.y2 = bounding_box.y2;
}

void CArrowList::add_arrow(s16 start_x, s16 start_y, bool fly_to_left) {
	LinkedList* new_element = new LinkedList;
	if (new_element == 0)
		return; // ERROR
	new_element->next = 0;
	new_element->age = 0;
	new_element->arrow = new CMovable(start_x, start_y, this->textures, this->number_of_textures, this->time_per_frame, this->bounding_box, this->speed, fly_to_left, (fly_to_left?-1.0f:1.0f));
	this->last->next = new_element;
	this->last = new_element;
}

bool CArrowList::collide(CCollidable* object) {
	bool collision = false;
	LinkedList* it = root.next;
	LinkedList* prev = &root;
	LinkedList* last_valid = &root;
	while (it != 0) {
		last_valid = it;
		if (it->arrow != 0) {
			if (it->arrow->check_collision(object)) {
				// remove!
				delete it->arrow;
				LinkedList* next = it->next;
				delete it;
				prev->next = next;
				it = prev;
				collision = true;
			}
		}
		prev = it;
		it = it->next;
	}
	this->last = last_valid;
	
	return collision;
}

void CArrowList::draw(s16 screen_offset_x, s16 screen_offset_y) {
	LinkedList* it = root.next;
	while (it != 0) {
		if (it->arrow != 0) {
			it->arrow->draw(screen_offset_x, screen_offset_y);
		}
		it = it->next;
	}
}

void CArrowList::update(u16 time_steps) {
	LinkedList* it = root.next;
	LinkedList* prev = &root;
	LinkedList* last_valid = &root;
	while (it != 0) {
		last_valid = it;
		if (it->arrow != 0) {
			it->arrow->update(time_steps);
			it->age += time_steps;
			if (it->age > this->max_age) {
				// remove!
				delete it->arrow;
				LinkedList* next = it->next;
				delete it;
				prev->next = next;
				it = prev;
			}
		}
		prev = it;
		it = it->next;
	}
	this->last = last_valid;
}

void CArrowList::clear() {
	LinkedList* it = root.next;
	while (it != 0) {
		if (it->arrow != 0) {
			delete it->arrow;
		}
		LinkedList* next = it->next;
		delete it;
		it = next;
	}
	root.next = 0;
	this->last = &(this->root);
}


CArrowList::~CArrowList() {
	this->clear();
}


