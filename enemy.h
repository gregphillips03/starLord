/**
	William (Greg) Phillips
	Star Lord
*/

#ifndef ENEMYH
#define ENEMYH
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

class Enemy
{
public:
	Enemy(); 
	~Enemy(); 
	void drawEnemy(int width, int height); 
	void startEnemy(int width, int height); 
	void updateEnemy(int height); 
	int collideEnemy(int height, int width, int hits); 
	void setLive(bool b){live = b;}
	void setDestroy(bool b){ destroy = b; }
	void setSpeed(int i);
	void setSpeedFlat(){ speed = 1; }
	int getBoundX(){ return boundx; }
	int getBoundY(){ return boundy; }
	int getX(){ return x; }
	int getY(){ return y;  }
	bool getLive(){ return live;  }
private:
	int x; 
	int y; 
	int boundx; 
	int boundy;
	int speed; 
	int thisShip; 

	int maxFrame; 
	int curFrame; 
	int frameCount; 
	int frameDelay; 
	int frameWidth; 
	int frameHeight; 
	int animationColumns; 
	int animationRows; 

	bool live; 
	bool destroy; 
	ALLEGRO_BITMAP *image[6]; 
};

#endif