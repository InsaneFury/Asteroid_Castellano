#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

namespace asteroid {
	namespace pause_menu {
		void init();
		void update(bool &isGameOver);
		void draw();
		void deInit();
	}
}
#endif // !PAUSE_MENU_H
