#include "gameplay.h"

#include "Utility/pause_menu.h"
#include "Logic/game.h"
#include "Utility/animations.h"
#include "Characters/Player/player.h"
#include "Characters/Enemys/asteroids.h"
#include "Utility/buttons.h"
#include "Scenes/victory.h"

namespace asteroid {
	namespace gameplay {

		bool pause;
		bool tutorial;

		static Texture2D gameplay_vintage;
		static Texture2D gameplay_tutorial;

		static buttons::BTNTEX pause_btn;

		static Vector2 mouse_point;

		static float timer;
		static float delayTime;

		void init() {

			timer = 0.0f;
			

			pause = false;
			tutorial = true;

			pause_btn.btn_texture = LoadTexture("res/Textures/PAUSE_BTN.png");
			pause_btn.btnOnHover_texture = LoadTexture("res/Textures/PAUSEONHOVER_BTN.png");
			buttons::createButton(
				pause_btn, 
				pause_btn.btn_texture.height, 
				pause_btn.btn_texture.width, 
				(float)(GetScreenWidth() - pause_btn.btn_texture.width - pause_btn.btn_texture.width/2), 
				(float)(pause_btn.btn_texture.height/2), 
				WHITE);

			gameplay_vintage = LoadTexture("res/Textures/VINTAGE.png");
			gameplay_tutorial = LoadTexture("res/Textures/tutorial.png");
			animations::init();
			players::init();
			asteroids::init();
			pause_menu::init();
			victory::init();

		}

		void update(bool &isGameOver) {
			game::updateMouse();
			timer += GetFrameTime();
			delayTime = 2.0f;

			if (!isGameOver){

				mouse_point = GetMousePosition();

				if (pause == false && tutorial == false) {
					buttons::isMouseOverButton(pause_btn);
					if (CheckCollisionPointRec(mouse_point, pause_btn.size))
					{
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
							pause = !pause;
							timer = 0;
						}
					}
				}
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					tutorial = false;
				}
		
				if (!pause && tutorial == false){
					animations::update();
					if (timer >= delayTime) {
						players::update();
						asteroids::update();
					}	
				}
				else if (tutorial == false) {
					pause_menu::update(isGameOver);
				}
				if (victory::isVictory()) {
					victory::update(isGameOver);
				}
			}
		}

		void draw() {
			
			if (tutorial) {		
				DrawTexture(gameplay_tutorial, 0, 0, WHITE);
			}
			else {
				animations::draw();

				if (timer <= delayTime && !pause) {
					DrawText(
						"READY!?",
						GetScreenWidth() / 2 - MeasureText("READY!?", 100) / 2,
						150,
						100,
						WHITE);
					players::draw();
					asteroids::draw();
				}
				else{
					if (timer <= delayTime + 2.0f && !pause) {
						DrawText(
							"GO!!",
							GetScreenWidth() / 2 - MeasureText("GO!!", 100) / 2,
							150,
							100,
							WHITE);

					}
					
					players::draw();
					asteroids::draw();

					DrawText(
						FormatText("SCORE: %02i", asteroids::destroyedMeteorsCount),
						GetScreenWidth() / 2 - MeasureText("SCORE: 00", 40) / 2,
						50,
						40,
						WHITE);
				}
				if (pause == false) {
					buttons::draw(pause_btn);
				}

				if (pause) {
					pause_menu::draw();
					timer = 0;
				}
				if (victory::isVictory()) {
					victory::draw();
					timer = 0;
				}
			}
				
			
			game::drawMouse();
			BeginBlendMode(BLEND_MULTIPLIED);
			DrawTexture(gameplay_vintage, 0, 0, WHITE);
			EndBlendMode();
		}

		void deInit() {
			victory::deInit();
			pause_menu::deInit();
			animations::deInit();
			players::deInit();
			asteroids::deInit();
			UnloadTexture(gameplay_vintage);
			UnloadTexture(gameplay_tutorial);
			UnloadTexture(pause_btn.btn_texture);
		}
	}
}

