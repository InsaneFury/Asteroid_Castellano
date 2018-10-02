#include "player.h"
#include "gun.h"
#include <math.h>

namespace asteroid {
	namespace players {

		Player player;

		float PLAYER_SPEED = 1;
		static float timer; //Animations coming soon

		void init() {
			player.texture = LoadTexture("res/Textures/space_ship.png");
			player.position = { (float)GetScreenWidth() / 2 - player.texture.width / 2,(float)GetScreenHeight() / 2 - player.texture.height / 2 };
			player.color = WHITE;
			player.acceleration = 0;
			player.rotation = 0;
			player.speed.x = 0;
			player.speed.y = 0;
			player.score = 0;

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

			// Player logic: rotation
			if (IsKeyDown(KEY_A)) player.rotation -= 0.5f;
			if (IsKeyDown(KEY_D)) player.rotation += 0.5f;

			// Player logic: speed
			player.speed.x = sin(player.rotation*DEG2RAD)*PLAYER_SPEED;
			player.speed.y = cos(player.rotation*DEG2RAD)*PLAYER_SPEED;

			// Player logic: acceleration
			if (IsKeyDown(KEY_W))
			{
				if (player.acceleration < 1) player.acceleration += 0.01f;
			}
			else
			{
				if (player.acceleration > 0) player.acceleration -= 0.01f;
				else if (player.acceleration < 0) player.acceleration = 0;
			}
			if (IsKeyDown(KEY_S))
			{
				if (player.acceleration > 0) player.acceleration -= 0.01f;
				else if (player.acceleration < 0) player.acceleration = 0;
			}

			// Player logic: movement
			player.position.x += (player.speed.x*player.acceleration);
			player.position.y -= (player.speed.y*player.acceleration);

			// Collision logic: player vs walls
			if (player.position.x > GetScreenWidth() + player.texture.height) player.position.x = -(player.texture.height);
			else if (player.position.x < -(player.texture.height)) player.position.x = GetScreenWidth() + player.texture.height;
			if (player.position.y > (GetScreenHeight() + player.texture.height)) player.position.y = -(player.texture.height);
			else if (player.position.y < -(player.texture.height)) player.position.y = GetScreenHeight() + player.texture.height;

			player.destRec = { player.position.x, player.position.y, (float)player.texture.width, (float)player.texture.height };

			gun::update();
		}

		void draw() {
			DrawTexturePro(player.texture,player.sourceRec,player.destRec,player.origin,player.rotation,player.color);
			gun::draw();
		}

		void deInit() {
			UnloadTexture(player.texture);
			gun::deInit();
		}
	}
}