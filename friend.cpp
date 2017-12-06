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
#include "friend.h"
#include <iostream>

#define MAXDEPTH -1120

/**
	Constructor for objects of class Friend
	Randomly assigns one of two ship images as the enemy ship's image
*/
Friend::Friend()
{
	for (int i = 0; i < 2; i++)
	{
		switch (i)
		{
		case 0:	image[i] = al_load_bitmap("./img/friend1.png");
			break;
		case 1: image[i] = al_load_bitmap("./img/explosionsheet.png"); 
			break; 
		}
		boundx = al_get_bitmap_width(image[0]);
		boundy = al_get_bitmap_height(image[0]);
		speed = rand() & 5 + 3;
		live = false;
		destroy = false;
		thisShip = static_cast <int> (rand()) % 1;
		maxFrame = 74;
		curFrame = 0;
		frameCount = 0;
		frameDelay = 5;
		frameWidth = 100;
		frameHeight = 100;
		animationColumns = 9;
		//std::cout << "Friendly ship built is " << thisShip << ".\n"; 
	}
}
/**
	Deconstructor for objects of class Friend
*/
Friend::~Friend()
{
	for (int i = 0; i < 2; i++)
	{
		al_destroy_bitmap(image[i]);
	}
}
/**
	Draws the friendly ships on the screen
	@param width	integer containing width of display
	@param height	integer containing height of display
*/
void Friend::drawFriend(int width, int height)
{
	if (live && !destroy) //if not destroyed, draw normal
	{
		al_draw_bitmap(image[thisShip], x, y, 0);
	}
	else if (!live && destroy) //if destroyed, turn into a destroyed icon
	{
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = (curFrame / animationColumns) * frameHeight;
		al_draw_bitmap_region(image[1], fx, fy, frameWidth, frameHeight, x, y, 0);
	}
}
/**
	Places the friendly ships on the display
	@param width	integer containing width of display
	@param height	integer containing height of display
*/
void Friend::startFriend(int width, int height)
{
	if (!live && !destroy) //if is not alive and is not destroyed
	{
		if (rand() % 300 == 0)
		{
			live = true;
			x = rand() % (width - boundx); //generate random x location on display
			y = MAXDEPTH - boundy; 
		}
	}
}
/**
	Updates the position of the friendly ships on the display
*/
void Friend::updateFriend(int height)
{
	if (live) //if ship is live
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
	Detects collision between the friendly ships and the bottom of screen
	@param height	integer containing height of display
	@return			1 for a hit, 0 for none
*/
int Friend::collideFriend(int height)
{
	if (y > height && live && !destroy) // if its alive and not destroyed, score a save
	{
		live = false;
		curFrame = 0; 
		frameCount = 0; 
		return 1;
	}
	else if (y > height && !live && destroy) //if its not alive and is destroyed, dont score a save
	{
		destroy = false;
		curFrame = 0;
		frameCount = 0;
		return 0;
	}
	else
	{
		return 0;
	}
}
