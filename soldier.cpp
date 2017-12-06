/**
	William (Greg) Phillips
	Star Lord
*/

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <stdio.h>
#include "soldier.h"

#define MAXDEPTH -1120
/**
	Constructor for objects of class Soldier
*/
Soldier::Soldier()
{
	maxframe = 36; 
	curframe = 0; 
	frameCount = 0; 
	frameDelay = 2; 
	char s[80]; 
	for (int i = 0; i < maxframe; i++)
	{
		sprintf_s(s, "sol-%d.png", i);
		image[i] = al_load_bitmap(s);
	}
}
/**
	Deconstrutor for objects of class Soldier
*/
Soldier::~Soldier()
{
	for (int i = 0; i < maxframe; i++)
	{
		al_destroy_bitmap(image[i]); 
	}
}
/**
	Draws the soldier onto the screen
	@param width	integer containing display width in pixels
	@param height	integer containing display height in pixels
	@param camera	float containing the camera position on the display
*/
void Soldier::drawSoldier(int width, int height, float camera)
{
	al_draw_tinted_bitmap(image[curframe], al_map_rgb(0, 255, 165), 20, 580 + camera, 0); 
	if (++frameCount >= frameDelay)
	{
		frameCount = 0; 
		if (++curframe >= maxframe)
		{
			curframe = 0;
		}
	}

}