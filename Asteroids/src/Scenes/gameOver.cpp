#include "gameOver.h"
#include "gameplay.h"
#include "Logic/game.h"
#include "Utility/buttons.h"

namespace asteroid {
	namespace gameOver {
		using namespace game;
		using namespace gameplay;

		buttons::BTN retry;
		buttons::BTN menu;
		buttons::BTN quit;

		Rectangle rec;

		//Line pos
		Vector2 startPos;
		Vector2 endPos;

		int lineThick; //Rec line
		float thick; //Simple line

		void init() {
			buttons::createButton(retry, 80, 400, (float)(GetScreenWidth() / 2 - 200), (float)(GetScreenHeight() - 350), 5, 40, GRAY, DARKGRAY, SKYBLUE);
			buttons::createButton(menu, 80, 400, (float)(GetScreenWidth() / 2 - 200), (float)(GetScreenHeight() - 260), 5, 40, GRAY, DARKGRAY, SKYBLUE);
			buttons::createButton(quit, 80, 400, (float)(GetScreenWidth() / 2 - 200), (float)(GetScreenHeight() - 170), 5, 40, GRAY, DARKGRAY, SKYBLUE);

			rec.height = 150;
			rec.width = 400;
			rec.x = GetScreenWidth() / 2 - rec.width / 2;
			rec.y = GetScreenHeight() / 2 - rec.height;

			startPos = { (float)(rec.x) , (float)(GetScreenHeight() - 160) };
			endPos = { (float)(rec.x + 400) , (float)(GetScreenHeight() - 160) };

			lineThick = 5; //Rec line
			thick = 4; //Simple line
		}

		void update(bool &endGame) {

			//mouse
			Vector2 mousePoint = GetMousePosition();


			buttons::isMouseOverButton(retry);
			if (CheckCollisionPointRec(mousePoint, retry.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Game;
					gameplay::init();
				}
			}

			buttons::isMouseOverButton(quit);
			if (CheckCollisionPointRec(mousePoint, quit.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					endGame = true;
				}
			}

			buttons::isMouseOverButton(menu);
			if (CheckCollisionPointRec(mousePoint, menu.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					gameplay::init();
					actualScene = Menu;
				}
			}
		}

		void draw() {
			ClearBackground(WHITE);

			//Draw UI
			DrawText("GAME OVER", GetScreenWidth() / 2 - MeasureText("GAME OVER",100)/2, GetScreenHeight() / 2 - 150, 100, GRAY);

			//Draw buttons
			buttons::draw(retry, "RETRY");
			buttons::draw(menu, "MENU");
			buttons::draw(quit, "QUIT");
		}
	}
}


		
		