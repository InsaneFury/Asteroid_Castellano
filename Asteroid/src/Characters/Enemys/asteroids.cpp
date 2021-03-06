#include "asteroids.h"

#include <cmath>
#include <iostream>

#include "Characters\Player\player.h"
#include "Characters\Player\gun.h"

namespace asteroid {
	namespace asteroids {
		using namespace players;
		using namespace gun;

		static const int METEORS_SPEED = 150;
		static const float METEOR_ROTATION_SPEED = 100.0f;
		static const int MAX_BIG_METEORS = 6;
		static const int MAX_MEDIUM_METEORS = 12;
		static const int MAX_SMALL_METEORS = 24;

		Meteor bigMeteor[MAX_BIG_METEORS];
		Meteor mediumMeteor[MAX_MEDIUM_METEORS];
		Meteor smallMeteor[MAX_SMALL_METEORS];

		static Texture bigMeteorTex;
		static Texture mediumMeteorTex;
		static Texture smallMeteorTex;

		static int midMeteorsCount;
		static int smallMeteorsCount;
		int destroyedMeteorsCount;

		Vector2 range1, range2;
		static int posx, posy;
		static int velx, vely;
		
		static int safeZone;
		static bool victory;
		static bool pause;

		//Returns a value random between two diferents range for example [1,10] [45,100]
		static float GetRandomValueInRange(Vector2 range1, Vector2 range2) {
			int result1,result2;

			result1 = GetRandomValue(range1.x, range1.y);
			result2 = GetRandomValue(range2.x, range2.y);

			if (GetRandomValue(0, 1)) {
				return result1;
			}
			else {
				return result2;
			}
		}

		static void initMeteor() {
			//Textures
			bigMeteorTex = LoadTexture("res/Textures/BIG_METEOR.png");
			mediumMeteorTex = LoadTexture("res/Textures/MEDIUM_METEOR.png");
			smallMeteorTex = LoadTexture("res/Textures/SMALL_METEOR.png");

			//Big Meteors
			for (int i = 0; i < MAX_BIG_METEORS; i++) {

				//Start Getting Random Values to spawn
				//X
				range1 = { (float)0, (float)((GetScreenWidth() / 2) - safeZone) };
				range2 = { (float)((GetScreenWidth() / 2) + safeZone),(float)GetScreenWidth() };

				posx = GetRandomValueInRange(range1, range2);

				//Y
				range1 = { (float)0, (float)((GetScreenHeight() / 2 )-safeZone)};
				range2 = { (float)((GetScreenHeight() / 2) + safeZone), (float)GetScreenHeight() };

				posy = GetRandomValueInRange(range1, range2);
				//End Spawn Values

				bigMeteor[i].position = { (float)posx,(float)posy };

				velx = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);
				vely = GetRandomValue(-METEORS_SPEED, METEORS_SPEED);

				if (velx == 0) {
					velx = METEORS_SPEED / 2;
				}
				if (vely == 0) {
					vely = METEORS_SPEED / 2;
				}

				bigMeteor[i].speed = { (float)velx, (float)vely };
				bigMeteor[i].radius = bigMeteorTex.width / 2;
				bigMeteor[i].active = true;
				bigMeteor[i].color = WHITE;

				// NOTE: Source rectangle (part of the texture to use for drawing)
				bigMeteor[i].sourceRec = {
					0.0f,
					0.0f,
					(float)bigMeteorTex.width,
					(float)bigMeteorTex.height
				};

				// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
				bigMeteor[i].destRec = {
					bigMeteor[i].position.x,
					bigMeteor[i].position.y,
					(float)bigMeteorTex.width,
					(float)bigMeteorTex.height
				};

				// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
				bigMeteor[i].origin = {
					(float)bigMeteorTex.width / 2,
					(float)bigMeteorTex.height / 2
				};
			}

			//Medium Meteors
			for (int i = 0; i < MAX_MEDIUM_METEORS; i++) {

				mediumMeteor[i].position = { -100, -100 };
				mediumMeteor[i].speed = { 0, 0 };
				mediumMeteor[i].radius = mediumMeteorTex.width / 2;
				mediumMeteor[i].active = false;
				mediumMeteor[i].color = WHITE;

				// NOTE: Source rectangle (part of the texture to use for drawing)
				mediumMeteor[i].sourceRec = {
					0.0f,
					0.0f,
					(float)mediumMeteorTex.width,
					(float)mediumMeteorTex.height
				};

				// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
				mediumMeteor[i].destRec = {
					mediumMeteor[i].position.x,
					mediumMeteor[i].position.y,
					(float)mediumMeteorTex.width,
					(float)mediumMeteorTex.height
				};

				// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
				mediumMeteor[i].origin = {
					(float)mediumMeteorTex.width / 2,
					(float)mediumMeteorTex.height / 2
				};
			}

			//Small Meteors
			for (int i = 0; i < MAX_SMALL_METEORS; i++) {

				smallMeteor[i].position = { -100, -100 };
				smallMeteor[i].speed = { 0, 0 };
				smallMeteor[i].radius = smallMeteorTex.width / 2;
				smallMeteor[i].active = false;
				smallMeteor[i].color = WHITE;

				// NOTE: Source rectangle (part of the texture to use for drawing)
				smallMeteor[i].sourceRec = {
					0.0f,
					0.0f,
					(float)smallMeteorTex.width,
					(float)smallMeteorTex.height
				};

				// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
				smallMeteor[i].destRec = {
					smallMeteor[i].position.x,
					smallMeteor[i].position.y,
					(float)smallMeteorTex.width,
					(float)smallMeteorTex.height
				};

				// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
				smallMeteor[i].origin = {
					(float)smallMeteorTex.width / 2,
					(float)smallMeteorTex.height / 2
				};
			}

		}

		static void updateMeteor() {
			// Meteors logic: big meteors
			for (int i = 0; i < MAX_BIG_METEORS; i++) {
				if (bigMeteor[i].active) {
					//Rotation
					bigMeteor[i].rotation += METEOR_ROTATION_SPEED * GetFrameTime();

					// Movement
					bigMeteor[i].position.x += bigMeteor[i].speed.x * GetFrameTime();
					bigMeteor[i].position.y += bigMeteor[i].speed.y * GetFrameTime();

					// Collision logic: meteor vs wall
					if (bigMeteor[i].position.x > GetScreenWidth() + bigMeteor[i].radius) {
						bigMeteor[i].position.x = -(bigMeteor[i].radius);
					}
					else if (bigMeteor[i].position.x < 0 - bigMeteor[i].radius) {
						bigMeteor[i].position.x = GetScreenWidth() + bigMeteor[i].radius;
					}
					if (bigMeteor[i].position.y > GetScreenHeight() + bigMeteor[i].radius) {
						bigMeteor[i].position.y = -(bigMeteor[i].radius);
					}
					else if (bigMeteor[i].position.y < 0 - bigMeteor[i].radius) {
						bigMeteor[i].position.y = GetScreenHeight() + bigMeteor[i].radius;
					}
				}

				bigMeteor[i].destRec = {
					bigMeteor[i].position.x,
					bigMeteor[i].position.y,
					(float)bigMeteorTex.width,
					(float)bigMeteorTex.height
				};

			}

			// Meteors logic: medium meteors
			for (int i = 0; i < MAX_MEDIUM_METEORS; i++) {
				if (mediumMeteor[i].active) {
					//Rotation
					mediumMeteor[i].rotation += METEOR_ROTATION_SPEED * GetFrameTime();

					// Movement
					mediumMeteor[i].position.x += mediumMeteor[i].speed.x * GetFrameTime();
					mediumMeteor[i].position.y += mediumMeteor[i].speed.y * GetFrameTime();

					// Collision logic: meteor vs wall
					if (mediumMeteor[i].position.x > GetScreenWidth() + mediumMeteor[i].radius) {
						mediumMeteor[i].position.x = -(mediumMeteor[i].radius);
					}
					else if (mediumMeteor[i].position.x < 0 - mediumMeteor[i].radius) {
						mediumMeteor[i].position.x = GetScreenWidth() + mediumMeteor[i].radius;
					}
					if (mediumMeteor[i].position.y > GetScreenHeight() + mediumMeteor[i].radius) {
						mediumMeteor[i].position.y = -(mediumMeteor[i].radius);
					}
					else if (mediumMeteor[i].position.y < 0 - mediumMeteor[i].radius) {
						mediumMeteor[i].position.y = GetScreenHeight() + mediumMeteor[i].radius;
					}
				}

				mediumMeteor[i].destRec = {
					mediumMeteor[i].position.x,
					mediumMeteor[i].position.y,
					(float)mediumMeteorTex.width,
					(float)mediumMeteorTex.height
				};

			}

			// Meteors logic: small meteors
			for (int i = 0; i < MAX_SMALL_METEORS; i++) {
				if (smallMeteor[i].active) {
					//Rotation
					smallMeteor[i].rotation += METEOR_ROTATION_SPEED * GetFrameTime();

					// Movement
					smallMeteor[i].position.x += smallMeteor[i].speed.x * GetFrameTime();
					smallMeteor[i].position.y += smallMeteor[i].speed.y * GetFrameTime();

					// Collision logic: meteor vs wall
					if (smallMeteor[i].position.x > GetScreenWidth() + smallMeteor[i].radius) {
						smallMeteor[i].position.x = -(smallMeteor[i].radius);
					}
					else if (smallMeteor[i].position.x < 0 - smallMeteor[i].radius) {
						smallMeteor[i].position.x = GetScreenWidth() + smallMeteor[i].radius;
					}
					if (smallMeteor[i].position.y > GetScreenHeight() + smallMeteor[i].radius) {
						smallMeteor[i].position.y = -(smallMeteor[i].radius);
					}
					else if (smallMeteor[i].position.y < 0 - smallMeteor[i].radius) {
						smallMeteor[i].position.y = GetScreenHeight() + smallMeteor[i].radius;
					}
				}

				smallMeteor[i].destRec = {
					smallMeteor[i].position.x,
					smallMeteor[i].position.y,
					(float)smallMeteorTex.width,
					(float)smallMeteorTex.height
				};

			}

			// Collision logic: player-shoots vs meteors
			for (int i = 0; i < PLAYER_MAX_SHOOTS; i++) {
				if ((shoot[i].active)) {
					for (int a = 0; a < MAX_BIG_METEORS; a++) {
						if (bigMeteor[a].active &&
							CheckCollisionCircles(
								shoot[i].position,
								shoot[i].radius,
								bigMeteor[a].position,
								bigMeteor[a].radius)) {

							shoot[i].active = false;
							shoot[i].lifeSpawn = 0;
							bigMeteor[a].active = false;
							destroyedMeteorsCount++;

							for (int j = 0; j < 2; j++) {
								if (midMeteorsCount % 2 == 0) {

									mediumMeteor[midMeteorsCount].position = {
										bigMeteor[a].position.x,
										bigMeteor[a].position.y
									};

									mediumMeteor[midMeteorsCount].speed = {
									  (float)(cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1),
									  (float)(sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1)
									};

								}
								else {
									mediumMeteor[midMeteorsCount].position = {
										bigMeteor[a].position.x,
										bigMeteor[a].position.y
									};

									mediumMeteor[midMeteorsCount].speed = {
									  (float)(cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED),
									  (float)(sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED)
									};

								}

								mediumMeteor[midMeteorsCount].active = true;
								midMeteorsCount++;
							}
							bigMeteor[a].color = RED;
							a = MAX_BIG_METEORS;
						}
					}

					for (int b = 0; b < MAX_MEDIUM_METEORS; b++) {

						if (mediumMeteor[b].active &&
							CheckCollisionCircles(
								shoot[i].position,
								shoot[i].radius,
								mediumMeteor[b].position,
								mediumMeteor[b].radius)) {

							shoot[i].active = false;
							shoot[i].lifeSpawn = 0;
							mediumMeteor[b].active = false;
							destroyedMeteorsCount++;

							for (int j = 0; j < 2; j++) {
								if (smallMeteorsCount % 2 == 0) {

									smallMeteor[smallMeteorsCount].position = {
										mediumMeteor[b].position.x,
										mediumMeteor[b].position.y
									};

									smallMeteor[smallMeteorsCount].speed = {
									  (float)(cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1),
									  (float)(sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED*-1)
									};

								}
								else {

									smallMeteor[smallMeteorsCount].position = {
										mediumMeteor[b].position.x,
										mediumMeteor[b].position.y
									};

									smallMeteor[smallMeteorsCount].speed = {
									  (float)(cos(shoot[i].rotation*DEG2RAD)*METEORS_SPEED),
									  (float)(sin(shoot[i].rotation*DEG2RAD)*METEORS_SPEED)
									};

								}

								smallMeteor[smallMeteorsCount].active = true;
								smallMeteorsCount++;
							}
							mediumMeteor[b].color = GREEN;
							b = MAX_MEDIUM_METEORS;
						}
					}

					for (int c = 0; c < MAX_SMALL_METEORS; c++) {

						if (smallMeteor[c].active &&
							CheckCollisionCircles(
								shoot[i].position,
								shoot[i].radius,
								smallMeteor[c].position,
								smallMeteor[c].radius)) {

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
			if (destroyedMeteorsCount == 15) {
				victory = true;
			}
		}

		static void drawMeteor() {
			for (int i = 0; i < MAX_BIG_METEORS; i++) {

				if (bigMeteor[i].active) {
					DrawTexturePro(
						bigMeteorTex,
						bigMeteor[i].sourceRec,
						bigMeteor[i].destRec,
						bigMeteor[i].origin,
						bigMeteor[i].rotation,
						WHITE);
				}

			}

			for (int i = 0; i < MAX_MEDIUM_METEORS; i++) {

				if (mediumMeteor[i].active) {
					DrawTexturePro(
						mediumMeteorTex,
						mediumMeteor[i].sourceRec,
						mediumMeteor[i].destRec,
						mediumMeteor[i].origin,
						mediumMeteor[i].rotation,
						WHITE);
				}

			}

			for (int i = 0; i < MAX_SMALL_METEORS; i++) {

				if (smallMeteor[i].active) {
					DrawTexturePro(
						smallMeteorTex,
						smallMeteor[i].sourceRec,
						smallMeteor[i].destRec,
						smallMeteor[i].origin,
						smallMeteor[i].rotation,
						WHITE);
				}

			}
		}

		void init() {

			safeZone = 250;
			victory = false;
			pause = false;
			destroyedMeteorsCount = 0;

			initMeteor();
			
			midMeteorsCount = 0;
			smallMeteorsCount = 0;
		}

		void update() {	
			updateMeteor();
		}


		void draw() {
			drawMeteor();
		}

		void deInit() {
				UnloadTexture(bigMeteorTex);
				UnloadTexture(mediumMeteorTex);
				UnloadTexture(smallMeteorTex);
		}

		
	}
}
