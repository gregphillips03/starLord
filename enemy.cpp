/**
	William (Greg) Phillips
	Star Lord
*/

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "enemy.h"
#include <iostream>

#define MAXDEPTH -1120
/**
	Constructor for objects of the class Enemy
	Randomly assigns one of four ship images as the enemy ship's image
*/
Enemy::Enemy()
{
	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0:	image[i] = al_load_bitmap("enemy0.png"); 
			break; 
		case 1:	image[i] = al_load_bitmap("enemy1.png");
			break;
		case 2:	image[i] = al_load_bitmap("enemy2.png");
			break;
		case 3:	image[i] = al_load_bitmap("enemy3.png");
			break;
		case 4: image[i] = al_load_bitmap("explodesheet.png"); 
			break; 
		}
		boundx = al_get_bitmap_width(image[0]);
		boundy = al_get_bitmap_height(image[0]);
		speed = rand() % 5 + 1; 
		live = false; 
		destroy = false; 
		thisShip = static_cast <int> (rand()) % 4; //number between 0 and 3
		maxFrame = 32; 
		curFrame = 0; 
		frameCount = 0; 
		frameDelay = 5; 
		frameWidth = 256; 
		frameHeight = 256; 
		animationColumns = 8; 
		//std::cout << "Enemy ship built is " << thisShip << ".\n";
	}
}
/**
Destructor for objects of class Enemy
*/
Enemy::~Enemy()
{
	for (int i = 0; i < 5; i++)
	{
		al_destroy_bitmap(image[i]); 
	}
}
/**
	Draws the enemy ships on the screen
	@param width	integer containing width of display
	@param height	integer containing height of display
*/
void Enemy::drawEnemy(int width, int height)
{
	if (live && !destroy) //if not destroyed, draw normal
	{
		al_draw_bitmap(image[thisShip], x, y, 0);
	}
	else if (!live && destroy) //if destroyed, turn into a destroyed icon
	{
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = (curFrame / animationColumns) * frameHeight;
		al_draw_bitmap_region(image[4], fx, fy, frameWidth, frameHeight, x, y, 0);
	}
}
/**
	Places the enemy ships on the display
	@param width	integer containing width of display
	@param height	integer containing height of display
*/
void Enemy::startEnemy(int width, int height)
{
	if (!live && !destroy) //if is not alive and is not destroyed
	{
		if (rand() % 200 == 0)
		{
			live = true; 
			x = rand() % (width - boundx); //generate random x location on display
			y = MAXDEPTH - boundy; //come in from off the screen
		}
	}
}
/**
	Updates the position of the enemy ships on the display
	@param height	integer containing screen height
*/
void Enemy::updateEnemy(int height)
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
	Detects collision between the enemy ships and the ship hull
	@param height	integer containing height of display
	@param width	integer containing width of display
	@param hits		integer containing number of hits on the hull
	@return			1 for a hit, 0 for none
*/
int Enemy::collideEnemy(int height, int width, int hits)
{
	if (y > height-270 && live && !destroy && hits < 19) // if its alive and not destroyed, score a hit
	{
		live = false; 
		curFrame = 0; //this fixes the bug where explosions don't get to finish
		frameCount = 0; 
		return 1; 
	}
	else if (y > height - 270 && live && !destroy && hits == 19 && x > width / 2)//when the hull is down to one damage
	{
		live = false;
		curFrame = 0; //this fixes the bug where explosions don't get to finish
		frameCount = 0;
		return 1;
	}
	else if (y > height - 270 && live && !destroy && hits == 19 && x < width / 2)
	{
		live = false; 
		curFrame = 0; 
		frameCount = 0; 
		return 0; 
	}
	else if (y > height -270 && !live && destroy) //if its not alive and is destroyed, dont score a hit
	{
		destroy = false; 
		curFrame = 0; //this fixes the bug where explosions don't get to finish
		frameCount = 0;
		return 0; 
	}
	else
	{
		return 0; 
	}
}
/**
	Increments the enemy's speed / used to make the levels more difficult
*/
void Enemy::setSpeed(int i)
{
	speed += i; 
	if (speed < 1)
	{
		speed = 1; 
	}
}
