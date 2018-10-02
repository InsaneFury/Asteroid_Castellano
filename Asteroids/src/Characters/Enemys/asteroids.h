#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "raylib.h"
namespace asteroid {
	namespace asteroids {
		struct Meteor {
			Texture2D texture;
			Vector2 position;
			Vector2 speed;
			float radius;
			bool active;
			Color color;
		};

		void init();
		void update();
		void draw();
		void deInit();

	}
}


#endif // !ASTEROIDS_H