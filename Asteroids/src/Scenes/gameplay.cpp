#include "gameplay.h"
#include "Logic/game.h"
#include "Utility/animations.h"
#include "Characters\Player\player.h"
#include "Characters\Enemys\asteroids.h"

namespace asteroid {
	namespace gameplay {

		bool pause = false;

		void init() {
			animations::init();
			players::init();
			asteroids::init();
		}

		void update(bool &isGameOver) {
			if (!isGameOver){
				if (IsKeyPressed('P')) {
					pause = !pause;
				}

				if (!pause){
					animations::update();
					players::update();
					asteroids::update();
				}
			}
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

