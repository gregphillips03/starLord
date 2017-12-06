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
#include <iostream>
#include "crate.h"

#define MAXDEPTH -1120

/**
	Constructor for objects of class Crate
*/
Crate::Crate()
{
	for (int i = 0; i < 2; i++)
	{
		switch (i)
		{
		case 0:	image[i] = al_load_bitmap("crate.png");
			break;
		case 1: image[i] = al_load_bitmap("portal_spark.png");
			break;
		}
	}
	boundx = al_get_bitmap_width(image[0]);
	boundy = al_get_bitmap_height(image[0]);
	speed = rand() & 5 + 3;
	live = false;
	destroy = false;
	maxFrame = 16;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 7;
	frameWidth = 182;
	frameHeight = 206;
	animationColumns = 4;
	supplyCrateRelease = NULL;
	supplyCrateRelease = al_load_sample("supplycrate.wav");
	if (!supplyCrateRelease)
	{
		exit(9);
	}
	type = assignType();
	std::cout << "Assign this crate as: " << type << ".\n";
}
/**
	Deconstructor for objects of class Crate
*/
Crate::~Crate()
{
	for (int i = 0; i < 2; i++)
	{
		al_destroy_bitmap(image[i]);
	}
}
/**
	Draws the crates on the screen
	@param width	integer containing width of display
	@param height	integer containing height of display
*/
void Crate::drawCrate(int width, int height)
{
	if (live && !destroy) //if not destroyed, draw normal
	{
		al_draw_bitmap(image[0], x, y, 0);
	}
	else if (!live && destroy) //if destroyed, turn into a destroyed icon
	{
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = (curFrame / animationColumns) * frameHeight;
		al_draw_bitmap_region(image[1], fx, fy, frameWidth, frameHeight, x, y, 0);
	}
}
/**
	Places the crates on the display
	@param width	integer containing width of display
	@param height	integer containing height of display
*/
void Crate::startCrate(int width, int height)
{
	if (!live && !destroy) //if is not alive and is not destroyed
	{
		if (rand() % 10000 == 0)
		{
			live = true;
			x = rand() % (width - boundx); //generate random x location on display
			y = MAXDEPTH - boundy; 
			al_play_sample(supplyCrateRelease, 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	}
}
/**
	Updates the position of the crates on the display
	@param height	height of the display
*/
void Crate::updateCrate(int height)
{
	if (live) //if crate is live
	{
		y += speed; //increment via speed
	}
	else if (!live && destroy) //if isn't alive but is destroyed
	{
		y += 1; //slow down the movement
		if (++frameCount >= frameDelay)
		{
			curFrame += 1;
			if (curFrame >= maxFrame)
			{
				y = height;
				curFrame = 0;
			}
			frameCount = 0;
		}
	}
}
/**
	Detects collision between the crates and the bottom of screen
	@param height	integer containing height of display
*/
void Crate::collideCrate(int height)
{
	if (y > height && live && !destroy) // if its alive and not destroyed
	{
		live = false;
		curFrame = 0;
		frameCount = 0;
	}
	else if (y > height && !live && destroy) //if its not alive and is destroyed
	{
		destroy = false;
		curFrame = 0;
		frameCount = 0;
	}
}
/**
	Assigns a type to a crate for special effects
	@return		integer representation of the crate's type
*/
int Crate::assignType()
{
	int i = rand() % 10;
	int j = 0; 

	switch (i)
	{
	case 0: case 1: case 2: case 3: j = 0; //points
		break;
	case 4: case 5: case 6:	j = 1; //health
		break;
	case 7: case 8: j = 2; //repair
		break;
	case 9: j = 3;//full health
		break;
	}
	return j;
}