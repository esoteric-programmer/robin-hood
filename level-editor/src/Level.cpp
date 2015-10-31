#include "Level.h"

CLevel::CLevel() :
		const_landscape_list(&landscape_list),
		const_nature_list(&nature_list),
		const_enemy_list(&enemy_list),
		const_cloud_list(&cloud_list) {
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
	// TODO
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
	// TODO
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
	// TODO
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
	this->clear();
}

