#ifndef ARROWLIST_INCLUDED
#define ARROWLIST_INCLUDED

#include "Movable.h"
#include "Drawable.h"
#include "Texture.h"

class CArrowList : public CDrawable {
private:
	typedef struct LinkedList {
		LinkedList* next;
		CMovable* arrow;
		u16 age;
	} LinkedList;
	
	LinkedList root;
	LinkedList* last;
	u16 max_age;
	CTexture** textures;
	u16 number_of_textures; 
	u16 time_per_frame;
	Rect bounding_box;
	float speed;
	
public:
	CArrowList(u16 max_age, CTexture* textures[], u16 number_of_textures, u16 time_per_frame, Rect bounding_box, float speed);
	void add_arrow(s16 start_x, s16 start_y, bool fly_to_left);
	bool collide(CCollidable*);
	void draw(s16 screen_offset_x, s16 screen_offset_y);
	void update(u16 time_steps);
	void clear();
	virtual ~CArrowList();
};

#endif

