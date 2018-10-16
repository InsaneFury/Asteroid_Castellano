#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace asteroid {
	namespace gameplay {
		void init();
		void update(bool &isGameOver);
		void draw();
		void deInit();

		extern bool pause;

	}
}
#endif // !GAMEPLAY_H


