#include "player.h"
#include "gun.h"
#include "Characters\Enemys\asteroids.h"
#include "Logic\game.h"
#include <math.h>
#include <iostream>

namespace asteroid {
	namespace players {
		using namespace asteroids;
		using namespace game;
		Player player;

		bool isMoving;

		int PLAYER_ORIENTATION = 90;
		float PLAYER_SPEED = 400;
		float PLAYER_ROTATION_SPEED = 300.0f;
		static float timer; //Animations coming soon
		
		Vector2 mousePosition;
		Vector2 U;
		
		void init() {
			player.texture = LoadTexture("res/Textures/space_ship.png");
			player.motor = LoadTexture("res/Textures/space_ship_motor.png");
			player.position = { (float)GetScreenWidth() / 2 - player.texture.width / 2,(float)GetScreenHeight() / 2 - player.texture.height / 2 };
			player.color = WHITE;
			player.acceleration = 0;
			player.rotation = 0;
			player.speed.x = 0;
			player.speed.y = 0;
			player.radius = (float)player.texture.width /2;
			player.score = 0;
			isMoving = false;

			U = { 0, 0 };

			// NOTE: Source rectangle (part of the texture to use for drawing)
			player.sourceRec = { 0.0f, 0.0f, (float)player.texture.width, (float)player.texture.height };

			// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
			player.destRec = { player.position.x, player.position.y, (float)player.texture.width, (float)player.texture.height};

			// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
			player.origin = { (float)player.texture.width/2, (float)player.texture.height/2 };

			gun::init();

			//FrameTimeCounter
			timer = GetFrameTime();

		}

		void update() {
			timer += GetFrameTime();

			mousePosition = GetMousePosition();

			//Distancia entre player y mouse
			U = {  mousePosition.x - player.position.x  , mousePosition.y - player.position.y };

			player.rotation = (atan2(U.y,U.x)*RAD2DEG) + PLAYER_ORIENTATION;
		
			// Player logic: speed
			player.speed.x = sin(player.rotation*DEG2RAD)*PLAYER_SPEED;
			player.speed.y = cos(player.rotation*DEG2RAD)*PLAYER_SPEED;

			// Player logic: acceleration
			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				if (player.acceleration < 1) {
					player.acceleration += 0.005f;
					isMoving = true;
				}
			}
			else
			{
				isMoving = false;
				if (player.acceleration > 0) {
					player.acceleration -= 0.001f ;
				}
				else if (player.acceleration < 0) {
					player.acceleration = 0;
				}
			}
			if (IsKeyDown(KEY_S))
			{
				if (player.acceleration > 0) {
					player.acceleration -= 0.01f;
				}
				else if (player.acceleration < 0) {
					player.acceleration = 0;
				}
			}

			// Player logic: movement
			player.position.x += (player.speed.x*player.acceleration* GetFrameTime());
			player.position.y -= (player.speed.y*player.acceleration* GetFrameTime());

			// Collision logic: player vs walls
			if (player.position.x > GetScreenWidth() + player.texture.height) player.position.x = -(player.texture.height);
			else if (player.position.x < -(player.texture.height)) player.position.x = GetScreenWidth() + player.texture.height;
			if (player.position.y > (GetScreenHeight() + player.texture.height)) player.position.y = -(player.texture.height);
			else if (player.position.y < -(player.texture.height)) player.position.y = GetScreenHeight() + player.texture.height;

			// Collision logic: player vs meteors

			for (int a = 0; a < MAX_BIG_METEORS; a++)
			{
				if (CheckCollisionCircles(player.position, player.radius, bigMeteor[a].position, bigMeteor[a].radius) && bigMeteor[a].active) {
					actualScene = Gameover;
				}
			}

			for (int a = 0; a < MAX_MEDIUM_METEORS; a++)
			{
				if (CheckCollisionCircles(player.position, player.radius, mediumMeteor[a].position, mediumMeteor[a].radius) && mediumMeteor[a].active) {
					actualScene = Gameover;
				}
			}

			for (int a = 0; a < MAX_SMALL_METEORS; a++)
			{
				if (CheckCollisionCircles(player.position, player.radius, smallMeteor[a].position, smallMeteor[a].radius) && smallMeteor[a].active) {
					actualScene = Gameover;
				}
			}

			player.destRec = { player.position.x, player.position.y, (float)player.texture.width, (float)player.texture.height };

			gun::update();
		}

		void draw() {
			DrawTexturePro(player.texture,player.sourceRec,player.destRec,player.origin,player.rotation,player.color);
			if (isMoving) {
			DrawTexturePro(player.motor, player.sourceRec, player.destRec, player.origin, player.rotation, player.color);
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