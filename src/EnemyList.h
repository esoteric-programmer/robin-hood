#ifndef ENEMYLIST_INCLUDED
#define ENEMYLIST_INCLUDED

#include "LandscapeList.h"
#include "Enemy.h"

class CEnemyList : public CLandscapeList {

private:
	CArrowList* arrowlist;

public:
	CEnemyList(CArrowList* arrowlist); // arrows of CRobin, enemies will fall down on contact
	void add_object(CCollidable* landscape, bool solid);
	void add_object(CEnemy* enemy);
	bool check_collision(CCollidable* collision);
	void update(u16 time_steps, u16* destroyed_enemies = 0);
	virtual ~CEnemyList();
};

#endif

