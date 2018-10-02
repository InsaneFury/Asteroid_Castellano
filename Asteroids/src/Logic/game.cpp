#include "game.h"
#include "Scenes/menu.h"
#include "Scenes/gameOver.h"
#include "Scenes/gameplay.h"
#include "Scenes/credits.h"

namespace asteroid {
	namespace game {
		static void init();
		static void update();
		static void draw();
		static void deInit();

		// Initialization
		//--------------------------------------------------------------------------------------
		int screenWidth = 1280;
		int screenHeight = 720;

		Music bgMusic;

		ActualScene actualScene = Menu;

		static bool endGame = false;

		void runGame() {
			init();

			// Main game loop
			while (!WindowShouldClose() && !endGame)
			{
				update();
				draw();
			}
			deInit();
		}

		void init() {
			//Initialization of all the game!
			SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)
			InitWindow(screenWidth, screenHeight, "Asteroid | by Ivan Castellano");
			InitAudioDevice();
			
			bgMusic = LoadMusicStream("res/Music/bgmusic.ogg");

			menu::init();
			gameplay::init();
			gameOver::init();
			credits::init();

			#ifdef AUDIO
			#define AUDIO
				PlayMusicStream(bgMusic);
				SetMusicVolume(bgMusic, 1.0f);
			#endif // !AUDIO
			SetExitKey(0);
		}

		void update() {
			// Update
			//----------------------------------------------------------------------------------
			UpdateMusicStream(bgMusic);
			switch (actualScene) {
			case Menu:
				menu::update(endGame);
				break;
			case Game:
				gameplay::update();
				break;
			case Gameover:
				gameOver::update(endGame);
				break;
			case Credits:
				credits::update();
				break;
			default:
				break;
			}
		}

		void draw() {
			// Draw
			//----------------------------------------------------------------------------------
			BeginDrawing();

			ClearBackground(RAYWHITE);
			switch (actualScene) {
			case Menu:
				menu::draw();
				break;
			case Game:
				gameplay::draw();
				break;
			case Gameover:
				gameOver::draw();
				break;
			case Credits:
				credits::draw();
				break;
			default:
				DrawText("An error has occurred please contact a Dev", screenWidth / 2, screenHeight / 2, 20, RED);
				break;
			}
			EndDrawing();
		}

		void deInit() {
			// De-Initialization
			//--------------------------------------------------------------------------------------
			#ifdef AUDIO
			#define AUDIO
				UnloadMusicStream(bgMusic);
				CloseAudioDevice();
			#endif // !AUDIO
				gameplay::deInit();
				credits::deInit();
				menu::deInit();
			CloseWindow();        // Close window and OpenGL context
		}
	}

	

}



