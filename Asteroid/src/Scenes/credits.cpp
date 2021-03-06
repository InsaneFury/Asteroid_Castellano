#include "credits.h"

#include "Logic/game.h"
#include "Utility/buttons.h"
#include "menu.h"

namespace asteroid {
	namespace credits {
		using namespace game;

		//Images
		static Texture2D credits_bg;
		static Texture2D credits_astronaut;
		static Texture2D credits_title;
		static Texture2D credits_text;

		static  Vector2 astronaut_position;
		static  Vector2 title_position;
		static  Vector2 text_position;

		static  buttons::BTNTEX back;

		//buttons::BTN back;

		void init() {
			credits_bg = LoadTexture("res/Textures/BG_CREDITS.png");
			credits_astronaut = LoadTexture("res/Textures/NEGATIVEASTRONAUT_CREDITS.png");
			credits_title = LoadTexture("res/Textures/TITLE_CREDITS.png");
			credits_text = LoadTexture("res/Textures/TEXT_CREDITS.png");

			astronaut_position = { 
				(float)(0 + credits_astronaut.width / 2) + 250,
				(float)(0 + credits_astronaut.height / 2) 
			};

			title_position = { 
				(float)(screenWidth / 2 - credits_title.width / 2), 
				(float)(screenHeight / 2 - credits_title.height / 2) - 150 
			};

			text_position = { 
				(float)(screenWidth / 2 - credits_text.width / 2), 
				(float)(screenHeight - credits_text.height / 2) - 275 
			};

			back.btn_texture = LoadTexture("res/Textures/BACK_BTN.png");
			back.btnOnHover_texture = LoadTexture("res/Textures/BACKONHOVER_BTN.png");

			buttons::createButton(
				back, 
				back.btn_texture.height,
				back.btn_texture.width, 
				(float)(0 + back.btn_texture.width/4), 
				(float)GetScreenHeight() - back.btn_texture.height - 20,
				WHITE);

		}

		void update() {
			game::updateMouse();
			Vector2 mouse_point = GetMousePosition();
			buttons::isMouseOverButton(back);

			if (CheckCollisionPointRec(mouse_point, back.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					menu::init();
					actualScene = Menu;
				}
			}
		}

		void draw() {
			ClearBackground(WHITE);
			
			//Draw UI
			DrawTexture(credits_bg, 0, 0, WHITE);
			DrawTextureEx(credits_astronaut, astronaut_position, 0, 1, WHITE);
			DrawTextureEx(credits_title, title_position, 0, 1, WHITE);
			DrawTextureEx(credits_text, text_position, 0, 1, WHITE);

			//Draw buttons
			buttons::draw(back);
			game::drawMouse();
		}

		void deInit() {
			//Images
			UnloadTexture(credits_bg);
			UnloadTexture(credits_astronaut);
			UnloadTexture(credits_title);
			UnloadTexture(credits_text);
			//Buttons
			UnloadTexture(back.btnOnHover_texture);
			UnloadTexture(back.btnOnHover_texture);

		}
	}
}
