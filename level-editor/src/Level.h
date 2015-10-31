#ifndef LEVEL_INCLUDED
#define LEVEL_INCLUDED

#include <SDL2/SDL.h>

#include "List.h"
#include "tools.h"

class CLevel {
public:
	struct Landscape {
		int x;
		int y;
		int type;
		Landscape* left;
		Landscape* right;
	};
	
	struct Nature {
		int x;
		int y;
		int type;
	};
	
	struct Enemy {
		int x;
		int y;
		int left_border;
		int right_border;
		int speed;
		int shoot_interval;
	};


private:
	// LANDSCAPELIST
	CList<Landscape> landscape_list;
	CConstList<Landscape> const_landscape_list;
	
	// NATURELIST
	CList<Nature> nature_list;
	CConstList<Nature> const_nature_list;
	
	// ENEMYLIST
	CList<Enemy> enemy_list;
	CConstList<Enemy> const_enemy_list;
	
	// ROBIN_POS
	Vector start_pos;
	// FINISH_POS
	Vector finish_pos;
	
	// CLOUDLIST
	CList<Landscape> cloud_list;
	CConstList<Landscape> const_cloud_list;
	
	unsigned int width;
	unsigned int height;
	
public:
	CLevel();

	void clear();
	void load_from_file(const char* file);
	void save_to_file(const char* file);
	
	CConstList<Landscape>* get_landscape_list();
	CConstList<Nature>* get_nature_list();
	CConstList<Enemy>* get_enemy_list();
	CConstList<Landscape>* get_cloud_list();

	unsigned int get_width();
	void set_width(unsigned int width);
	unsigned int get_height();
	void set_height(unsigned int height);

	void add_landscape(Landscape landscape);
	void add_nature(Nature nature);
	void add_enemy(Enemy enemy);
	void add_cloud(Landscape cloud);
	void remove_landscape(Landscape* landscape);
	void remove_nature(Nature* nature);
	void remove_enemy(Enemy* enemy);
	void remove_cloud(Landscape* cloud);
	
	void set_start_pos(Vector pos);
	Vector get_start_pos();
	void set_finish_pos(Vector pos);
	Vector get_finish_pos();
	
	~CLevel();
};

#endif

