#include "LandscapeList.h"


CLandscapeList::CLandscapeList()
	: CDrawable(0,0,false) {
	this->root.next = 0;
	this->root.landscape = 0;
	this->root.solid = false;
	this->last = &(this->root);
}

void CLandscapeList::add_object(CCollidable* landscape, bool solid) {
	LinkedList* new_element = new LinkedList;
	if (new_element == 0)
		return; // ERROR
	new_element->next = 0;
	new_element->solid = solid;
	new_element->landscape = landscape;
	this->last->next = new_element;
	this->last = new_element;
}


bool CLandscapeList::collide(IntVector position, Rect bounding_box, CCollidable*& collided_with, CCollidable::ObjectArea detection_area, bool only_solid) {
	
	LinkedList* it = root.next;
	while (it != 0) {
		if (it->landscape != 0) {
			if (!only_solid || it->solid) {
				if (it->landscape->check_collision(position, bounding_box, detection_area)) {
					collided_with = it->landscape;
					return true;
				}
			}
		}
		it = it->next;
	}
	
	return false;
}

void CLandscapeList::draw(s16 screen_offset_x, s16 screen_offset_y) {
	LinkedList* it = root.next;
	while (it != 0) {
		if (it->landscape != 0) {
			it->landscape->draw(screen_offset_x, screen_offset_y);
		}
		it = it->next;
	}
}

void CLandscapeList::update(u16 time_steps) {
	LinkedList* it = root.next;
	while (it != 0) {
		if (it->landscape != 0) {
			it->landscape->update(time_steps);
		}
		it = it->next;
	}
}

void CLandscapeList::clear() {
	LinkedList* it = root.next;
	while (it != 0) {
		if (it->landscape != 0) {
			delete it->landscape;
		}
		LinkedList* next = it->next;
		delete it;
		it = next;
	}
	root.next = 0;
	this->last = &(this->root);
}

CLandscapeList::~CLandscapeList() {
	this->clear();
}


