#include "EnemyList.h"

CEnemyList::CEnemyList(CArrowList* arrowlist) : CLandscapeList() {
	this->arrowlist = arrowlist;
}

void CEnemyList::add_object(CCollidable*, bool) {
	return; // not supported
}

void CEnemyList::add_object(CEnemy* enemy) {
	CLandscapeList::add_object(enemy, false);
}

bool CEnemyList::check_collision(CCollidable* collision) {
	LinkedList* it = root.next;
	while (it != 0) {
		if (it->landscape != 0) {
			if (it->landscape->check_collision(collision)) {
				return true;
			}
		}
		it = it->next;
	}
	return false;
}

void CEnemyList::update(u16 time_steps, u16* destroyed_enemies) {
	LinkedList* it = root.next;
	LinkedList* prev = &root;
	LinkedList* last_valid = &root;
	if (destroyed_enemies != 0)
		*destroyed_enemies = 0;
	while (it != 0) {
		last_valid = it;
		if (it->landscape != 0) {
			it->landscape->update(time_steps);
			if (arrowlist->collide(it->landscape)) {
				((CEnemy*)it->landscape)->force_dying();
			}
			if (((CFallable*)it->landscape)->left_landscape()) {
				// remove object!
				delete it->landscape;
				LinkedList* next = it->next;
				delete it;
				prev->next = next;
				it = prev;
				if (destroyed_enemies != 0)
					(*destroyed_enemies)++;
			}
		}
		prev = it;
		it = it->next;
	}
	this->last = last_valid;
}

CEnemyList::~CEnemyList() {
}

