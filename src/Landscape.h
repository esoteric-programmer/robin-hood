#ifndef LANDSCAPE_INCLUDED
#define LANDSCAPE_INCLUDED

#include "Collidable.h"

class CLandscape : public CCollidable {

public:
	CLandscape(s16 start_x, s16 start_y, CTexture*& texture, Rect bounding_box, bool mirrored = false);
	virtual ~CLandscape();

};

#endif

