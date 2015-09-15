#ifndef LANDSCAPELIST_INCLUDED
#define LANDSCAPELIST_INCLUDED

#include "Collidable.h"

class CLandscapeList : public CDrawable {
protected:
	typedef struct LinkedList {
		LinkedList* next;
		CCollidable* landscape;
		bool solid;
	} LinkedList;
	
	LinkedList root;
	LinkedList* last;
	
public:
	CLandscapeList();
	virtual void add_object(CCollidable* landscape, bool solid);
	virtual bool collide(IntVector position, Rect bounding_box, CCollidable*& collided_with, CCollidable::ObjectArea detection_area = CCollidable::ObjectArea::WHOLE_OBJECT, bool only_solid = false);
	void draw(s16 screen_offset_x, s16 screen_offset_y);
	virtual void update(u16 time_steps);
	void clear();
	virtual ~CLandscapeList();
};

#endif

