#include "Level.h"

CLevel::CLevel() :
		const_landscape_list(&landscape_list),
		const_nature_list(&nature_list),
		const_enemy_list(&enemy_list),
		const_cloud_list(&cloud_list) {
	add_base();
}

void CLevel::tidy_up() {
	// TODO clear level, free memory
}

void CLevel::add_base() {
	width = 400;
	height = 240;
	start_pos.x = 0;
	start_pos.y = 32;
	finish_pos.x = 64;
	finish_pos.y = 32;
	Landscape* grass1 = new Landscape;
	grass1->x = 0;
	grass1->y = 0;
	grass1->type = 0;
	grass1->left = 0;
	Landscape* grass2 = new Landscape;
	grass2->x = 32;
	grass2->y = 0;
	grass2->type = 0;
	grass2->left = grass1;
	grass1->right = grass2;
	Landscape* grass3 = new Landscape;
	grass3->x = 64;
	grass3->y = 0;
	grass3->type = 0;
	grass3->left = grass2;
	grass2->right = grass3;
	grass3->right = 0;
	landscape_list.add(grass1);
	landscape_list.add(grass2);
	landscape_list.add(grass3);
}

void CLevel::clear() {
	this->tidy_up();
	this->add_base();
}

void CLevel::load_from_file(const char* file) {
	// TODO
}

void CLevel::save_to_file(const char* file) {
	// TODO
}
	
CConstList<CLevel::Landscape>* CLevel::get_landscape_list() {
	return &(this->const_landscape_list);
}

CConstList<CLevel::Nature>* CLevel::get_nature_list() {
	return &(this->const_nature_list);
}
	
CConstList<CLevel::Enemy>* CLevel::get_enemy_list() {
	return &(this->const_enemy_list);
}

CConstList<CLevel::Landscape>* CLevel::get_cloud_list() {
	return &(this->const_cloud_list);
}
	
unsigned int CLevel::get_width() {
	return this->width;
}

void CLevel::set_width(unsigned int width) {
	this->width = width;
}

unsigned int CLevel::get_height() {
	return this->height;
}

void CLevel::set_height(unsigned int height) {
	this->height = height;
}

void CLevel::add_landscape(CLevel::Landscape landscape) {
	Landscape* nl = new Landscape;
	if (nl != 0) {
		nl->x = landscape.x;
		nl->y = landscape.y;
		nl->type = landscape.type;
		nl->left = 0; // TODO
		nl->right = 0; // TODO
		
		Landscape* it = this->landscape_list.first();
		while (it != 0) {
			if (it->type == nl->type) {
				if (it->y == nl->y) {
					if (it->x == nl->x-32) {
						it->right = nl;
						nl->left = it;
					}
					if (it->x == nl->x) {
						delete nl;
						return;
					}
					if (it->x == nl->x+32) {
						it->left = nl;
						nl->right = it;
					}
				}
			}else{
				if (it->x == nl->x && it->y == nl->y) {
					remove_landscape(it);
					it = this->landscape_list.first();
					continue;
				}
			}
			it = this->landscape_list.next();
		}
		this->landscape_list.add(nl);
	}
}

void CLevel::add_nature(CLevel::Nature nature) {
	// TODO
}

void CLevel::add_enemy(CLevel::Enemy enemy) {
	// TODO
}

void CLevel::add_cloud(CLevel::Landscape cloud) {
	// TODO
}

void CLevel::remove_landscape(CLevel::Landscape* landscape) {
	if (landscape == 0) {
		return;
	}
	if (landscape->left != 0) {
		landscape->left->right = 0;
	}
	if (landscape->right != 0) {
		landscape->right->left = 0;
	}
	this->landscape_list.remove(landscape);
	delete landscape;
}

void CLevel::remove_nature(CLevel::Nature* nature) {
	// TODO
}

void CLevel::remove_enemy(CLevel::Enemy* enemy) {
	// TODO
}

void CLevel::remove_cloud(CLevel::Landscape* cloud) {
	// TODO
}

	
void CLevel::set_start_pos(Vector pos) {
	this->start_pos.x = pos.x;
	this->start_pos.y = pos.y;
}

Vector CLevel::get_start_pos() {
	return this->start_pos;
}

void CLevel::set_finish_pos(Vector pos) {
	this->finish_pos.x = pos.x;
	this->finish_pos.y = pos.y;
}

Vector CLevel::get_finish_pos() {
	return this->finish_pos;
}
	
CLevel::~CLevel() {
	this->tidy_up();
}

