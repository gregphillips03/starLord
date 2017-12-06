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
#include <iostream>
#include "math.h"

#define MAXDEPTH -1120

/**
	Constructor for objects of the class Laser
*/
Laser::Laser()
{
	live = false; 
	speed = 15; 
	radian_angle = 0.0; 
	image = al_load_bitmap("laser.png"); 
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	sample = NULL; 
	sample = al_load_sample("laser.wav");
	destruct = NULL; 
	destruct = al_load_sample("mechchaos.wav");
	checkFire = NULL; 
	checkFire = al_load_sample("checkfire.wav");
	crateBreak = NULL; 
	crateBreak = al_load_sample("crateBreak.wav");
	thud = NULL; 
	thud = al_load_sample("thud.wav"); 
	if (!sample || !destruct || !crateBreak ||!thud ||
		!checkFire)
	{
		exit(9);
	}
}
/**
	Destructor for objects of class laser
*/
Laser::~Laser()
{
	al_destroy_bitmap(image); 
}

void Laser::drawLaser(Weapon &weapon)
{
	if (live)
	{
		al_draw_rotated_bitmap(image, boundx / 2, boundy / 2, x, y, radian_angle, 0);
	}
}
/**
	Fires the ship's laser
	@param width	integer containing width of display
	@param height	integer containing height of display
	@param weapon	address location of weapon object
*/
bool Laser::fireLaser(int width, int height, Weapon &weapon)
{
	if (!live)
	{
		x = weapon.getX(); 
		y = weapon.getY();
		live = true;
		radian_angle = weapon.getAngle(); 
		al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		return true; 
	}
	else{ return false; }
}
/**
	Updates the position of the laser pulse on the screen
	@param weapon	weapon object to work with
	@param widht	integer containing display width
*/
void Laser::updateLaser(Weapon &weapon, int width)
{
	if (live)
	{
		y -= speed*cos(radian_angle); 
		x += speed*sin(radian_angle); 
		if (y < MAXDEPTH || x < 0 || x > width)
		{
			live = false; 
		}
	}
}
/**
	Checks for a collision between laser pulse and enemies on the screen
	@param enemy	array containing enemy ships
	@param numEnemy	integer containing max number of enemy ships
	@param weapon	address location of weapon object
	@return			1 for hit, 0 for no hit
*/
int Laser::collideLaser(Enemy enemy[], int numEnemy, Weapon &weapon)
{   
	if (live)
	{
		for (int i = 0; i < numEnemy; i++)
		{
			if (enemy[i].getLive())
			{
				if (x >(enemy[i].getX() - enemy[i].getBoundX()) &&
					x <(enemy[i].getX() + enemy[i].getBoundX()) &&
					y >(enemy[i].getY() - enemy[i].getBoundY()) &&
					y < (enemy[i].getY() + enemy[i].getBoundY()))
				{
					live = false; 
					al_play_sample(destruct, 1.5, 0.0, 1.3, ALLEGRO_PLAYMODE_ONCE, NULL);
					enemy[i].setLive(false); 
					enemy[i].setDestroy(true); 
					return 1; 
				}
			}
		}
	}
	return 0; 
}
/**
	Checks for a collision between laser pulse and friends on the screen
	@param friendly		array containing friendly ships
	@param numFriend	integer containing max number of friendly ships
	@param weapon		address location of weapon object
	@return				1 for hit, 0 for no hit
*/
int Laser::collideLaserFriend(Friend friendly[], int numFriend, Weapon &weapon)
{
	if (live)
	{
		for (int i = 0; i < numFriend; i++)
		{
			if (friendly[i].getLive())
			{
				if (x >(friendly[i].getX() + 32) &&
					x <(friendly[i].getX() + friendly[i].getBoundX()/2) &&
					y >(friendly[i].getY() - friendly[i].getBoundY()) &&
					y < (friendly[i].getY() + friendly[i].getBoundY()))
				{
					live = false;
					al_play_sample(checkFire, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					friendly[i].setLive(false);
					friendly[i].setDestroy(true);
					return 1;
				}
			}
		}
	}
	return 0;
}
/**
	Checks for collision between laser and crate
	@param crate		array containing crates ships
	@param numFriend	integer containing max number of crates 
	@param weapon		address location of weapon object
	@param gs			address location of gamestate object

*/
void Laser::collideLaserCrate(Crate crate[], int numCrate, Weapon &weapon, GameState &gs)
{
	if (live)
	{
		for (int i = 0; i < numCrate; i++)
		{
			if (crate[i].getLive())
			{
				if (x >(crate[i].getX() - crate[i].getBoundX()) &&
					x <(crate[i].getX() + crate[i].getBoundX()) &&
					y >(crate[i].getY() - crate[i].getBoundY()) &&
					y < (crate[i].getY() + crate[i].getBoundY()))
				{
					live = false;
					al_play_sample(crateBreak, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					crate[i].setLive(false);
					crate[i].setDestroy(true);
					std::cout << "Destroyed a type, " << crate[i].getType() << " crate.\n";
					gs.updateStats(crate[i].getType()); 
				}
			}
		}
	}
}
/**
	Checks for collision between laser and asteroid
	@param asteroid		asteroid array to work with
	@param numAsteroid	integer containging number of asteroids
	@param weapon		address of weapon object to work with
*/
void Laser::collideLaserAsteroid(Asteroid asteroid[], int numAsteroid, Weapon &weapon)
{
	if (live)
	{
		for (int i = 0; i < numAsteroid; i++)
		{
			if (asteroid[i].getLive())
			{
				if (x >(asteroid[i].getX() +  32) &&
					x <(asteroid[i].getX() + asteroid[i].getBoundX() - 32) &&
					y >(asteroid[i].getY()) &&
					y < (asteroid[i].getY() + asteroid[i].getBoundY()) - 32)
				{
					live = false;
					al_play_sample(thud, 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
					asteroid[i].setHP(1);
					asteroid[i].setContact(true); 
				}
			}
		}
	}
}