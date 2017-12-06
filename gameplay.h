/**
	William (Greg) Phillips
	Star Lord 
*/

/**
	The game play class manages the flow of the game. It moves the story along as well as the specific instances of what
	is presented to the user on the screen. It controls the camera location to provide for vertical scrolling, and sets up
	each phase with an introduction.
*/

#ifndef GAMEPLAYH
#define GAMEPLAYH
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "friend.h"
#include "soldier.h"
#include "enemy.h"
#include "gameState.h"
#include "weapon.h"
#include "laser.h"
#include "special.h"
#include "crate.h"
#include "hull.h"
#include "asteroid.h"

class GamePlay
{
public:
	GamePlay(); 
	~GamePlay(); 
	void phaseOneIntro(bool &done, ALLEGRO_EVENT_QUEUE *event_queue, int numFriend, int height, int width, Friend introFriendly[],
					Soldier &soldier); 
	void phaseTwoIntro(bool &done, ALLEGRO_EVENT_QUEUE *event_queue, int numFriend, int height, int width, Friend introFriendly[],
					Soldier &soldier);
	void gameIntro(bool &done, bool &play, ALLEGRO_EVENT_QUEUE *event_queue, int width, int height, int numEnemy, int numFriend, 
					Friend introFriend[], Enemy introEnemy[], GameState &gs, bool keys[]);
	void gameLoopOne(bool &done, int &phase, ALLEGRO_EVENT_QUEUE *event_queue, int width, int height, int numEnemy, int numFriend, 
					int numLaser, Weapon &weapon, bool keys[], Enemy enemy[], Laser laser[], int numCrate, Friend friendly[], 
					Crate crate[], GameState &gs, Special special[], int &level, int &kills, int &friendKills, int &save, 
					Soldier &soldier, bool &solMsg, Hull &hull, bool &levelComplete, Asteroid asteroid[]);
	void gameLoopTwo(bool &done, int &phase, ALLEGRO_EVENT_QUEUE *event_queue, int width, int height, int numEnemy,
		int numLaser, Weapon &weapon, bool keys[], Enemy enemy[], Laser laser[], int numCrate, Crate crate[],
		GameState &gs, Special special[], Asteroid asteroid[], int numAsteroid, int &level, int &kills, int &friendKills,
		int &save, Soldier &soldier, bool &solMsg, Hull &hull, bool &levelComplete);
	void gamePlayOver(Hull &hull, int width, int height, GameState &gs, int &level, int &kills, int &friendKills, int save,
					int numLaser, int numCrate, int numFriend, int numEnemy, Laser laser[], Friend friendly[], Weapon &weapon,
					Crate crate[], Enemy enemy[]);
	void cameraUpdate(float *cameraPosition, int playerx, int playery, int screenWidth, int screenHeight,
					int playerWidth, int playerHeight);
private:
	ALLEGRO_SAMPLE *phaseoneintro;
	ALLEGRO_SAMPLE *phasetwointro; 
	ALLEGRO_SAMPLE *siren; 
	ALLEGRO_TRANSFORM cameraTrans;
	ALLEGRO_BITMAP *background; 
	ALLEGRO_BITMAP *scale; 
	ALLEGRO_FONT *intro; 
	ALLEGRO_FONT *intro2; 
	ALLEGRO_FONT *info; 
	ALLEGRO_FONT *open24;
	ALLEGRO_FONT *gameOver;
	float cameraPosition[2];
	bool redraw; 
};

#endif