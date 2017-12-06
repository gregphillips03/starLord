/**
	William (Greg) Phillips
	Star Lord
*/

#ifndef FRIENDH
#define FRIENDH
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

class Friend
{
public:
	Friend(); 
	~Friend(); 
	void drawFriend(int width, int height);
	void startFriend(int width, int height);
	void updateFriend(int height); 
	void setLive(bool b){ live = b; }
	void setDestroy(bool b){ destroy = b; }
	int getBoundX(){ return boundx; }
	int getBoundY(){ return boundy; }
	int collideFriend(int height); 
	int getX(){ return x; }
	int getY(){ return y; }
	bool getLive(){ return live; }
private:
	int x;
	int y;
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

	int thisShip; 
	bool live;
	bool destroy;
	ALLEGRO_BITMAP *image[2];
};

#endif