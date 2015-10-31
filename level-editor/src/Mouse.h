#ifndef MOUSE_INCLUDED
#define MOUSE_INCLUDED

#include <SDL2/SDL.h>
#include "tools.h"

class CMouse {
public:
	enum MouseType {
		CURSOR,
		GRASS,
		SOLID,
		ENEMY,
		ROBIN,
		FINISH,
		FLOWER,
		STONE,
		TREE,
		CLOUD
	};

private:
	Vector pos;
	MouseType type;

public:
	CMouse();
	CMouse(Vector pos, MouseType type);
	Vector get_coordinates();
	void set_coordinates(Vector pos);
	MouseType get_type();
	void set_type(MouseType type);
	~CMouse();
};

#endif

