/**
	William (Greg) Phillips
	Star Lord
*/

#ifndef WEAPONH

#include "asteroid.h"
#include "gameState.h"
#define WEAPONH

class Weapon
{
public:
	Weapon(int width, int height);
	~Weapon(); 
	void drawWeapon(int width, int height); 
	void rotateLeft(); 
	void rotateRight(); 
	void moveLeft(); 
	void moveRight(int width);
	void moveForward(); 
	void moveBackward(int height); 
	void collideWithAsteroid(Asteroid asteroid[], int numAsteroid, GameState &gs);
	float getAngle(){ return angle; }
	int getBoundX(){ return boundx; }
	int getBoundY(){ return boundy; }
	int getX(){ return x;  }
	int getY(){ return y;  }
private:
	int x; 
	int y; 
	int speed; 
	int boundx; 
	int boundy; 
	float angle; 
	ALLEGRO_BITMAP *image; 
};
#endif