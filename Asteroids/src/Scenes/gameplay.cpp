#include "gameplay.h"
#include "Logic/game.h"
#include "Utility/buttons.h"
#include "Characters\Player\player.h"
#include "Characters\Enemys\asteroids.h"
#include <math.h>

namespace asteroid {
	namespace gameplay {

		void init() {
			players::init();
			asteroids::init();
		}

		void update() {
			players::update();
			asteroids::update();
		}

		void draw() {
			players::draw();
			asteroids::draw();
		}

		void deInit() {
			players::deInit();
		}
	}
}

