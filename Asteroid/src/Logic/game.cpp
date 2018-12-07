#include "game.h"

#include "Scenes/menu.h"
#include "Scenes/game_over.h"
#include "Scenes/gameplay.h"
#include "Scenes/credits.h"
#include "Utility/post_processing.h"


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

		//Mouse
		static Texture mouse;
		static Vector2 mouse_pointer; 
		static Rectangle sourceRec;  
		static Rectangle destRec;  
		static Vector2 origin;   
		static float rotation;  
		static int rotationSpeed;

		ActualScene actualScene = Menu;

		static bool isGameOver = false;
		
		void runGame() {
			init();

			// Main game loop
			while (!WindowShouldClose() && !isGameOver)
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

			HideCursor();
			initMouse();

			#ifdef AUDIO
			#define AUDIO
			InitAudioDevice();
			bgMusic = LoadMusicStream("res/Music/bgmusic.ogg");
			#endif // !AUDIO

			rotationSpeed = 300;
			//postprocessing::init();
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

			
			#ifdef AUDIO
			#define AUDIO
			UpdateMusicStream(bgMusic);
			#endif // AUDIO
			
			switch (actualScene) {
			case Menu:
				menu::update(isGameOver);
				break;
			case Game:
				gameplay::update(isGameOver);
				break;
			case Gameover:
				gameOver::update(isGameOver);
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

			//postprocessing::draw();
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
			//EndShaderMode();
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
				//postprocessing::deInit();
				gameplay::deInit();
				credits::deInit();
				menu::deInit();
				deInitMouse();
			CloseWindow();        // Close window and OpenGL context
		}

		void initMouse() {

			mouse = LoadTexture("res/Textures/MOUSE.png");

			mouse_pointer = GetMousePosition();

			sourceRec = {
				0.0f,
				0.0f,
				(float)(mouse.width),
				(float)(mouse.height)
			};

			destRec = {
				mouse_pointer.x,
				mouse_pointer.y,
				(float)(mouse.width),
				(float)(mouse.height)
			};

			origin = {
				(float)(mouse.width / 2),
				(float)(mouse.height / 2)
			};

			rotation = 0;
		}
		void updateMouse() {
			mouse_pointer = GetMousePosition();
			rotation += rotationSpeed * GetFrameTime();
			destRec = {
				mouse_pointer.x,
				mouse_pointer.y,
				(float)(mouse.width),
				(float)(mouse.height)
			};
		}

		void drawMouse() {
			DrawTexturePro(mouse, sourceRec, destRec, origin, rotation, WHITE);
		}

		void deInitMouse() {
			UnloadTexture(mouse);
		}
	}

	

}



