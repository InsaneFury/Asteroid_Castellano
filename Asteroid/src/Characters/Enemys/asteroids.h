#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "raylib.h"

namespace asteroid {
	namespace asteroids {
		struct Meteor {
			Vector2 position;
			Vector2 speed;
			float radius;
			bool active;
			float rotation;
			Color color;
			//Stuff to use DrawTexturePro
			// NOTE: Source rectangle (part of the texture to use for drawing)
			Rectangle sourceRec;
			// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
			Rectangle destRec;
			// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
			Vector2 origin;
		};

		extern int destroyedMeteorsCount;
		extern bool victory;
		extern const int MAX_BIG_METEORS;
		extern const int MAX_MEDIUM_METEORS;
		extern const int MAX_SMALL_METEORS;

		extern Meteor bigMeteor[];
		extern Meteor mediumMeteor[];
		extern Meteor smallMeteor[];

		void init();
		void update();
		void draw();
		void deInit();

	}
}


#endif // !ASTEROIDS_H