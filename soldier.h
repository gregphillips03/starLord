/**
	William (Greg) Phillips
	Star Lord
*/

#ifndef SOLDIERH
#define SOLDIERH
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

class Soldier
{
public:
	Soldier(); 
	~Soldier(); 
	void drawSoldier(int width, int height, float camera); 
private:
	int maxframe; 
	int curframe; 
	int frameCount; 
	int frameDelay; 
	ALLEGRO_BITMAP *image[36];
};

#endif