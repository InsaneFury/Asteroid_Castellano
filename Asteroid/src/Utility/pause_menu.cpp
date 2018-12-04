#include "pause_menu.h"

#include "Scenes/gameplay.h"
#include "Logic/game.h"
#include "buttons.h"
#include "Logic/game.h"

namespace asteroid {
	namespace pause_menu {
		using namespace game;
		using namespace gameplay;

		//Images
		static Texture2D pause_bg;
		static Texture2D pause_title;

		static Vector2 title_position;
		static Vector2 mouse_point;

		static buttons::BTNTEX resume;
		static buttons::BTNTEX retry;
		static buttons::BTNTEX menu;
		static buttons::BTNTEX quit;
		static buttons::BTNTEX mute;
		static buttons::BTNTEX unmute;

		static bool isPlaying;

		void init() {
			pause_bg = LoadTexture("res/Textures/PAUSE_BG.png");
			pause_title = LoadTexture("res/Textures/PAUSE_TITLE.png");

			resume.btn_texture = LoadTexture("res/Textures/RESUMEONHOVER_BTN.png");
			resume.btnOnHover_texture = LoadTexture("res/Textures/RESUME_BTN.png");
			retry.btn_texture = LoadTexture("res/Textures/RETRYONHOVER_BTN.png");
			retry.btnOnHover_texture = LoadTexture("res/Textures/RETRY_BTN.png");
			menu.btn_texture = LoadTexture("res/Textures/MENUONHOVER_BTN.png");
			menu.btnOnHover_texture = LoadTexture("res/Textures/MENU_BTN.png");
			quit.btn_texture = LoadTexture("res/Textures/QUIT_BTN.png");
			quit.btnOnHover_texture = LoadTexture("res/Textures/QUITONHOVER_BTN.png");
			mute.btn_texture = LoadTexture("res/Textures/MUTE_BTN.png");
			mute.btnOnHover_texture = LoadTexture("res/Textures/MUTE_BTN.png");
			unmute.btn_texture = LoadTexture("res/Textures/MUTEON_BTN.png");
			unmute.btnOnHover_texture = LoadTexture("res/Textures/MUTEON_BTN.png");

			title_position = { 
				(float)(screenWidth / 2 - pause_title.width / 2) + 10, 
				(float)(screenHeight / 2 - pause_title.height / 2) - 180 
			};

			buttons::createButton(
				resume,
				resume.btn_texture.height, 
				resume.btn_texture.width, 
				(float)(GetScreenWidth() / 2 - resume.btn_texture.width / 2),
				(float)(GetScreenHeight() - 400),
				WHITE);

			buttons::createButton(
				retry, 
				retry.btn_texture.height,
				retry.btn_texture.width, 
				(float)(GetScreenWidth() / 2 - retry.btn_texture.width / 2),
				(float)(GetScreenHeight() - 330), 
				WHITE);

			buttons::createButton(
				menu, 
				menu.btn_texture.height,
				menu.btn_texture.width, 
				(float)(GetScreenWidth() / 2 - menu.btn_texture.width / 2),
				(float)(GetScreenHeight() - 260),
				WHITE);

			buttons::createButton(
				quit, 
				quit.btn_texture.height, 
				quit.btn_texture.width,
				(float)(GetScreenWidth() / 2 - quit.btn_texture.width / 2), 
				(float)(GetScreenHeight() - 190), 
				WHITE);

			buttons::createButton(
				mute, 
				mute.btn_texture.height,
				mute.btn_texture.width, 
				(float)(GetScreenWidth() / 2 - mute.btn_texture.width / 2), 
				(float)(GetScreenHeight() - 120), 
				WHITE);

			buttons::createButton(
				unmute,
				unmute.btn_texture.height, 
				unmute.btn_texture.width, 
				(float)(GetScreenWidth() / 2 - unmute.btn_texture.width / 2),
				(float)(GetScreenHeight() - 120), 
				WHITE);

			isPlaying = true;
		}

		void update(bool &isGameOver) {

			//mouse
			mouse_point = GetMousePosition();
			
			buttons::isMouseOverButton(resume);
			if (CheckCollisionPointRec(mouse_point, resume.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					pause = !pause;
				}
			}
			buttons::isMouseOverButton(retry);
			if (CheckCollisionPointRec(mouse_point, retry.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Game;
					pause_menu::pause = false;
					gameplay::tutorial = true;
					gameplay::init();
				}
			}
			buttons::isMouseOverButton(menu);
			if (CheckCollisionPointRec(mouse_point, menu.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					gameplay::init();
					pause_menu::pause = false;
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
			buttons::isMouseOverButton(mute);
			if (CheckCollisionPointRec(mouse_point, mute.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					if (isPlaying) {
						PauseMusicStream(bgMusic);
						isPlaying = false;
					}
					else {
						PlayMusicStream(bgMusic);
						isPlaying = true;
					}
				}
			}
		}

		void draw() {
			//Draw UI
			DrawTexture(pause_bg, 0, 0, WHITE);
			DrawTextureEx(pause_title, title_position, 0, 1, WHITE);

			//Draw buttons
			buttons::draw(resume);
			buttons::draw(retry);
			buttons::draw(menu);
			buttons::draw(quit);
			if (isPlaying) {
				buttons::draw(mute);
			}
			else {
				buttons::draw(unmute);
			}	
		}

		void deInit() {
			//images
			UnloadTexture(pause_bg);
			UnloadTexture(pause_title);
			//buttons
			UnloadTexture(resume.btn_texture);
			UnloadTexture(retry.btn_texture);
			UnloadTexture(menu.btn_texture);
			UnloadTexture(quit.btn_texture);
			UnloadTexture(mute.btn_texture);
			UnloadTexture(unmute.btn_texture);
		}
	}
}