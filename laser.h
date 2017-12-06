/**
	William (Greg) Phillips
	Star Lord
*/

#ifndef LASERH
#define LASERH
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "weapon.h"
#include "enemy.h"
#include "friend.h"
#include "crate.h"
#include "asteroid.h"
#include "gameState.h"

#define pi 3.14159265359

class Laser
{
public:
	Laser(); 
	~Laser(); 
	void drawLaser(Weapon &weapon); 
	bool fireLaser(int width, int height, Weapon &weapon);
	void updateLaser(Weapon &weapon, int width);
	void collideLaserCrate(Crate crate[], int numCrate, Weapon &weapon, GameState &gs); 
	int collideLaser(Enemy enemy[], int numEnemy, Weapon &weapon);
	int collideLaserFriend(Friend friendly[], int numFriend, Weapon &weapon);
	void collideLaserAsteroid(Asteroid asteroid[], int numAsteroid, Weapon &weapon);
private:
	int x; 
	int y; 
	int boundx; 
	int boundy; 
	bool live; 
	int speed; 
	float radian_angle; 
	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *sample;
	ALLEGRO_SAMPLE *destruct; 
	ALLEGRO_SAMPLE *checkFire; 
	ALLEGRO_SAMPLE *crateBreak; 
	ALLEGRO_SAMPLE *thud; 
};

#endif