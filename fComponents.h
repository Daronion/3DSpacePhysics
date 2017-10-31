#pragma once

#include <thread>
#include "Part.h"

struct fComponents {

	std::thread * th;
	bool done;
	Vector3 force;

	fComponents(std::thread * t, bool d,Vector3 f) {
		th = t;
		done = d;
		force = f;
	}
};