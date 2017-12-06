/**
	William (Greg) Phillips
	Star Lord
*/

#ifndef HULLH
#define HULLH
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

class Hull
{
public:
	Hull(); 
	~Hull(); 
	void drawHull(int hits, int width, int height); 
private:
	ALLEGRO_BITMAP *image[20]; 
};

#endif