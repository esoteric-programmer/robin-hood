#include "Landscape.h"

CLandscape::CLandscape(s16 start_x, s16 start_y, CTexture*& texture, Rect bounding_box, bool mirrored)
		: CCollidable(start_x, start_y, &texture, 1, 1, bounding_box, mirrored) {
}

CLandscape::~CLandscape() {
}


