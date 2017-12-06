/**
	William (Greg) Phillips
	Star Lord
*/

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <iostream>
#include "weapon.h"
#include "enemy.h"
#include "laser.h"
#include "hull.h"
#include "friend.h"
#include "gameState.h"
#include "crate.h"
#include "asteroid.h"
#include "soldier.h"
#include "special.h"
#include "gameplay.h"

#define MAXDEPTH -1120

int main(void)
{
	/**
		SET UP THE BASIC WORKING PARTS OF THE GAME	
	*/

	const int width = 800; //screen width
	const int height = 800; //screen height
	const int FPS = 60; //frames per second
	const int numEnemy = 7;
	const int numLaser = 100;
	const int numFriend = 3; 
	const int numCrate = 7; 
	const int numAsteroid = 10; 
	enum KEYS{left, right, space, enter, up, down, a, f, d}; //keys available to player
	bool keys[9] = { false, false, false, false, false, false, false, false, false}; //array to store key use values
	bool done = false; //if the the game is over with
	bool redraw = true; //if we should flash the display
	bool play = false; //if the player is ready to play the game
	bool solMsg = false; 
	bool levelComplete = false; 
	int level = 1; //current player level
	int phase = 1; //current game phase
	int kills = 0; //ships killed
	int save = 0; //friendly ships protected
	int friendKills = 0; //friendly ships hit
	ALLEGRO_DISPLAY *display = NULL; //allocate memory for the display
	ALLEGRO_EVENT_QUEUE *event_queue = NULL; //allocate memory for the event queue
	ALLEGRO_TIMER *timer = NULL; //allocate memory for the timer
	ALLEGRO_SAMPLE *sample = NULL; 

	srand(time(NULL)); 

	if (!al_init()) //try to initialize allegro
	{ 
		return -1; //exit with malfunction code
	} 
	if (!al_install_audio())
	{
		return -1; 
	}
	if (!al_init_acodec_addon())
	{
		return -1; 
	}
	if (!al_reserve_samples(5))
	{
		return -1; 
	}
	sample = al_load_sample("./music/quantum.wav");

	if (!sample)
	{
		exit(9);
	}

	display = al_create_display(width, height); //create a display with a width and height

	if (!display) //try to initialize the display
	{
		return -1; //exit with malfunction code
	}

	al_install_keyboard(); //install the keyboard
	al_install_mouse(); //install the mouse
	al_init_image_addon(); //initialize the use of images
	al_init_font_addon(); //add fonts
	al_init_ttf_addon(); //add support for true type fonts

	Weapon weapon(width, height); //create a weapon object to work with
	Enemy enemy[numEnemy]; //create an array of enemy objects to work with
	Enemy introEnemy[numEnemy]; //create enemy ships for the intro screen
	Laser laser[numLaser]; //create an array of laser objects to work with
	Friend friendly[numFriend]; //create a friend object to work with
	Friend introFriendly[numFriend]; //create friendly ships for the intro screen
	Hull hull; //create hull object to work with
	GameState gs; //create a game state object to work with
	Crate crate[numCrate]; //create a crate object to work with
	Asteroid asteroid[numAsteroid]; //create an asteroid object to work with
	Soldier soldier; //create a soldier object to work with
	Special special[numCrate]; //create a special object to work with
	GamePlay gp; //create a gameplay object to work with

	event_queue = al_create_event_queue(); //create an event queue to work with
	timer = al_create_timer(1.0 / FPS); //create a timer that ticks 60 times a second
	srand(time(NULL)); //seed the timer with an initial random value

	al_register_event_source(event_queue, al_get_keyboard_event_source()); //register keyboard as an event source
	al_register_event_source(event_queue, al_get_timer_event_source(timer)); //register timer as an event source
	al_register_event_source(event_queue, al_get_display_event_source(display)); //register timer as an event source
	al_register_event_source(event_queue, al_get_mouse_event_source()); //register mouse as an event source

	al_start_timer(timer); //start ticking the timer
	al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

	/**
		INTRO LOOP
	*/

	gp.gameIntro(done, play, event_queue, width, height, numEnemy, numFriend, introFriendly, introEnemy, gs, keys); 

	/**
		Phase One Intro LOOP
	*/

	gp.phaseOneIntro(done, event_queue, numFriend, height, width, introFriendly, soldier); 

	/**
		GAME LOOP ONE
	*/

	gp.gameLoopOne(done, phase, event_queue, width, height, numEnemy, numFriend, numLaser, weapon, keys, enemy, laser, numCrate,
		friendly, crate, gs, special, level, kills, friendKills, save, soldier, solMsg, hull, levelComplete, asteroid);

	if (!gs.phaseOneCheck(friendKills, done, levelComplete) && levelComplete)
	{
		levelComplete = false; 
		/**
		Phase Two Intro LOOP
		*/
		gp.phaseTwoIntro(done, event_queue, numFriend, height, width, introFriendly, soldier);

		/**
		GAME LOOP TWO
		*/
		gp.gameLoopTwo(done, phase, event_queue, width, height, numEnemy, numLaser, weapon, keys, enemy, laser, numCrate,
			crate, gs, special, asteroid, numAsteroid, level, kills, friendKills, save, soldier, solMsg, hull, levelComplete);

		if (!gs.phaseTwoCheck(done, levelComplete) && levelComplete)
		{
			levelComplete = false; 
			/**
			Phase Three Intro LOOP
			*/

			/**
			GAME LOOP THREE
			*/
		}
	}

	/**
		GAME OVER
	*/

	gp.gamePlayOver(hull, width, height, gs, level, kills, friendKills, save, numLaser, numCrate, numFriend, numEnemy, laser, friendly,
		weapon, crate, enemy);

	al_destroy_event_queue(event_queue); //destroy our event queue object
	al_destroy_timer(timer);//destroy our timer object
	al_destroy_display(display); //destroy our display object

	return 0; //exit normally
}
