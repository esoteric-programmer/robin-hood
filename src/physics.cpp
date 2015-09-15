#include <math.h>
#include "physics.h"

Vector getPosition(Parabel p, float time) {
	Vector pos;
	pos.x = 0.5 * p.accelerate.x * time * time + p.start_speed.x * time + p.start_point.x;
	pos.y = 0.5 * p.accelerate.y * time * time + p.start_speed.y * time + p.start_point.y;
	return pos;
}

Parabel getParabel(Parabel p, float time) {
	Parabel res;
	res.start_point.x = 0.5 * p.accelerate.x * time * time + p.start_speed.x * time + p.start_point.x;
	res.start_point.y = 0.5 * p.accelerate.y * time * time + p.start_speed.y * time + p.start_point.y;
	res.start_speed.x = p.accelerate.x * time + p.start_speed.x;
	res.start_speed.y = p.accelerate.y * time + p.start_speed.y;
	res.accelerate.x = p.accelerate.x;
	res.accelerate.y = p.accelerate.y;
	return res;
}

bool intersect(Parabel p, Line l, bool get_second_intersection, float& time) {

	if (l.vertical) {
		if (p.accelerate.x == 0.0f)
			return false;
		float tmp_square = (2.0f * (l.position - p.start_point.x) + p.start_speed.x * p.start_speed.x) * (p.accelerate.x);
		if (tmp_square < 0.0f)
			return false;
		float tmp = sqrt(tmp_square);
		if (!get_second_intersection) {
			time = (-tmp - p.start_speed.x) / (p.accelerate.x);
		}else{
			time = (tmp - p.start_speed.x) / (p.accelerate.x);
		}
		return true;
	} else {
		if (p.accelerate.y == 0.0f)
			return false;
		float tmp_square = (2.0f * (l.position - p.start_point.y) + p.start_speed.y * p.start_speed.y) * (p.accelerate.y);
		if (tmp_square < 0.0f)
			return false;
		float tmp = sqrt(tmp_square);
		if (!get_second_intersection) {
			time = (-tmp - p.start_speed.y) / (p.accelerate.y);
		}else{
			time = (tmp - p.start_speed.y) / (p.accelerate.y);
		}
		return true;
	}

}


