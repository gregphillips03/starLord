/**
	William (Greg) Phillips
	Star Lord
*/

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "laser.h"
#include "special.h"
#include "math.h"

#define MAXDEPTH -1120

/**
	Constructor for objects of class Special
*/
Special::Special()
{
	coin = al_load_bitmap("coin.png"); 
	health = al_load_bitmap("health.png");
	repair = al_load_bitmap("repair.png"); 
	healthpack = al_load_bitmap("healthpack.png");

	coindrop = NULL; 
	coindrop = al_load_sample("coin.wav"); 
	heart = NULL; 
	heart = al_load_sample("heart.wav");
	wrench = NULL; 
	wrench = al_load_sample("wrench.wav");
	powerup = NULL; 
	powerup = al_load_sample("powerup.wav"); 

	if (!coindrop || !heart || !wrench || !powerup)
	{
		exit(-9); 
	}

	speed = 10; 
	live = false; 
	angle = 0.0; 

	maxFrame_c = 10; 
	curFrame_c = 0; 
	frameCount_c = 0; 
	frameDelay_c = 3; 
	frameWidth_c = 50;
	frameHeight_c = 50;
	animationColumns_c = 10; 
	animationRows_c = 1; 

	maxFrame_h = 5;
	curFrame_h = 0;
	frameCount_h = 0;
	frameDelay_h = 3;
	frameWidth_h = 62;
	frameHeight_h = 62;
	animationColumns_h = 8;
	animationRows_h = 2;
}
/**
	Destructor for objects of class Special
*/
Special::~Special()
{
	al_destroy_bitmap(coin); 
	al_destroy_bitmap(health); 
	al_destroy_bitmap(healthpack); 
	al_destroy_bitmap(repair); 
	al_destroy_sample(coindrop); 
	al_destroy_sample(wrench); 
	al_destroy_sample(powerup); 
	al_destroy_sample(heart); 
}
/**
	Draws the special item on the dispaly
	@param width		integer containing display width in pixels
	@param height		integer containing display height in pixels
	@param type			integer contianing the special's type
*/
void Special::drawSpecial(int width, int height, int type)
{
	// 0 points - coin
	// 1 health - heart
	// 2 repair - wrench
	// 3 sheild - healthpack (full power)

	int fx; 
	int fy; 
	float r; 
	float g;
	float b; 

	switch (type)
	{
	case 0: 		fx = (curFrame_c % animationColumns_c) * frameWidth_c;
					fy = (curFrame_c / animationColumns_c) * frameHeight_c;
					al_draw_bitmap_region(coin, fx, fy, frameWidth_c, frameHeight_c, x, y, 0);
					break; 
	case 1:			fx = (curFrame_h % animationColumns_h) * frameWidth_h;
					fy = (curFrame_h / animationColumns_h) * frameHeight_h;
					al_draw_bitmap_region(health, fx, fy, frameWidth_h, frameHeight_h, x, y, 0);
					break;
	case 2:			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					al_draw_tinted_rotated_bitmap(repair, al_map_rgba_f(r, g, b, 1), 25, 25, x, y, angle, 0);
					break;
	case 3:			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					al_draw_tinted_rotated_bitmap(healthpack, al_map_rgba_f(r, g, b, 1), 25, 25, x, y, angle, 0);
					break;
	}
}
/**
	Updates the special items location on the display
	@param height		integer containing display height in pixels
	@param type			integer containing the special's type
*/
void Special::updateSpecial(int height, int type)
{
	switch (type)
	{
	case 0: if (live) //if alive
			{
				y -= speed;
				if (++frameCount_c >= frameDelay_c)
				{
					curFrame_c += 1;
					if (curFrame_c >= maxFrame_c)
					{
						curFrame_c = 0;
					}
					frameCount_c = 0;
				}
			}
			break; 
	case 1: if (live) //if alive
			{
				y -= speed;
				if (++frameCount_h >= frameDelay_h)
				{
					curFrame_h += 1;
					if (curFrame_h >= maxFrame_h)
					{
						curFrame_h = 0;
					}
					frameCount_h = 0;
				}
			}
			break; 
	case 2: if (live) //if alive
			{
				y -= speed;
				angle -= .08; 
			}
			break;
	case 3: if (live) //if alive
			{
				y -= speed;
				angle -= .08;
			}
			break;
	}

	if (y < MAXDEPTH)
	{
		live = false; 
	}
}
/**
	Stars the special on the display when a crate is destroyed
	@param width		integer containing display width in pixels
	@param height		integer contianing display height in pixels
	@param crate		array containing crate objects
	@param c			integer containing which crate we're referencing
	@param type			integer containing the special's type
*/
void Special::startSpecial(int width, int height, Crate crate[], int c, int type)
{
	if (crate[c].getDestroy() && !live)
	{
		live = true; 
		x = crate[c].getX(); 
		y = crate[c].getY(); 
		switch (type)
		{
		case 0:	al_play_sample(coindrop, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); 
			break; 
		case 1: al_play_sample(heart, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); 
			break; 
		case 2: al_play_sample(wrench, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); 
			break; 
		case 3: al_play_sample(powerup, 1.2, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); 
			break; 
		}
	}
}
