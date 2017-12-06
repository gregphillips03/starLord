/**
	William (Greg) Phillips
	Star Lord
*/

/**
	The special class controls special objects that give the end user assitance during the game.
	The objects are "contained" in crates. When the crates are destroyed, the special object is
	then released onto the screen, depending on its type. The types are:

	0 = coin, adds to the player's score 
	1 = health, adds to the player's health x100
	2 = repair, removes one hull damage 
	3 = healthpack, fully restores the player's health
*/

#ifndef SPECIALH
#define SPECIALH
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "crate.h"

class Special
{
public:
	Special(); 
	~Special(); 
	void drawSpecial(int width, int height, int type); 
	void updateSpecial(int height, int type);
	void startSpecial(int width, int height, Crate crate[], int c, int type); 
	bool getLive(){ return live; }

private:
	int x;
	int y;
	int speed;
	bool live;
	float angle; 

	int maxFrame_c;
	int curFrame_c;
	int frameCount_c;
	int frameDelay_c;
	int frameWidth_c;
	int frameHeight_c;
	int animationColumns_c;
	int animationRows_c;

	int maxFrame_h;
	int curFrame_h;
	int frameCount_h;
	int frameDelay_h;
	int frameWidth_h;
	int frameHeight_h;
	int animationColumns_h;
	int animationRows_h;

	ALLEGRO_BITMAP *coin;
	ALLEGRO_BITMAP *health;
	ALLEGRO_BITMAP *repair; 
	ALLEGRO_BITMAP *healthpack; 

	ALLEGRO_SAMPLE *coindrop;
	ALLEGRO_SAMPLE *heart; 
	ALLEGRO_SAMPLE *wrench; 
	ALLEGRO_SAMPLE *powerup; 
};

#endif