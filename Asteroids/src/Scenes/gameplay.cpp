#include "gameplay.h"
#include "Logic/game.h"
#include "Utility/buttons.h"
#include "Utility/animations.h"
#include "Characters\Player\player.h"
#include "Characters\Enemys\asteroids.h"
#include <math.h>

namespace asteroid {
	namespace gameplay {

		void init() {
			animations::init();
			players::init();
			asteroids::init();
		}

		void update() {
			animations::update();
			players::update();
			asteroids::update();
		}

		void draw() {
			animations::draw();
			players::draw();
			asteroids::draw();
		}

		void deInit() {
			animations::deInit();
			players::deInit();
			asteroids::deInit();
		}
	}
}

