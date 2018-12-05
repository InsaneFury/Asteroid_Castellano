#include "victory.h"

#include "gameplay.h"
#include "Logic/game.h"
#include "Utility/buttons.h"
#include "Characters/Enemys/asteroids.h"

namespace asteroid {
	namespace victory {
		using namespace game;
		using namespace gameplay;

		//Images
		static Texture2D gameover_bg;
		static Texture2D gameover_title;

		static Vector2 title_position;
		static Vector2 mouse_point;
		static int LEVEL1 = 25;

		static buttons::BTNTEX retry;
		static buttons::BTNTEX menu;
		static buttons::BTNTEX quit;

		void init() {
			gameover_bg = LoadTexture("res/Textures/GAMEOVER_BG.png");
			gameover_title = LoadTexture("res/Textures/VICTORY.png");

			retry.btn_texture = LoadTexture("res/Textures/RETRYONHOVER_BTN.png");
			retry.btnOnHover_texture = LoadTexture("res/Textures/RETRY_BTN.png");
			menu.btn_texture = LoadTexture("res/Textures/MENUONHOVER_BTN.png");
			menu.btnOnHover_texture = LoadTexture("res/Textures/MENU_BTN.png");
			quit.btn_texture = LoadTexture("res/Textures/QUIT_BTN.png");
			quit.btnOnHover_texture = LoadTexture("res/Textures/QUITONHOVER_BTN.png");

			title_position = { 
				(float)(screenWidth / 2 - gameover_title.width / 2) + 10,
				(float)(screenHeight / 2 - gameover_title.height / 2) - 180 
			};

			buttons::createButton(
				retry, 
				retry.btn_texture.height, 
				retry.btn_texture.width, 
				(float)(GetScreenWidth() / 2 - retry.btn_texture.width / 2), 
				(float)(GetScreenHeight() - 400), 
				WHITE);

			buttons::createButton(
				menu, 
				menu.btn_texture.height, 
				menu.btn_texture.width, 
				(float)(GetScreenWidth() / 2 - menu.btn_texture.width / 2),
				(float)(GetScreenHeight() - 330), 
				WHITE);

			buttons::createButton(
				quit, 
				quit.btn_texture.height, 
				quit.btn_texture.width, 
				(float)(GetScreenWidth() / 2 - quit.btn_texture.width / 2), 
				(float)(GetScreenHeight() - 260),
				WHITE);

		}

		void update(bool &isGameOver) {
			game::updateMouse();
			//mouse
			mouse_point = GetMousePosition();

			buttons::isMouseOverButton(retry);
			if (CheckCollisionPointRec(mouse_point, retry.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Game;
					gameplay::pause = false;
					gameplay::tutorial = true;
					gameplay::init();
				}
			}
			buttons::isMouseOverButton(menu);
			if (CheckCollisionPointRec(mouse_point, menu.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					gameplay::init();
					gameplay::pause = false;
					gameplay::tutorial = true;
					actualScene = Menu;
				}
			}
			buttons::isMouseOverButton(quit);
			if (CheckCollisionPointRec(mouse_point, quit.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					isGameOver = true;
				}
			}
		}

		void draw() {
			ClearBackground(WHITE);
			
			//Draw UI
			DrawTexture(gameover_bg, 0, 0, WHITE);
			DrawTextureEx(gameover_title, title_position, 0, 1, WHITE);

			//Draw buttons
			buttons::draw(retry);
			buttons::draw(menu);
			buttons::draw(quit);

			game::drawMouse();
		}

		void deInit() {
			//images
			UnloadTexture(gameover_bg);
			UnloadTexture(gameover_title);
			//buttons
			UnloadTexture(retry.btn_texture);
			UnloadTexture(menu.btn_texture);
			UnloadTexture(quit.btn_texture);
		}

		bool isVictory() {
			if (asteroids::destroyedMeteorsCount >= LEVEL1) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}