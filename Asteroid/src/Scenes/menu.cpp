#include "menu.h"

#include "Logic/game.h"
#include "Utility/buttons.h"

namespace asteroid {
	namespace menu {
		using namespace game;

		//Images
		static Texture2D menu_bg;

		static Vector2 title_position;
		static Vector2 mouse_point;

		static buttons::BTNTEX play;
		static buttons::BTNTEX credits;
		static buttons::BTNTEX quit;

		void init() {
			menu_bg = LoadTexture("res/Textures/NEW_BG_MENU.png");

			play.btn_texture = LoadTexture("res/Textures/PLAY_BTN.png");
			credits.btn_texture = LoadTexture("res/Textures/CREDITS_BTN.png");
			quit.btn_texture = LoadTexture("res/Textures/QUIT_BTN.png");
			play.btnOnHover_texture = LoadTexture("res/Textures/PLAYONHOVER_BTN.png");
			credits.btnOnHover_texture = LoadTexture("res/Textures/CREDITSONHOVER_BTN.png");
			quit.btnOnHover_texture = LoadTexture("res/Textures/QUITONHOVER_BTN.png");

			buttons::createButton(
				play,
				play.btn_texture.height, 
				play.btn_texture.width, 
				(float)(GetScreenWidth() / 2 - play.btn_texture.width / 2), 
				(float)(GetScreenHeight() - 400), 
				WHITE);

			buttons::createButton(
				credits, 
				credits.btn_texture.height, 
				credits.btn_texture.width, 
				(float)(GetScreenWidth() / 2 - credits.btn_texture.width / 2), 
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

		void update(bool &endGame) {
			game::updateMouse();
			mouse_point = GetMousePosition();

			buttons::isMouseOverButton(play);
			if (CheckCollisionPointRec(mouse_point, play.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Game;
				}
			}
			buttons::isMouseOverButton(credits);
			if (CheckCollisionPointRec(mouse_point, credits.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Credits;
				}
			}

			buttons::isMouseOverButton(quit);
			if (CheckCollisionPointRec(mouse_point, quit.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					endGame = true;
				}
			}
		}

		void draw() {
			ClearBackground(WHITE);
			
			//Draw UI
			DrawTexture(menu_bg,0,0,WHITE);

			//Draw buttons
			buttons::draw(play);
			buttons::draw(credits);
			buttons::draw(quit);
			DrawText("v1.2", screenWidth - 50, screenHeight - 20, 20, WHITE);
			game::drawMouse();
		}

		void deInit() {
			//images
			UnloadTexture(menu_bg);
			//buttons
			UnloadTexture(play.btn_texture);
			UnloadTexture(credits.btn_texture);
			UnloadTexture(quit.btn_texture);
			UnloadTexture(play.btnOnHover_texture);
			UnloadTexture(credits.btnOnHover_texture);
			UnloadTexture(quit.btnOnHover_texture);	
		}
	}
}

