#include "asteroids.h"
#include "Characters\Player\player.h"
#include "Characters\Player\gun.h"
#include <math.h>

namespace asteroid {
	namespace asteroids {
		using namespace players;
		using namespace gun;

		static const int METEORS_SPEED = 150;
		static const float METEOR_ROTATION_SPEED = 100.0f;
		const int MAX_BIG_METEORS = 6;
		const int MAX_MEDIUM_METEORS = 12;
		const int MAX_SMALL_METEORS = 24;

		Meteor bigMeteor[MAX_BIG_METEORS];
		Meteor mediumMeteor[MAX_MEDIUM_METEORS];
		Meteor smallMeteor[MAX_SMALL_METEORS];

		static int midMeteorsCount;
		static int smallMeteorsCount;
		static int destroyedMeteorsCount;

		static int posx, posy;
		static int velx, vely;
		
		bool correctRange;
		bool victory;
		bool pause;

		void init() {

			bool correctRange = false;
			victory = false;
			pause = false;
			destroyedMeteorsCount = 0;

			for (int i = 0; i < MAX_BIG_METEORS; i++)
			{
				bigMeteor[i].texture = LoadTexture("res/Textures/BIG_METEOR.png");

				posx = GetRandomValue(0, GetScreenWidth());

				while (!correctRange)
				{
					if (posx > GetScreenWidth() / 2 - 150 && posx < GetScreenWidth() / 2 + 150) posx = GetRandomValue(0, GetScreenWidth());
					else correctRange = true;
				}

				correctRange = false;

				posy = GetRandomValue(0, GetScreenHeight());

				while (!correctRange)
				{
					if (posy > GetScreenHeight() / 2 - 150 && posy < GetScreenHeight() / 2 + 150)  posy = GetRandomValue(0, GetScreenHeight());
					else correctRange = true;
				}

				bigMeteor[i].position = { (float)posx,(float)posy };

				correctRange = false;
				velx = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);
				vely = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);

				while (!correctRange)
				{
					if (velx == 0 && vely == 0)
					{
						velx = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);
						vely = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);
					}
					else correctRange = true;
				}

				bigMeteor[i].speed = { (float)velx, (float)vely };
				bigMeteor[i].radius = bigMeteor[i].texture.width / 2;
				bigMeteor[i].active = true;
				bigMeteor[i].color = WHITE;

				// NOTE: Source rectangle (part of the texture to use for drawing)
				bigMeteor[i].sourceRec = { 0.0f, 0.0f, (float)bigMeteor[i].texture.width, (float)bigMeteor[i].texture.height };

				// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
				bigMeteor[i].destRec = { bigMeteor[i].position.x, bigMeteor[i].position.y, (float)bigMeteor[i].texture.width, (float)bigMeteor[i].texture.height };

				// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
				bigMeteor[i].origin = { (float)bigMeteor[i].texture.width / 2, (float)bigMeteor[i].texture.height / 2 };
			}

			for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
			{
				mediumMeteor[i].texture = LoadTexture("res/Textures/MEDIUM_METEOR.png");
				mediumMeteor[i].position = { -100, -100 };
				mediumMeteor[i].speed = { 0, 0 };
				mediumMeteor[i].radius = mediumMeteor[i].texture.width / 2;
				mediumMeteor[i].active = false;
				mediumMeteor[i].color = WHITE;

				// NOTE: Source rectangle (part of the texture to use for drawing)
				mediumMeteor[i].sourceRec = { 0.0f, 0.0f, (float)mediumMeteor[i].texture.width, (float)mediumMeteor[i].texture.height };

				// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
				mediumMeteor[i].destRec = { mediumMeteor[i].position.x, mediumMeteor[i].position.y, (float)mediumMeteor[i].texture.width, (float)mediumMeteor[i].texture.height };

				// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
				mediumMeteor[i].origin = { (float)mediumMeteor[i].texture.width / 2, (float)mediumMeteor[i].texture.height / 2 };
			}

			for (int i = 0; i < MAX_SMALL_METEORS; i++)
			{
				smallMeteor[i].texture = LoadTexture("res/Textures/SMALL_METEOR.png");
				smallMeteor[i].position = { -100, -100 };
				smallMeteor[i].speed = { 0, 0 };
				smallMeteor[i].radius = smallMeteor[i].texture.width / 2;
				smallMeteor[i].active = false;
				smallMeteor[i].color = WHITE;

				// NOTE: Source rectangle (part of the texture to use for drawing)
				smallMeteor[i].sourceRec = { 0.0f, 0.0f, (float)smallMeteor[i].texture.width, (float)smallMeteor[i].texture.height };

				// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
				smallMeteor[i].destRec = { smallMeteor[i].position.x, smallMeteor[i].position.y, (float)smallMeteor[i].texture.width, (float)smallMeteor[i].texture.height };

				// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
				smallMeteor[i].origin = { (float)smallMeteor[i].texture.width / 2, (float)smallMeteor[i].texture.height / 2 };
			}

			midMeteorsCount = 0;
			smallMeteorsCount = 0;
		}

		void update() {
			// Meteors logic: big meteors
			for (int i = 0; i < MAX_BIG_METEORS; i++)
			{
				if (bigMeteor[i].active)
				{
					//Rotation
					bigMeteor[i].rotation += METEOR_ROTATION_SPEED * GetFrameTime();

					// Movement
					bigMeteor[i].position.x += bigMeteor[i].speed.x * GetFrameTime();
					bigMeteor[i].position.y += bigMeteor[i].speed.y * GetFrameTime();

					// Collision logic: meteor vs wall
					if (bigMeteor[i].position.x > GetScreenWidth() + bigMeteor[i].texture.height) bigMeteor[i].position.x = -(bigMeteor[i].texture.height);
					else if (bigMeteor[i].position.x < 0 - bigMeteor[i].texture.height) bigMeteor[i].position.x = GetScreenWidth() + bigMeteor[i].texture.height;
					if (bigMeteor[i].position.y > GetScreenHeight() + bigMeteor[i].radius) bigMeteor[i].position.y = -(bigMeteor[i].radius);
					else if (bigMeteor[i].position.y < 0 - bigMeteor[i].texture.height) bigMeteor[i].position.y = GetScreenHeight() + bigMeteor[i].texture.height;
				}

				bigMeteor[i].destRec = { bigMeteor[i].position.x, bigMeteor[i].position.y, (float)bigMeteor[i].texture.width, (float)bigMeteor[i].texture.height };
			}

			// Meteors logic: medium meteors
			for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
			{
				if (mediumMeteor[i].active)
				{
					//Rotation
					mediumMeteor[i].rotation += METEOR_ROTATION_SPEED * GetFrameTime();

					// Movement
					mediumMeteor[i].position.x += mediumMeteor[i].speed.x * GetFrameTime();
					mediumMeteor[i].position.y += mediumMeteor[i].speed.y * GetFrameTime();

					// Collision logic: meteor vs wall
					if (mediumMeteor[i].position.x > GetScreenWidth() + mediumMeteor[i].texture.height) mediumMeteor[i].position.x = -(mediumMeteor[i].texture.height);
					else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].texture.height) mediumMeteor[i].position.x = GetScreenWidth() + mediumMeteor[i].texture.height;
					if (mediumMeteor[i].position.y > GetScreenHeight() + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].texture.height);
					else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].texture.height) mediumMeteor[i].position.y = GetScreenHeight() + mediumMeteor[i].texture.height;
				}

				mediumMeteor[i].destRec = { mediumMeteor[i].position.x, mediumMeteor[i].position.y, (float)mediumMeteor[i].texture.width, (float)mediumMeteor[i].texture.height };
			}

			// Meteors logic: small meteors
			for (int i = 0; i < MAX_SMALL_METEORS; i++)
			{
				if (smallMeteor[i].active)
				{
					//Rotation
					smallMeteor[i].rotation += METEOR_ROTATION_SPEED * GetFrameTime();

					// Movement
					smallMeteor[i].position.x += smallMeteor[i].speed.x * GetFrameTime();
					smallMeteor[i].position.y += smallMeteor[i].speed.y * GetFrameTime();

					// Collision logic: meteor vs wall
					if (smallMeteor[i].position.x > GetScreenWidth() + smallMeteor[i].texture.height) smallMeteor[i].position.x = -(smallMeteor[i].texture.height);
					else if (smallMeteor[i].position.x < 0 - smallMeteor[i].texture.height) smallMeteor[i].position.x = GetScreenWidth() + smallMeteor[i].texture.height;
					if (smallMeteor[i].position.y > GetScreenHeight() + smallMeteor[i].texture.height) smallMeteor[i].position.y = -(smallMeteor[i].texture.height);
					else if (smallMeteor[i].position.y < 0 - smallMeteor[i].texture.height) smallMeteor[i].position.y = GetScreenHeight() + smallMeteor[i].texture.height;
				}

				smallMeteor[i].destRec = { smallMeteor[i].position.x, smallMeteor[i].position.y, (float)smallMeteor[i].texture.width, (float)smallMeteor[i].texture.height };
			}

			// Collision logic: player-shoots vs meteors
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++)
			{
				if ((shoot[i].active))
				{
					for (int a = 0; a < MAX_BIG_METEORS; a++)
					{
						if (bigMeteor[a].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, bigMeteor[a].position, bigMeteor[a].radius))
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = 0;
							bigMeteor[a].active = false;
							destroyedMeteorsCount++;

							for (int j = 0; j < 2; j++)
							{
								if (midMeteorsCount % 2 == 0)
								{
									mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x, bigMeteor[a].position.y };
									mediumMeteor[midMeteorsCount].speed = { (float)(cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1), (float)(sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1) };
								}
								else
								{
									mediumMeteor[midMeteorsCount].position = { bigMeteor[a].position.x, bigMeteor[a].position.y };
									mediumMeteor[midMeteorsCount].speed = { (float)(cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED), (float)(sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED) };
								}

								mediumMeteor[midMeteorsCount].active = true;
								midMeteorsCount++;
							}
							bigMeteor[a].color = RED;
							a = MAX_BIG_METEORS;
						}
					}

					for (int b = 0; b < MAX_MEDIUM_METEORS; b++)
					{
						if (mediumMeteor[b].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, mediumMeteor[b].position, mediumMeteor[b].radius))
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = 0;
							mediumMeteor[b].active = false;
							destroyedMeteorsCount++;

							for (int j = 0; j < 2; j++)
							{
								if (smallMeteorsCount % 2 == 0)
								{
									smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
									smallMeteor[smallMeteorsCount].speed = { (float)(cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1), (float)(sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1) };
								}
								else
								{
									smallMeteor[smallMeteorsCount].position = { mediumMeteor[b].position.x, mediumMeteor[b].position.y };
									smallMeteor[smallMeteorsCount].speed = { (float)(cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED), (float)(sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED) };
								}

								smallMeteor[smallMeteorsCount].active = true;
								smallMeteorsCount++;
							}
							mediumMeteor[b].color = GREEN;
							b = MAX_MEDIUM_METEORS;
						}
					}

					for (int c = 0; c < MAX_SMALL_METEORS; c++)
					{
						if (smallMeteor[c].active && CheckCollisionCircles(shoot[i].position, shoot[i].radius, smallMeteor[c].position, smallMeteor[c].radius))
						{
							shoot[i].active = false;
							shoot[i].lifeSpawn = 0;
							smallMeteor[c].active = false;
							destroyedMeteorsCount++;
							smallMeteor[c].color = YELLOW;
							c = MAX_SMALL_METEORS;
						}
					}
				}
			}
		}


		void draw() {
			for (int i = 0; i < MAX_BIG_METEORS; i++)
			{
				if (bigMeteor[i].active) {
					DrawTexturePro(bigMeteor[i].texture, bigMeteor[i].sourceRec, bigMeteor[i].destRec, bigMeteor[i].origin, bigMeteor[i].rotation, WHITE);
				}
			}

			for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
			{
				if (mediumMeteor[i].active) {
					DrawTexturePro(mediumMeteor[i].texture, mediumMeteor[i].sourceRec, mediumMeteor[i].destRec, mediumMeteor[i].origin, mediumMeteor[i].rotation, WHITE);
				}
			}

			for (int i = 0; i < MAX_SMALL_METEORS; i++)
			{
				if (smallMeteor[i].active) {
					DrawTexturePro(smallMeteor[i].texture, smallMeteor[i].sourceRec, smallMeteor[i].destRec, smallMeteor[i].origin, smallMeteor[i].rotation, WHITE);
				}
			}
		}

		void deInit() {
			for (int i = 0; i < MAX_BIG_METEORS; i++)
			{
				UnloadTexture(bigMeteor[i].texture);
			}
			for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
			{
				UnloadTexture(mediumMeteor[i].texture);
			}

			for (int i = 0; i < MAX_SMALL_METEORS; i++)
			{
				UnloadTexture(smallMeteor[i].texture);
			}
		}
	}
}
