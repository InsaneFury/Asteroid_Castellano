#include "player.h"

#include <cmath>
#include <iostream>

#include "gun.h"
#include "Characters/Enemys/asteroids.h"
#include "Logic/game.h"
#include "Scenes/victory.h"

namespace asteroid {
	namespace players {
		using namespace asteroids;
		using namespace game;
		Player player;

		static bool isMoving;

		static int PLAYER_ORIENTATION = 90;
		float PLAYER_SPEED = 100;
		static float PLAYER_ROTATION_SPEED = 300.0f;
		static float timer; //Animations coming soon
		
		static Vector2 mousePosition;
		static Vector2 U;
		static Vector2 UNormalized;

		void init() {

			player.texture = LoadTexture("res/Textures/space_ship.png");
			player.motor = LoadTexture("res/Textures/space_ship_motor.png");

			player.position = { 
				(float)GetScreenWidth() / 2 - player.texture.width / 2,
				(float)GetScreenHeight() / 2 - player.texture.height / 2
			};

			player.color = WHITE;
			player.acceleration = {0,0};
			player.rotation = 0;
			player.speed.x = 0;
			player.speed.y = 0;
			player.radius = (float)player.texture.width /2;
			player.score = 0;
			isMoving = false;

			U = { 0, 0 };
			UNormalized = { 0,0 };

			// NOTE: Source rectangle (part of the texture to use for drawing)
			player.sourceRec = { 
				0.0f,
				0.0f, 
				(float)player.texture.width, 
				(float)player.texture.height 
			};

			// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
			player.destRec = { 
				player.position.x, 
				player.position.y, 
				(float)player.texture.width, 
				(float)player.texture.height
			};

			// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
			player.origin = { 
				(float)player.texture.width/2, 
				(float)player.texture.height/2 
			};

			gun::init();

			//FrameTimeCounter
			timer = 0;

		}

		void update() {
			timer += GetFrameTime();

			mousePosition = GetMousePosition();

			//Distancia entre player y mouse
			U = {  mousePosition.x - player.position.x  , mousePosition.y - player.position.y };

			player.rotation = (atan2(U.y,U.x)*RAD2DEG) + PLAYER_ORIENTATION;
	
			// Player logic: acceleration
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
				float modU = sqrt(pow(U.x, 2) + pow(U.y, 2));
				UNormalized.x = U.x / modU;
				UNormalized.y = U.y / modU;
				player.acceleration.x += UNormalized.x * GetFrameTime();
				player.acceleration.y += UNormalized.y * GetFrameTime();

				isMoving = true;
			}
			else {
				isMoving = false;
			}
			
			player.position.x += player.acceleration.x  * GetFrameTime();
			player.position.y += player.acceleration.y  * GetFrameTime();

			// Collision logic: player vs walls
			if (player.position.x > GetScreenWidth() + player.radius) {
				player.position.x = -(player.radius);
			}

			else if (player.position.x < -(player.radius)) {
				player.position.x = GetScreenWidth() + player.radius;
			}

			if (player.position.y > (GetScreenHeight() + player.radius)) {
				player.position.y = -(player.radius);
			}

			else if (player.position.y < -(player.radius)) {
				player.position.y = GetScreenHeight() + player.radius;
			}

			// Collision logic: player vs meteors

			for (int a = 0; a < MAX_BIG_METEORS; a++)
			{
				if (CheckCollisionCircles(
					player.position, 
					player.radius, 
					bigMeteor[a].position, 
					bigMeteor[a].radius) 
					&& bigMeteor[a].active) {

					if (!victory::isVictory()) {
						actualScene = Gameover;
					}	

				}
			}

			for (int a = 0; a < MAX_MEDIUM_METEORS; a++)
			{
				if (CheckCollisionCircles(
					player.position, 
					player.radius, 
					mediumMeteor[a].position, 
					mediumMeteor[a].radius) 
					&& mediumMeteor[a].active) {

					if (!victory::isVictory()) {
						actualScene = Gameover;
					}

				}
			}

			for (int a = 0; a < MAX_SMALL_METEORS; a++)
			{
				if (CheckCollisionCircles(
					player.position, 
					player.radius,
					smallMeteor[a].position, 
					smallMeteor[a].radius)
					&& smallMeteor[a].active) {

					if (!victory::isVictory()) {
						actualScene = Gameover;
					}

				}
			}

			player.destRec = { 
				player.position.x, 
				player.position.y, 
				(float)player.texture.width, 
				(float)player.texture.height 
			};

			gun::update();
		}

		void draw() {

			DrawTexturePro(
				player.texture,
				player.sourceRec,
				player.destRec,
				player.origin,
				player.rotation,
				player.color);

			if (isMoving) {

			DrawTexturePro(
				player.motor, 
				player.sourceRec, 
				player.destRec, 
				player.origin, 
				player.rotation,
				player.color);
			}

			gun::draw();
		}

		void deInit() {
			UnloadTexture(player.texture);
			UnloadTexture(player.motor);
			gun::deInit();
		}
	}
}