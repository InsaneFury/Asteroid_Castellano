#ifndef VICTORY_H
#define VICTORY_H

namespace asteroid {
	namespace victory {
		void init();
		void update(bool &isGameOver);
		void draw();
		void deInit();
		bool isVictory();
	}
}
#endif // !VICTORY_H
