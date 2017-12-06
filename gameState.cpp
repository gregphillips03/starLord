/**
	William (Greg) Phillips
	Star Lord
*/

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <iostream>
#include "gameState.h"


/**
	Constructor for objects of class GameState
*/
GameState::GameState()
{
	sample = NULL; 
	sample = al_load_sample("speedincrease.wav");
	p1 = NULL; 
	p1 = al_load_sample("speeddecrease.wav"); 
	speedreduction = NULL; 
	speedreduction = al_load_sample("speedreduction.wav"); 

	healthBar = NULL; 
	healthBar = al_load_bitmap("healthbar.png"); 
	frameWidth = 228;
	frameHeight = 136;
	animationColumns = 7;
	animationRows = 1;
	maxFrame = 7;
	curFrame = 0;

	hullhealth = NULL;
	hullhealth = al_load_bitmap("hullhealth.png"); 
	frameWidth_hull = 800; 
	frameHeight_hull = 25; 
	animationColumns_hull = 1; 
	animationRows_hull = 20; 
	maxFrame_hull = 20; 
	curFrame_hull = 0; 

	if (!hullhealth)
	{
		exit(9); 
	}

	playerHealth = 1000; //change back to 1000 after debugging
	playerScore = 0; 
	hits = 0; 
	delaypulsered = 0; 
	delaypulseorange = 0; 
	delaypulseyellow = 0; 
	msgstart = 0; 
	msgend = 0; 
}
/**
	Updates the game's level, based on the number of enemy ship kills
	@param enemy[]		array of enemy objects
	@param asteroid[]	array of asteroid objects
	@param numEnemy		integer containing max number of enemy
	@param level		address location of integer containing the current game level
	@param kills		integer containing the number of enemy ships killed
	@param phase		address of integer value containing the current game phase
*/
bool GameState::updateLevel(Enemy enemy[], int numEnemy, int &level, int kills, int &phase, bool &levelComplete)
{
	switch (level)
	{
	case 1:
		if (kills > 20)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(1);
				al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
			level += 1;
		}
		break;
	case 2:
		if (kills > 40)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(1);
			}
			level += 1;
			al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		break;
	case 3:
		if (kills > 60)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(1);
			}
			level += 1;
			al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		break;
	case 4:
		if (kills > 80)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(1);
			}
			level += 1;
			al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		break;
	case 5:
		if (kills > 100)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(1);
			}
			level += 1;
			al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		break;
	case 6:
		if (kills > 120)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(1);
			}
			level += 1;
			al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		break;
	case 7:
		if (kills > 140)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(-1);
			}
			level += 1;
			msgstart = 0; 
			msgend = 480; 
			al_play_sample(p1, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); 
		}
		break;
	case 8:
		if (kills > 160)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(-1);
			}
			level += 1;
			al_play_sample(speedreduction, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); 
		}
		break;
	case 9:
		if (kills > 180)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(-1); 
			}
			levelComplete = true; 
			level += 1;
			phase += 1; 
		}
		break;
	case 10:
		if (kills > 220)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(1);
			}
			level += 1;
			al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		break; 
	case 11:
		if (kills > 240)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(1);
			}
			level += 1;
			al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
		break; 
	case 12:
		if (kills > 260)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(1);
			}
			level += 1;
			al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	case 13:
		if (kills > 280)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(1);
			}
			level += 1;
			al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
	case 14:
		if (kills > 300)
		{
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].setSpeed(1);
			}
			level += 1;
			al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			levelComplete = true; 
			phase =+ 1;
		}
	}

	if (++msgstart < msgend)
	{
		return true; 
	}
	else
	{
		return false; 
	}
}
/**
	Checks the current game state to ensure that the hull is not destroyed and too many friendlies haven't been killed
	@param hits				integer containing the number of hits agains the ship hull
	@param friendKills		integer containing the number of friendly ships killed
	@param done				address of boolean value to determine if the game is over
	@param levelComplete	bool address containing if the level has been completed
*/
bool GameState::phaseOneCheck(int friendKills, bool &done, bool &levelComplete)
{
	if (hits > 19 || friendKills > 9)
	{
		done = true;
		levelComplete = false; 
		return true; 
	}
	else
	{
		return false; 
	}
}
/**
	Checks the first phase to determine if it's done or not
	@param friendKills		integer containing number of friendly ships killed
	@param done				boolean address of done variable containing if the game is done or not
	@param levelComplete	address of boolean variable that contains if the level was succesfully completed
*/
bool GameState::phaseTwoCheck(bool &done, bool &levelComplete)
{
	if (hits > 19)
	{
		done = true; 
		levelComplete = false; 
		return true; 
	}
	if (playerHealth < 1)
	{
		done = true; 
		return true; 
	}
	return false; 
}
/**
	Checks the second phase to determine if it's done or not
	@param done				boolean address of done variable containing if the game is done or not
	@param levelComplete	address of boolean variable that contains if the level was succesfully completed
*/
void GameState::drawHealth(int width, int height, float camera, ALLEGRO_FONT *font)
{
	//std::cout << "hit the draw health function. Health at: " << playerHealth << "\n";
	if (getHealth() >= 900)
	{
		curFrame = 0; 
	}
	else if (getHealth() >= 800)
	{
		curFrame = 1; 
	}
	else if (getHealth() >= 650)
	{
		curFrame = 2; 
	}
	else if (getHealth() >= 400)
	{
		curFrame = 3; 
	}
	else if (getHealth() >= 200)
	{
		curFrame = 4; 
	}
	else if (getHealth() >= 100)
	{
		curFrame = 5; 
	}
	else
	{
		curFrame = 6; 
	}

	if (curFrame >= 5 && delaypulsered >= 3)
	{
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = (curFrame / animationColumns) * frameHeight;
		al_draw_tinted_bitmap_region(healthBar, al_map_rgb(255, 0, 0), fx, fy, frameWidth, frameHeight, 0, height - 200 + camera, 0);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 75, height - 180 + camera, 0, "%i", playerHealth);
	}
	else if (curFrame >= 4 && delaypulseorange >= 3)
	{
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = (curFrame / animationColumns) * frameHeight;
		al_draw_tinted_bitmap_region(healthBar, al_map_rgb(255, 165, 0), fx, fy, frameWidth, frameHeight, 0, height - 200 + camera, 0);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 75, height - 180 + camera, 0, "%i", playerHealth);
	}
	else if (curFrame >= 3 && delaypulseyellow >= 3)
	{
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = (curFrame / animationColumns) * frameHeight;
		al_draw_tinted_bitmap_region(healthBar, al_map_rgb(255, 255, 0), fx, fy, frameWidth, frameHeight, 0, height - 200 + camera, 0);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 75, height - 180 + camera, 0, "%i", playerHealth);
	}
	else
	{
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = (curFrame / animationColumns) * frameHeight;
		al_draw_bitmap_region(healthBar, fx, fy, frameWidth, frameHeight, 0, height - 200 + camera, 0);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 75, height - 180 + camera, 0, "%i", playerHealth);
	}
	if (++delaypulsered > 4)
	{
		delaypulsered = 0; 
	}
	if (++delaypulseorange > 7)
	{
		delaypulseorange = 0; 
	}
	if (++delaypulseyellow > 10)
	{
		delaypulseyellow = 0; 
	}

}
/**
	Draws the health bar onto the screen
	@param width		integer containing width of display in pixels
	@param height		integer	containing height of display in pixels
	@param camera		float containing current camera position to modify health bar's position during scrolling
	@param font			pointer to allegro font to display the health numerically above the health bar
*/
void GameState::drawHullHealth(int width, int height, float camera, ALLEGRO_FONT *font)
{
	if (hits < 20)
	{
		curFrame_hull = hits; 
	}
	else
	{
		curFrame_hull = 19; 
	}
	int fx = (curFrame_hull % animationColumns_hull) * frameWidth_hull;
	int fy = (curFrame_hull / animationColumns_hull) * frameHeight_hull;
	al_draw_bitmap_region(hullhealth, fx, fy, frameWidth_hull, frameHeight_hull, 0, 0 + camera, 0);
	al_draw_textf(font, al_map_rgb(255, 255, 255), width/2, 5 + camera, 0, "%i", 20 - hits);
}
/**
	Updates the player's score, health, and hull damage
	@param type		integer containing the type of the special object sent from the method call
*/
void GameState::updateStats(int type)
{
	switch (type)
	{
	case 0:	playerScore += 10 * (rand() % 10 + 1);
		break;
	case 1: playerHealth += 100;
		if (playerHealth > 1000)
		{
			playerHealth = 1000;
		}
		break;
	case 2: hits -= 1;
		if (hits < 0)
		{
			hits = 0; 
		}
		break; 
	case 3:	playerHealth = 1000; 
		break; 
	}
}
