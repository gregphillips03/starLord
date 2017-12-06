/**
	William (Greg) Phillips
	Star Lord
*/

#ifndef CRATEH
#define CRATEH
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

class Crate
{
public:
	Crate(); 
	~Crate();
	void drawCrate(int width, int height);
	void startCrate(int width, int height);
	void updateCrate(int height);
	void collideCrate(int height);
	int getBoundX(){ return boundx; }
	int getBoundY(){ return boundy; }
	int assignType(); 
	void setLive(bool b){ live = b; }
	void setDestroy(bool b){ destroy = b; }
	int getX(){ return x; }
	int getY(){ return y; }
	int getType(){ return type;  }
	bool getLive(){ return live; }
	bool getDestroy(){ return destroy; }
private:
	int x;
	int y;
	int type; 
	int boundx;
	int boundy;
	int speed;
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
	ALLEGRO_BITMAP *image[2];
	ALLEGRO_SAMPLE *supplyCrateRelease;
};

#endif