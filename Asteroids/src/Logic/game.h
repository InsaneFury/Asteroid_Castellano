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

		void runGame();
	}
}
#endif // !GAME_H



