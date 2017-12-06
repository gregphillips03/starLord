/**
	William (Greg) Phillips
	Star Lord
*/

/**
	The weapon class is the fighter ship shown on the display, controlled by the end user. It controls drawing the 
	figter on the display, moving it around, and checking for collision with other objects. 
*/

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "weapon.h"
#define pi 3.14159265359

#define MAXDEPTH -1120

/**
	Constructor for objects of class Weapon
*/
Weapon::Weapon(int width, int height)
{
	image = al_load_bitmap("./img/weapon.png"); 
	angle = 0.0; 
	boundx = al_get_bitmap_width(image); 
	boundy = al_get_bitmap_height(image); 
	x = (width / 2);
	y = height - (boundy / 2);
	speed = 5; 
}
/**
	Destructor for objects of class weapon
*/
Weapon::~Weapon()
{
	al_destroy_bitmap(image); 
}
/**
	Draws the weapon to the screen
	@param width	integer containing screen width in pixels
	@param height	integer containing screen height in pixels
*/
void Weapon::drawWeapon(int width, int height)
{
	//al_draw_rotated_bitmap(image, boundx / 2, boundy / 2, (width / 2), height - (boundy /2), angle, 0);
	al_draw_rotated_bitmap(image, boundx / 2, boundy / 2, x, y, angle, 0);
}
/**
	Rotates the ship to the left on its center axis
*/
void Weapon::rotateLeft()
{
	angle -= 0.08;
	if (angle < -1.4)
    {
		angle = -1.4; 
	}
}
/**
	Rotates the ship to the right on its center axis
*/
void Weapon::rotateRight()
{
	angle += 0.08;
	if (angle > 1.4)
	{
		angle = 1.4;
	}
}
/**
	Moves the ship to the left side of the display
*/
void Weapon::moveLeft()
{
	x -= speed; 
	if (x < 0 + boundx / 2)
	{ 
		x = 0 + boundx / 2;
	}
}
/**
	Moves the ship to the right side of the display
*/
void Weapon::moveRight(int width)
{
	x += speed; 
	if (x > width - boundx / 2)
	{
		x = width - boundx / 2; 
	}
}
/**
	Moves the ship to the top side of the display
*/
void Weapon::moveForward()
{
	y -= speed; 
	if (y < MAXDEPTH + boundy / 2)
	{
		y = MAXDEPTH + boundy / 2; 
	}
}
/**
	Moves the ship to the bottom side of the display
*/
void Weapon::moveBackward(int height)
{
	y += speed; 
	if (y > height - boundy / 2)
	{
		y = height - boundy / 2; 
	}
}
/**
	Determines if an asteroid has collided with the ship and damages ship if it did
	@param asteroid		array of asteroid objects
	@param numAsteroid	integer containing number of asteroids
	@param gs			address of GamesState object
*/
void Weapon::collideWithAsteroid(Asteroid asteroid[], int numAsteroid, GameState &gs)
{
	for (int i = 0; i < numAsteroid; i++)
	{
		if (asteroid[i].getLive())
		{
			if (x > (asteroid[i].getX() + 32) &&
				x < (asteroid[i].getX() + asteroid[i].getBoundX() - 32) &&
				y > (asteroid[i].getY()) &&
				y < (asteroid[i].getY() + asteroid[i].getBoundY()) - 32)
			{
				gs.setHealth(-1); 
				//al_clear_to_color(al_map_rgb(255, 0, 0)); 
				//al_flip_display(); 
				//al_clear_to_color(al_map_rgb(255, 255, 255)); 
				//al_flip_display(); 
			}
		}
	}
}
