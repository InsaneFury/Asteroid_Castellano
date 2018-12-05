#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#define AUDIO

namespace asteroid {
	namespace game {
		extern int screenWidth;
		extern int screenHeight;

		enum ActualScene {
			Menu,
			Game,
			Gameover,
			Credits
		};

		extern ActualScene actualScene;
		extern Music bgMusic;

		void runGame();
		void initMouse();
		void updateMouse();
		void drawMouse();
		void deInitMouse();
	}
}
#endif // !GAME_H



