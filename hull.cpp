/**
	William (Greg) Phillips
	Star Lord
*/

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "hull.h"
#include <stdio.h>

/**
	Constructor for objects of class Hull
*/
Hull::Hull()
{
	char s[80];
	for (int i = 0; i < 20; i++)
	{
		sprintf_s(s, "hull%d.png", i);
		image[i] = al_load_bitmap(s);
		al_convert_mask_to_alpha(image[i], al_map_rgb(255, 255, 255));
	}
}
/**
	Destructor for objects of class Hull
*/
Hull::~Hull()
{
	for (int i = 0; i < 20; i++)
	{
		al_destroy_bitmap(image[i]); 
	}
}
/**
	Draws the hull image on the display
	@param hits		integer containing the number of times the hull has been hit
	@param width	integer containing the screen width in pixels
	@param height	integer containing the screen height in pixels
*/
void Hull::drawHull(int hits, int width, int height)
{
	if (hits < 20)
	{
		al_draw_bitmap(image[hits], 0, height-200, 0);
	}
	else
	{
		al_draw_bitmap(image[19], 0, height-200, 0); 
	}
}

