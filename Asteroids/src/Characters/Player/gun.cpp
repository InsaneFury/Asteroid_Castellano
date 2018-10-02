#include "gun.h"
#include "player.h"
#include <math.h>

namespace asteroid {
	namespace gun {
		using namespace players;

		const int PLAYER_MAX_SHOOTS = 10;

		Shoot shoot[PLAYER_MAX_SHOOTS];

		void init() {

			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++){
				shoot[i].texture = LoadTexture("res/Textures/shoot.png");
				shoot[i].position = { 0, 0 };
				shoot[i].speed = { 0, 0 };
				shoot[i].radius = 2;
				shoot[i].active = false;
				shoot[i].lifeSpawn = 0;
				shoot[i].color = WHITE;
				// NOTE: Source rectangle (part of the texture to use for drawing)
				shoot[i].sourceRec = { 0.0f, 0.0f, (float)shoot[i].texture.width, (float)shoot[i].texture.height };

				// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
				shoot[i].destRec = { shoot[i].position.x, shoot[i].position.y, (float)shoot[i].texture.width, (float)shoot[i].texture.height };

				// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
				shoot[i].origin = { (float)shoot[i].texture.width / 2, (float)shoot[i].texture.height / 2 };
			}
		}

		void update() {
			
			// Player shoot logic
			if (IsKeyPressed(KEY_SPACE)){
				for (int i = 0; i < PLAYER_MAX_SHOOTS; i++){
					if (!shoot[i].active){
						shoot[i].position = {(float) (player.position.x + sin(player.rotation*DEG2RAD)*(player.texture.height)),(float)(player.position.y - cos(player.rotation*DEG2RAD)*(player.texture.height)) };
						shoot[i].active = true;
						shoot[i].destRec = { shoot[i].position.x, shoot[i].position.y, (float)shoot[i].texture.width, (float)shoot[i].texture.height };
						shoot[i].speed.x = 1.5*sin(player.rotation*DEG2RAD)*PLAYER_SPEED;
						shoot[i].speed.y = 1.5*cos(player.rotation*DEG2RAD)*PLAYER_SPEED;
						shoot[i].rotation = player.rotation;
						break;
					}
				}
			}

			// Shoot life timer
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++){
				if (shoot[i].active) shoot[i].lifeSpawn++;
			}

			// Shot logic
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++){
				if (shoot[i].active){
					// Movement
					shoot[i].position.x += shoot[i].speed.x;
					shoot[i].position.y -= shoot[i].speed.y;
					shoot[i].destRec = { shoot[i].position.x, shoot[i].position.y, (float)shoot[i].texture.width, (float)shoot[i].texture.height };

					// Collision logic: shoot vs walls
					if (shoot[i].position.x > GetScreenWidth() + shoot[i].radius){
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					else if (shoot[i].position.x < 0 - shoot[i].radius){
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					if (shoot[i].position.y > GetScreenHeight() + shoot[i].radius){
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}
					else if (shoot[i].position.y < 0 - shoot[i].radius){
						shoot[i].active = false;
						shoot[i].lifeSpawn = 0;
					}

					// Life of shoot
					if (shoot[i].lifeSpawn >= 240) {
						shoot[i].position = { 0, 0 };
						shoot[i].speed = { 0, 0 };
						shoot[i].lifeSpawn = 0;
						shoot[i].active = false;
					}
					
				}
			}
		}

		void draw() {
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
				if (shoot[i].active) {
					DrawTexturePro(shoot[i].texture, shoot[i].sourceRec, shoot[i].destRec, shoot[i].origin, shoot[i].rotation, shoot[i].color);
				}
			}
		}

		void deInit() {
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
				UnloadTexture(shoot[i].texture);
			}
		}
	}
}

