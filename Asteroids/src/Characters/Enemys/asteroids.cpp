#include "asteroids.h"
#include "Characters\Player\player.h"
#include "Characters\Player\gun.h"
#include <math.h>

namespace asteroid {
	namespace asteroids {
		using namespace players;
		using namespace gun;

		static const int METEORS_SPEED = 1;
		const int MAX_BIG_METEORS = 4;
		const int MAX_MEDIUM_METEORS = 8;
		const int MAX_SMALL_METEORS = 16;

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
				bigMeteor[i].radius = 40;
				bigMeteor[i].active = true;
				bigMeteor[i].color = BLUE;
			}

			for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
			{
				mediumMeteor[i].position = { -100, -100 };
				mediumMeteor[i].speed = { 0, 0 };
				mediumMeteor[i].radius = 20;
				mediumMeteor[i].active = false;
				mediumMeteor[i].color = BLUE;
			}

			for (int i = 0; i < MAX_SMALL_METEORS; i++)
			{
				smallMeteor[i].position = { -100, -100 };
				smallMeteor[i].speed = { 0, 0 };
				smallMeteor[i].radius = 10;
				smallMeteor[i].active = false;
				smallMeteor[i].color = BLUE;
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
					// Movement
					bigMeteor[i].position.x += bigMeteor[i].speed.x;
					bigMeteor[i].position.y += bigMeteor[i].speed.y;

					// Collision logic: meteor vs wall
					if (bigMeteor[i].position.x > GetScreenWidth() + bigMeteor[i].radius) bigMeteor[i].position.x = -(bigMeteor[i].radius);
					else if (bigMeteor[i].position.x < 0 - bigMeteor[i].radius) bigMeteor[i].position.x = GetScreenWidth() + bigMeteor[i].radius;
					if (bigMeteor[i].position.y > GetScreenHeight() + bigMeteor[i].radius) bigMeteor[i].position.y = -(bigMeteor[i].radius);
					else if (bigMeteor[i].position.y < 0 - bigMeteor[i].radius) bigMeteor[i].position.y = GetScreenHeight() + bigMeteor[i].radius;
				}
			}

			// Meteors logic: medium meteors
			for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
			{
				if (mediumMeteor[i].active)
				{
					// Movement
					mediumMeteor[i].position.x += mediumMeteor[i].speed.x;
					mediumMeteor[i].position.y += mediumMeteor[i].speed.y;

					// Collision logic: meteor vs wall
					if (mediumMeteor[i].position.x > GetScreenWidth() + mediumMeteor[i].radius) mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
					else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.x = GetScreenWidth() + mediumMeteor[i].radius;
					if (mediumMeteor[i].position.y > GetScreenHeight() + mediumMeteor[i].radius) mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
					else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) mediumMeteor[i].position.y = GetScreenHeight() + mediumMeteor[i].radius;
				}
			}

			// Meteors logic: small meteors
			for (int i = 0; i < MAX_SMALL_METEORS; i++)
			{
				if (smallMeteor[i].active)
				{
					// Movement
					smallMeteor[i].position.x += smallMeteor[i].speed.x;
					smallMeteor[i].position.y += smallMeteor[i].speed.y;

					// Collision logic: meteor vs wall
					if (smallMeteor[i].position.x > GetScreenWidth() + smallMeteor[i].radius) smallMeteor[i].position.x = -(smallMeteor[i].radius);
					else if (smallMeteor[i].position.x < 0 - smallMeteor[i].radius) smallMeteor[i].position.x = GetScreenWidth() + smallMeteor[i].radius;
					if (smallMeteor[i].position.y > GetScreenHeight() + smallMeteor[i].radius) smallMeteor[i].position.y = -(smallMeteor[i].radius);
					else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) smallMeteor[i].position.y = GetScreenHeight() + smallMeteor[i].radius;
				}
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
							// smallMeteor[c].position = (Vector2){-100, -100};
							c = MAX_SMALL_METEORS;
						}
					}
				}
			}
		}


		void draw() {
			// Draw meteors
			for (int i = 0; i < MAX_BIG_METEORS; i++)
			{
				if (bigMeteor[i].active) DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, DARKGRAY);
				else DrawCircleV(bigMeteor[i].position, bigMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
			}

			for (int i = 0; i < MAX_MEDIUM_METEORS; i++)
			{
				if (mediumMeteor[i].active) DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, GRAY);
				else DrawCircleV(mediumMeteor[i].position, mediumMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
			}

			for (int i = 0; i < MAX_SMALL_METEORS; i++)
			{
				if (smallMeteor[i].active) DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, GRAY);
				else DrawCircleV(smallMeteor[i].position, smallMeteor[i].radius, Fade(LIGHTGRAY, 0.3f));
			}
		}

		void deInit() {

		}
	}
}
