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
#include "asteroid.h"

#define MAXDEPTH -1120
/**
	Constructor for objects of class Asteroid
*/
Asteroid::Asteroid()
{
	hp = 10; 
	speed = rand() % 2 + 1;
	live = false; 
	destroy = false; 
	contact = false; 

	image = al_load_bitmap("asteroid.png");
	frameWidth = 128; 
	boundx = frameWidth; 
	frameHeight = 128;
	boundy = frameHeight; 
	animationColumns = 8; 
	animationRows = 8; 
	maxFrame = 64;
	curFrame = 0; 
	frameCount = 0; 
	frameDelay = 5; 

	destroyed = al_load_bitmap("smoke.png"); 
	frameWidth_d = 256;
	frameHeight_d = 256;
	animationColumns_d = 7;
	animationRows_d = 7;
	maxFrame_d = 46;
	curFrame_d = 0;
	frameCount_d = 0;
	frameDelay_d = 5;

	shatter = NULL; 
	shatter = al_load_sample("shatter.wav"); 
	if (!shatter)
	{
		exit(9); 
	}
}
/**
	Destructor for objets of class Asteroid
*/
Asteroid::~Asteroid()
{
	al_destroy_bitmap(image);
	al_destroy_bitmap(destroyed); 
}
/**
	Draws the asteroid on the screen
	@param width	integer containing width of display
	@param height	integer containing height of display
*/
void Asteroid::drawAsteroid(int width, int height)
{
	if (live && !destroy && contact)
	{
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = (curFrame / animationColumns) * frameHeight;
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		al_draw_tinted_bitmap_region(image, al_map_rgba_f(r, g, b, 1), fx, fy, frameWidth, frameHeight, x, y, 0);
		contact = false;
	}
	else if (live && !destroy) //if not destroyed, draw normal
	{
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = (curFrame / animationColumns) * frameHeight;
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x, y, 0);
	}
	else if (!live && destroy) //if destroyed, turn into a destroyed version
	{
		int fx = (curFrame_d % animationColumns_d) * frameWidth_d;
		int fy = (curFrame_d / animationColumns_d) * frameHeight_d;
		al_draw_bitmap_region(destroyed, fx, fy, frameWidth_d, frameHeight_d, x, y, 0);
	}
}
/**
	Places the asteroid on the display
	@param width	integer containing width of display
	@param height	integer containing height of display
*/
void Asteroid::startAsteroid(int width, int height)
{
	if (!live && !destroy) //if is not alive and is not destroyed
	{
		if (rand() % 500 == 0)
		{
			live = true;
			hp = 10; 
			x = rand() % (width - boundx); //generate random x location on display
			y = MAXDEPTH - boundy;
		}
	}
}
/**
	Updates the position of the asteroid on the display
	@param height	height of the display
*/
void Asteroid::updateAsteroid(int height)
{
	if (live) //if asteroid is live
	{
		y += speed; //increment via speed
		if (++frameCount >= frameDelay)
		{
			curFrame += 1;
			if (curFrame >= maxFrame)
			{
				curFrame = 0;
			}
			frameCount = 0;
		}
	}
	else if (!live && destroy) //if isn't alive but is destroyed
	{
		y += speed;
		if (++frameCount_d >= frameDelay_d)
		{
			curFrame_d += 1;
			if (curFrame_d >= maxFrame_d) //finish playing out the smoke sequence animation
			{
				y = height; //drop down object to the screen bottom to recycle it
				curFrame_d = 0; //set the frame animation for the smoke sequence back to zero
			}
			frameCount_d = 0;
		}
	}
}
/**
	Detects collision between the asteroids and the bottom of screen
	@param height	integer containing height of display
*/
void Asteroid::collideAsteroid(int height, GameState &gs)
{
	if (y > height && live && !destroy) // if its alive and not destroyed
	{
		live = false;
		curFrame = 0;
		frameCount = 0;
		gs.setHits(1); 
	}
	else if (y > height && !live && destroy) //if its not alive and is destroyed
	{
		destroy = false;
		curFrame_d = 0;
		frameCount_d = 0;
	}
}
/**
	Sets the asteroids HP after a successful laser hit
	@param i	integer containg amount to subtract from asteroids HP
*/
void Asteroid::setHP(int i)
{
	hp -= i; 
	if (hp <= 0)
	{
		destroy = true; 
		live = false; 
		al_play_sample(shatter, 1.5, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}
/**
	Sets the asteroids speed
	@param i		integer containing the amount of speed to add to asteroid movement
*/
void Asteroid::setSpeed(int i)
{
	speed += i;
	if (speed < 1)
	{
		speed = 1;
	}
}