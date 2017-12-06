/**
	William (Greg) Phillips
	Star Lord
*/

/**
	The asteroid class controls the movement and placement of asteroids on the display. Asteroids damage the end 
	user's fighter as well as the ship hull. Asteroids have HP, and thus aren't destroyed on a single hit. 
*/

#ifndef ASTEROIDH
#define ASTEROIDH
#include "gameState.h"
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

class Asteroid
{
public:
	Asteroid(); 
	~Asteroid(); 
	void drawAsteroid(int width, int height);
	void startAsteroid(int width, int height);
	void updateAsteroid(int height);
	void collideAsteroid(int height, GameState &gs); 
	int getBoundX(){ return boundx; }
	int getBoundY(){ return boundy; }
	void setLive(bool b){ live = b; }
	void setDestroy(bool b){ destroy = b; }
	void setHP(int i); 
	void setSpeed(int i); 
	void setContact(bool b){ contact = b; }
	int getX(){ return x; }
	int getY(){ return y; }
	int getHP(){ return hp; }
	bool getLive(){ return live; }
private:
	int x; 
	int y; 
	int hp;
	int speed;

	int boundx;
	int boundy;

	int maxFrame;
	int maxFrame_d; 
	int curFrame;
	int curFrame_d; 

	int frameCount;
	int frameCount_d; 
	int frameDelay;
	int frameDelay_d; 

	int frameWidth;
	int frameWidth_d; 
	int frameHeight;
	int frameHeight_d;
	int animationColumns;
	int animationColumns_d; 
	int animationRows;
	int animationRows_d; 
	
	bool live;
	bool destroy;
	bool contact; 

	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *destroyed; 
	ALLEGRO_SAMPLE *shatter; 
};
#endif