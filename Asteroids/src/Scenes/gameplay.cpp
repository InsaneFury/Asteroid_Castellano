#include "gameplay.h"
#include "Logic/game.h"
#include "Utility/animations.h"
#include "Characters\Player\player.h"
#include "Characters\Enemys\asteroids.h"

namespace asteroid {
	namespace gameplay {

		bool pause = false;
		Texture2D gameplay_vintage;

		void init() {
			gameplay_vintage = LoadTexture("res/Textures/VINTAGE.png");
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
			if (pause) {
				DrawText("PAUSE", (float)GetScreenWidth() / 2 - MeasureText("PAUSE", 50)/2, (float)GetScreenHeight()/2 - 25, 50, WHITE);
			}
			BeginBlendMode(BLEND_MULTIPLIED);
			DrawTexture(gameplay_vintage, 0, 0, WHITE);
			EndBlendMode();
		}

		void deInit() {
			animations::deInit();
			players::deInit();
			asteroids::deInit();
			UnloadTexture(gameplay_vintage);
		}
	}
}

