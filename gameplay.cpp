/**
	William (Greg) Phillips
	Star Lord 
*/

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include "gameplay.h"

#define MAXDEPTH -1120

enum KEYS{ left, right, space, enter, up, down, a, f, d };

/**
	Constructor for objects of class GamePlay
*/
GamePlay::GamePlay()
{
	redraw = true;
	cameraPosition[0] = 0;
	cameraPosition[1] = 0;

	intro = NULL;
	intro = al_load_font("./font/term.ttf", 72, 0); //allocate memory for the font, size 72
	intro2 = NULL;
	intro2 = al_load_font("./font/term.ttf", 60, 0); //allocated memory for the font, size 60
	info = NULL;
	info = al_load_font("./font/term.ttf", 24, 0); //allocate memory for the font, size 24
	open24 = NULL;
	open24 = al_load_font("./font/open24.ttf", 24, 0); //allocate memory for the font, size 24
	gameOver = NULL;
	gameOver = al_load_font("./font/term.ttf", 80, 0); //allocate memory for the font, size 80

	background = NULL;
	background = al_load_bitmap("./img/background.png");
	scale = NULL;
	scale = al_load_bitmap("./img/scale.png");
	phaseoneintro = NULL;
	phaseoneintro = al_load_sample("./sound/phaseoneintro.wav");
	phasetwointro = NULL;
	phasetwointro = al_load_sample("./sound/phasetwointro.wav");
	siren = NULL;
	siren = al_load_sample("./sound/siren.wav");

	if (!phaseoneintro || !phasetwointro || !siren)
	{
		exit(9);
	}
}

/**
	Destructor for objects of class GamePlay
*/
GamePlay::~GamePlay()
{
	al_destroy_sample(phaseoneintro); 
	al_destroy_bitmap(background);
}
/**
	Game introduction that displays the title text and function keys to the end user
	@param done			address of boolean variable of if the game is done or not
	@param play			address of boolean variable of if the user is ready to play
	@param event_queue	pointer to allegro event queue
	@param width		integer containing display width in pixels
	@param height		integer containing display height in pixels
	@param numEnemy		integer containing max number of enemy ships
	@param numFriend	integer containing max number of friendly ships
	@param introFriend	array containing friendly ship objects
	@param introEnemy	array containing enemy ship objects
	@param gs			address of game state object
	@param keys			boolean array containing key presses
*/

void GamePlay::gameIntro(bool &done, bool &play, ALLEGRO_EVENT_QUEUE *event_queue, int width, int height, int numEnemy, 
	int numFriend, Friend introFriendly[], Enemy introEnemy[], GameState &gs, bool keys[])
{
	while (!play && !done)
	{
		ALLEGRO_EVENT ev; //create an event variable
		al_wait_for_event(event_queue, &ev); //start listening for events

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if (keys[enter])
			{
				play = true;
			}
			for (int i = 0; i < numEnemy; i++) //try to spawn an enemy ship
			{
				introEnemy[i].startEnemy(width, height);
			}
			for (int i = 0; i < numFriend; i++) //try to spawn an enemy ship
			{
				introFriendly[i].startFriend(width, height);
			}
			for (int i = 0; i < numEnemy; i++) //update the enemy ship on the display
			{
				introEnemy[i].updateEnemy(height);
			}
			for (int i = 0; i < numFriend; i++) //update the enemy ship on the display
			{
				introFriendly[i].updateFriend(height);
			}
			for (int i = 0; i < numEnemy; i++) //check for collision
			{
				introEnemy[i].collideEnemy(height, gs.getHits(), width);
			}
			for (int i = 0; i < numFriend; i++) //check for collision
			{
				introFriendly[i].collideFriend(height);
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //we clicked the 'x' in the window
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) //we pressed a key
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ENTER:
				keys[enter] = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_draw_bitmap(background, 0, 0, 0);

			for (int i = 0; i < numFriend; i++)
			{
				introFriendly[i].drawFriend(width, height);
			}
			for (int i = 0; i < numEnemy; i++)
			{
				introEnemy[i].drawEnemy(width, height);
			}
			al_draw_text(intro, al_map_rgb(255, 255, 255), width / 2, 150, ALLEGRO_ALIGN_CENTRE,
				"Star Lord");
			al_draw_text(intro2, al_map_rgb(255, 0, 0), width / 2, 270, ALLEGRO_ALIGN_CENTRE,
				"First");
			al_draw_text(intro2, al_map_rgb(255, 0, 0), width / 2, 330, ALLEGRO_ALIGN_CENTRE,
				"Contact");
			al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, (height / 2) + 50, ALLEGRO_ALIGN_CENTRE,
				"<Space> to Rapid Fire Laser");
			al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, (height / 2) + 90, ALLEGRO_ALIGN_CENTRE,
				"<d> to Single Fire Laser");
			al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, (height / 2) + 130, ALLEGRO_ALIGN_CENTRE,
				"<a>/<f> to Turn Ship");
			al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, (height / 2) + 170, ALLEGRO_ALIGN_CENTRE,
				"<Arrow Keys> to Move Ship");
			al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, (height / 2) + 240, ALLEGRO_ALIGN_CENTRE,
				"Press <Enter> to Play");
			al_flip_display(); //flash the screen
			al_clear_to_color(al_map_rgb(0, 0, 0)); //clear the screen to black
		}
	}
}

void GamePlay::phaseOneIntro(bool &done, ALLEGRO_EVENT_QUEUE *event_queue, int numFriend, int height, int width, Friend introFriendly[], 
						Soldier &soldier)
{
	time_t start = time(NULL);
	time_t current = time(NULL);
	al_play_sample(phaseoneintro, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

	while (current - start < 12 && !done)
	{
		ALLEGRO_EVENT ev; //create an event variable
		al_wait_for_event(event_queue, &ev); //start listening for events

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			for (int i = 0; i < numFriend; i++) //try to spawn an enemy ship
			{
				introFriendly[i].startFriend(width, height);
			}
			for (int i = 0; i < numFriend; i++) //update the enemy ship on the display
			{
				introFriendly[i].updateFriend(height);
			}
			for (int i = 0; i < numFriend; i++) //check for collision
			{
				introFriendly[i].collideFriend(height);
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //we clicked the 'x' in the window
		{
			done = true;
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			current = time(NULL);
			al_draw_bitmap(background, 0, 0, 0);

			for (int i = 0; i < numFriend; i++)
			{
				introFriendly[i].drawFriend(width, height);
			}
			soldier.drawSoldier(width, height, 0);
			al_draw_text(intro, al_map_rgb(255, 255, 255), width / 2, 150, ALLEGRO_ALIGN_CENTRE,
				"Star Lord");
			al_draw_text(intro2, al_map_rgb(255, 0, 0), width / 2, 270, ALLEGRO_ALIGN_CENTRE,
				"Phase One");
			al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, 350, ALLEGRO_ALIGN_CENTRE,
				"\"Onslaught\"");
			al_draw_text(info, al_map_rgb(0, 255, 0), width / 2, 400, ALLEGRO_ALIGN_CENTRE,
				"Shoot the enemy ships");
			al_draw_text(info, al_map_rgb(255, 0, 0), width / 2, 450, ALLEGRO_ALIGN_CENTRE,
				"Don't shoot friendly ships");
			al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, 500, ALLEGRO_ALIGN_CENTRE,
				"Keep the enemy");
			al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, 530, ALLEGRO_ALIGN_CENTRE,
				"from hitting the hull!");
			al_flip_display(); //flash the screen
			al_clear_to_color(al_map_rgb(0, 0, 0)); //clear the screen to black
		}

	}
}

void GamePlay::phaseTwoIntro(bool &done, ALLEGRO_EVENT_QUEUE *event_queue, int numFriend, int height, int width, Friend introFriendly[],
						Soldier &soldier)
{
	time_t start = time(NULL);
	time_t current = time(NULL);
	al_play_sample(phasetwointro, 1.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

	while (current - start < 12)
	{
		ALLEGRO_EVENT ev; //create an event variable
		al_wait_for_event(event_queue, &ev); //start listening for events

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			for (int i = 0; i < numFriend; i++) //try to spawn an enemy ship
			{
				introFriendly[i].startFriend(width, height);
			}
			for (int i = 0; i < numFriend; i++) //update the enemy ship on the display
			{
				introFriendly[i].updateFriend(height);
			}
			for (int i = 0; i < numFriend; i++) //check for collision
			{
				introFriendly[i].collideFriend(height);
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //we clicked the 'x' in the window
		{
			done = true;
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			current = time(NULL);
			al_draw_bitmap(background, 0, 0 + cameraPosition[1], 0);

			for (int i = 0; i < numFriend; i++)
			{
				introFriendly[i].drawFriend(width, height);
			}
			soldier.drawSoldier(width, height, cameraPosition[1]);
			al_draw_text(intro, al_map_rgb(255, 255, 255), width / 2, 150 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
				"Star Lord");
			al_draw_text(intro2, al_map_rgb(255, 0, 0), width / 2, 270 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
				"Phase Two");
			al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, 350 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
				"\"Behind the Rubble\"");
			al_draw_text(info, al_map_rgb(0, 255, 0), width / 2, 400 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
				"Shoot Enemy Ships and Asteroids");
			al_draw_text(info, al_map_rgb(255, 0, 0), width / 2, 450 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
				"Don't Run into Asteroids");
			al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, 500 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
				"Keep the enemy");
			al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, 530 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
				"from hitting the hull!");
			al_flip_display(); //flash the screen
			al_clear_to_color(al_map_rgb(0, 0, 0)); //clear the screen to black
		}

	}
}

void GamePlay::gameLoopOne(bool &done, int &phase, ALLEGRO_EVENT_QUEUE *event_queue, int width, int height, int numEnemy,
						int numFriend, int numLaser, Weapon &weapon, bool keys[], Enemy enemy[], Laser laser[], int numCrate, 
						Friend friendly[], Crate crate[], GameState &gs, Special special[], int &level, int &kills, int &friendKills, 
						int &save, Soldier &soldier, bool &solMsg, Hull &hull, bool &levelComplete, Asteroid asteroid[])
{
	while (!done && phase == 1)
	{
		ALLEGRO_EVENT ev; //create an event variable
		al_wait_for_event(event_queue, &ev); //start listening for events

		if (ev.type == ALLEGRO_EVENT_TIMER) //event is generated by the timer
		{
			redraw = true;
			if (keys[a])
			{
				weapon.rotateLeft();
			}
			if (keys[f])
			{
				weapon.rotateRight();
			}
			if (keys[space])
			{
				for (int i = 0; i < numLaser; i++)
				{
					bool b = laser[i].fireLaser(width, height, weapon);
					if (b){ break; }
				}
			}
			if (keys[d])
			{
				for (int i = 0; i < numLaser; i++)
				{
					bool b = laser[i].fireLaser(width, height, weapon);
					if (b){ break; }
				}
				keys[d] = false;
			}
			if (keys[left])
			{
				weapon.moveLeft();
			}
			if (keys[right])
			{
				weapon.moveRight(width);
			}
			if (keys[up])
			{
				weapon.moveForward();
			}
			if (keys[down])
			{
				weapon.moveBackward(height);
			}

			//** Starts **//
			for (int i = 0; i < numEnemy; i++) //try to spawn an enemy ship
			{
				enemy[i].startEnemy(width, height);
			}
			for (int i = 0; i < numFriend; i++) //try to spawn an friendly ship
			{
				friendly[i].startFriend(width, height);
			}
			for (int i = 0; i < numCrate; i++) //try to spawn a crate and corresponding special effect
			{
				crate[i].startCrate(width, height);
				special[i].startSpecial(width, height, crate, i, crate[i].getType());
			}

			//** Updates **//
			for (int i = 0; i < numEnemy; i++) //update the enemy ship on the display
			{
				enemy[i].updateEnemy(height);
			}
			for (int i = 0; i < numFriend; i++) //update the friendly ship on the display
			{
				friendly[i].updateFriend(height);
			}
			for (int i = 0; i < numCrate; i++)
			{
				crate[i].updateCrate(height);
				special[i].updateSpecial(height, crate[i].getType());
			}
			for (int i = 0; i < numLaser; i++) //update location of laser pulses on screen
			{
				laser[i].updateLaser(weapon, width);
			}

			//** Collision with laser beams **//
			for (int i = 0; i < numLaser; i++)
			{
				int j = (laser[i].collideLaser(enemy, numEnemy, weapon));
				gs.setScore(j*level);
				kills += j;
			}
			for (int i = 0; i < numLaser; i++)
			{
				int j = (laser[i].collideLaserFriend(friendly, numFriend, weapon));
				gs.setScore(-(j*level));
				friendKills += j;
			}
			for (int i = 0; i < numLaser; i++)
			{
				laser[i].collideLaserCrate(crate, numCrate, weapon, gs);
			}

			//** Collision at screen bottom **//
			for (int i = 0; i < numEnemy; i++)
			{
				gs.setHits(enemy[i].collideEnemy(height, width, gs.getHits()));
			}
			for (int i = 0; i < numFriend; i++)
			{
				int j = friendly[i].collideFriend(height);
				save += j;
				gs.setScore(j*level);
			}
			for (int i = 0; i < numCrate; i++)
			{
				crate[i].collideCrate(height);
			}

			//** Transform based off camera position **//
			cameraUpdate(cameraPosition, weapon.getX(), weapon.getY(), width, height, weapon.getBoundX(), weapon.getBoundY());
			al_identity_transform(&cameraTrans);
			al_translate_transform(&cameraTrans, -cameraPosition[0], -cameraPosition[1]);
			al_use_transform(&cameraTrans);

			//** GameState Checks **//
			solMsg = gs.updateLevel(enemy, numEnemy, level, kills, phase, levelComplete);
			gs.phaseOneCheck(friendKills, done, levelComplete);
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //we clicked the 'x' in the window
		{
			done = true;
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) //we pressed a key
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[left] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[right] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[space] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[up] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[down] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[a] = true;
				break;
			case ALLEGRO_KEY_F:
				keys[f] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[d] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) //we stopped pressing a key
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[left] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[right] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[space] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[up] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[down] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[a] = false;
				break;
			case ALLEGRO_KEY_F:
				keys[f] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[d] = false;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_draw_bitmap(scale, 0, MAXDEPTH, 0);
			hull.drawHull(gs.getHits(), width, height);

			al_draw_textf(open24, al_map_rgb(255, 255, 255), 20, 750 + cameraPosition[1], ALLEGRO_ALIGN_LEFT,
				"SCORE: %i", gs.getScore());
			al_draw_textf(open24, al_map_rgb(255, 255, 255), 20, 720 + cameraPosition[1], ALLEGRO_ALIGN_LEFT,
				"LEVEL: %i", level);
			al_draw_textf(open24, al_map_rgb(255, 255, 255), 780, 720 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
				"ENEMY KILLS: %i", kills);

			switch (friendKills)
			{
			case 0:	al_draw_textf(open24, al_map_rgb(255, 255, 255), 780, 690 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
				"FRIEND KILLS: %i", friendKills);
				break;
			case 1: case 2:
				al_draw_textf(open24, al_map_rgb(0, 255, 0), 780, 690 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
					"FRIEND KILLS: %i", friendKills);
				break;
			case 3: case 4: case 5:
				al_draw_textf(open24, al_map_rgb(255, 255, 0), 780, 690 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
					"FRIEND KILLS: %i", friendKills);
				break;
			case 6: case 7:
				al_draw_textf(open24, al_map_rgb(255, 165, 0), 780, 690 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
					"FRIEND KILLS: %i", friendKills);
				break;
			case 8: case 9: case 10:
				al_draw_textf(open24, al_map_rgb(255, 0, 0), 780, 690 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
					"FRIEND KILLS: %i", friendKills);
				break;
			}
			al_draw_textf(open24, al_map_rgb(255, 255, 255), 780, 660 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
				"FRIEND SAVES: %i", save);
			switch (gs.getHits())
			{
			case 0:case 1: case 2: case 3: case 4: 			al_draw_textf(open24, al_map_rgb(0, 255, 0), //green
				780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
				break;
			case 5: case 6: case 7: case 8: case 9: al_draw_textf(open24, al_map_rgb(255, 255, 0), //yellow
				780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
				break;
			case 10: case 11: case 12: case 13: case 14:	al_draw_textf(open24, al_map_rgb(255, 165, 0), //orange
				780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
				break;
			default:	al_draw_textf(open24, al_map_rgb(255, 0, 0), //red
				780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
				break;
			}
			for (int i = 0; i < numLaser; i++)
			{
				laser[i].drawLaser(weapon);
			}
			for (int i = 0; i < numCrate; i++)
			{
				crate[i].drawCrate(width, height);
				if (special[i].getLive())
				{
					special[i].drawSpecial(width, height, crate[i].getType());
				}
			}
			for (int i = 0; i < numFriend; i++)
			{
				friendly[i].drawFriend(width, height);
			}
			gs.drawHealth(width, height, cameraPosition[1], info);
			gs.drawHullHealth(width, height, cameraPosition[1], info);
			if (solMsg)
			{
				soldier.drawSoldier(width, height, cameraPosition[1]);
			}
			weapon.drawWeapon(width, height);
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].drawEnemy(width, height);
			}
			al_flip_display(); //flash the screen
			al_clear_to_color(al_map_rgb(0, 0, 0)); //clear the screen to black
		}
	}
}

void GamePlay::gameLoopTwo(bool &done, int &phase, ALLEGRO_EVENT_QUEUE *event_queue, int width, int height, int numEnemy, 
	int numLaser, Weapon &weapon, bool keys[], Enemy enemy[], Laser laser[], int numCrate, Crate crate[],
	GameState &gs, Special special[], Asteroid asteroid[], int numAsteroid, int &level, int &kills, int &friendKills,
	int &save, Soldier &soldier, bool &solMsg, Hull &hull, bool &levelComplete)
{
	al_play_sample(siren, 1.2, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0); 

	while (!done && phase == 2)
	{
		ALLEGRO_EVENT ev; //create an event variable
		al_wait_for_event(event_queue, &ev); //start listening for events

		if (ev.type == ALLEGRO_EVENT_TIMER) //event is generated by the timer
		{
			redraw = true;
			if (keys[a])
			{
				weapon.rotateLeft();
			}
			if (keys[f])
			{
				weapon.rotateRight();
			}
			if (keys[space])
			{
				for (int i = 0; i < numLaser; i++)
				{
					bool b = laser[i].fireLaser(width, height, weapon);
					if (b){ break; }
				}
			}
			if (keys[d])
			{
				for (int i = 0; i < numLaser; i++)
				{
					bool b = laser[i].fireLaser(width, height, weapon);
					if (b){ break; }
				}
				keys[d] = false;
			}
			if (keys[left])
			{
				weapon.moveLeft();
			}
			if (keys[right])
			{
				weapon.moveRight(width);
			}
			if (keys[up])
			{
				weapon.moveForward();
			}
			if (keys[down])
			{
				weapon.moveBackward(height);
			}

			//** Starts **//
			for (int i = 0; i < numEnemy; i++) //try to spawn an enemy ship
			{
				enemy[i].startEnemy(width, height);
			}
			for (int i = 0; i < numCrate; i++) //try to spawn a crate and corresponding special effect
			{
				crate[i].startCrate(width, height);
				special[i].startSpecial(width, height, crate, i, crate[i].getType());
			}
			for (int i = 0; i < numAsteroid; i++) //try to spawn an asteroid
			{
				asteroid[i].startAsteroid(width, height);
			}

			//** Updates **//
			for (int i = 0; i < numEnemy; i++) //update the enemy ship on the display
			{
				enemy[i].updateEnemy(height);
			}
			for (int i = 0; i < numCrate; i++)
			{
				crate[i].updateCrate(height);
				special[i].updateSpecial(height, crate[i].getType());
			}
			for (int i = 0; i < numAsteroid; i++)
			{
				asteroid[i].updateAsteroid(height);
			}
			for (int i = 0; i < numLaser; i++) //update location of laser pulses on screen
			{
				laser[i].updateLaser(weapon, width);
			}

			//** Collision with laser beams **//
			for (int i = 0; i < numLaser; i++)
			{
				int j = (laser[i].collideLaser(enemy, numEnemy, weapon));
				gs.setScore(j*level);
				kills += j;
			}
			for (int i = 0; i < numLaser; i++)
			{
				laser[i].collideLaserCrate(crate, numCrate, weapon, gs);
			}
			for (int i = 0; i < numAsteroid; i++)
			{
				laser[i].collideLaserAsteroid(asteroid, numAsteroid, weapon);
			}

			//** Collision with Ship **//
			for (int i = 0; i < numAsteroid; i++)
			{
				weapon.collideWithAsteroid(asteroid, numAsteroid, gs); 
			}

			//** Collision at screen bottom **//
			for (int i = 0; i < numEnemy; i++)
			{
				gs.setHits(enemy[i].collideEnemy(height, width, gs.getHits()));
			}
			for (int i = 0; i < numCrate; i++)
			{
				crate[i].collideCrate(height);
			}
			for (int i = 0; i < numAsteroid; i++)
			{
				asteroid[i].collideAsteroid(height, gs);
			}
			//** Transform based off camera position **//
			cameraUpdate(cameraPosition, weapon.getX(), weapon.getY(), width, height, weapon.getBoundX(), weapon.getBoundY());
			al_identity_transform(&cameraTrans);
			al_translate_transform(&cameraTrans, -cameraPosition[0], -cameraPosition[1]);
			al_use_transform(&cameraTrans);

			//** GameState Checks **//
			solMsg = gs.updateLevel(enemy, numEnemy, level, kills, phase, levelComplete);
			gs.phaseTwoCheck(done, levelComplete);
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //we clicked the 'x' in the window
		{
			done = true;
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) //we pressed a key
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[left] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[right] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[space] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[up] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[down] = true;
				break;
			case ALLEGRO_KEY_A:
				keys[a] = true;
				break;
			case ALLEGRO_KEY_F:
				keys[f] = true;
				break;
			case ALLEGRO_KEY_D:
				keys[d] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) //we stopped pressing a key
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[left] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[right] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[space] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[up] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[down] = false;
				break;
			case ALLEGRO_KEY_A:
				keys[a] = false;
				break;
			case ALLEGRO_KEY_F:
				keys[f] = false;
				break;
			case ALLEGRO_KEY_D:
				keys[d] = false;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_draw_bitmap(scale, 0, MAXDEPTH, 0);
			hull.drawHull(gs.getHits(), width, height);

			al_draw_textf(open24, al_map_rgb(255, 255, 255), 20, 750 + cameraPosition[1], ALLEGRO_ALIGN_LEFT,
				"SCORE: %i", gs.getScore());
			al_draw_textf(open24, al_map_rgb(255, 255, 255), 20, 720 + cameraPosition[1], ALLEGRO_ALIGN_LEFT,
				"LEVEL: %i", level);
			al_draw_textf(open24, al_map_rgb(255, 255, 255), 780, 720 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
				"ENEMY KILLS: %i", kills);

			switch (gs.getHits())
			{
			case 0:case 1: case 2: case 3: case 4: 			al_draw_textf(open24, al_map_rgb(0, 255, 0), //green
				780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
				break;
			case 5: case 6: case 7: case 8: case 9: al_draw_textf(open24, al_map_rgb(255, 255, 0), //yellow
				780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
				break;
			case 10: case 11: case 12: case 13: case 14:	al_draw_textf(open24, al_map_rgb(255, 165, 0), //orange
				780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
				break;
			default:	al_draw_textf(open24, al_map_rgb(255, 0, 0), //red
				780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
				break;
			}
			for (int i = 0; i < numLaser; i++)
			{
				laser[i].drawLaser(weapon);
			}
			for (int i = 0; i < numCrate; i++)
			{
				crate[i].drawCrate(width, height);
				if (special[i].getLive())
				{
					special[i].drawSpecial(width, height, crate[i].getType());
				}
			}
			for (int i = 0; i < numAsteroid; i++)
			{
				asteroid[i].drawAsteroid(width, height);
			}

			gs.drawHealth(width, height, cameraPosition[1], info);
			gs.drawHullHealth(width, height, cameraPosition[1], info);
			if (solMsg)
			{
				soldier.drawSoldier(width, height, cameraPosition[1]);
			}
			weapon.drawWeapon(width, height);
			for (int i = 0; i < numEnemy; i++)
			{
				enemy[i].drawEnemy(width, height);
			}
			al_flip_display(); //flash the screen
			al_clear_to_color(al_map_rgb(0, 0, 0)); //clear the screen to black
		}
	}
}

void GamePlay::gamePlayOver(Hull &hull, int width, int height, GameState &gs, int &level, int &kills, int &friendKills, int save, 
						int numLaser, int numCrate, int numFriend, int numEnemy, Laser laser[], Friend friendly[], Weapon &weapon, 
						Crate crate[], Enemy enemy[])
{
	redraw = false;
	al_draw_bitmap(scale, 0, MAXDEPTH, 0);
	hull.drawHull(gs.getHits(), width, height);
	al_draw_textf(open24, al_map_rgb(255, 255, 255), 20, 750 + cameraPosition[1], ALLEGRO_ALIGN_LEFT,
		"SCORE: %i", gs.getScore());
	al_draw_textf(open24, al_map_rgb(255, 255, 255), 20, 720 + cameraPosition[1], ALLEGRO_ALIGN_LEFT,
		"LEVEL: %i", level);
	al_draw_textf(open24, al_map_rgb(255, 255, 255), 780, 720 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
		"ENEMY KILLS: %i", kills);
	switch (friendKills)
	{
	case 0:	al_draw_textf(open24, al_map_rgb(255, 255, 255), 780, 690 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
		"FRIEND KILLS: %i", friendKills);
		break;
	case 1: case 2:
		al_draw_textf(open24, al_map_rgb(0, 255, 0), 780, 690 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
			"FRIEND KILLS: %i", friendKills);
		break;
	case 3: case 4: case 5:
		al_draw_textf(open24, al_map_rgb(255, 255, 0), 780, 690 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
			"FRIEND KILLS: %i", friendKills);
		break;
	case 6: case 7:
		al_draw_textf(open24, al_map_rgb(255, 165, 0), 780, 690 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
			"FRIEND KILLS: %i", friendKills);
		break;
	case 8: case 9: case 10:
		al_draw_textf(open24, al_map_rgb(255, 0, 0), 780, 690 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
			"FRIEND KILLS: %i", friendKills);
		break;
	}
	al_draw_textf(open24, al_map_rgb(255, 255, 255), 780, 660 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT,
		"FRIEND SAVES: %i", save);
	switch (gs.getHits())
	{
	case 0:case 1: case 2: case 3: case 4: 			al_draw_textf(open24, al_map_rgb(0, 255, 0), //green
		780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
		break;
	case 5: case 6: case 7: case 8: case 9: al_draw_textf(open24, al_map_rgb(255, 255, 0), //yellow
		780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
		break;
	case 10: case 11: case 12: case 13: case 14:	al_draw_textf(open24, al_map_rgb(255, 165, 0), //orange
		780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
		break;
	default:	al_draw_textf(open24, al_map_rgb(255, 0, 0), //red
		780, 750 + cameraPosition[1], ALLEGRO_ALIGN_RIGHT, "DAMAGE: %i", 20 - gs.getHits());
		break;
	}
	for (int i = 0; i < numLaser; i++)
	{
		laser[i].drawLaser(weapon);
	}
	for (int i = 0; i < numCrate; i++)
	{
		crate[i].drawCrate(width, height);
	}
	for (int i = 0; i < numFriend; i++)
	{
		friendly[i].drawFriend(width, height);
	}
	gs.drawHealth(width, height, cameraPosition[1], info);
	weapon.drawWeapon(width, height);
	for (int i = 0; i < numEnemy; i++)
	{
		enemy[i].drawEnemy(width, height);
	}

	/**
	Game over text
	*/
	al_draw_text(gameOver, al_map_rgb(255, 0, 0), width / 2, height / 2 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
		"GAME OVER");
	if (gs.getHits() > 19)
	{
		al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, (height / 2) + 90 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
			"Hull Destroyed");
		al_draw_textf(info, al_map_rgb(255, 255, 255), width / 2, (height / 2) + 170 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
			"SCORE: %i", gs.getScore());
	}
	else if (friendKills > 9)
	{
		al_draw_text(info, al_map_rgb(255, 255, 255), width / 2, (height / 2) + 90 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
			"Too Many Friendly Ships Killed");
		al_draw_textf(info, al_map_rgb(255, 255, 255), width / 2, (height / 2) + 170 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
			"SCORE: %i", gs.getScore());
	}
	else
	{
		al_draw_textf(info, al_map_rgb(255, 255, 255), width / 2, (height / 2) + 170 + cameraPosition[1], ALLEGRO_ALIGN_CENTRE,
			"SCORE: %i", gs.getScore());
	}
	al_flip_display(); //flash the screen

	al_rest(10.0);
}

void GamePlay::cameraUpdate(float *cameraPosition, int playerx, int playery, int screenWidth, int screenHeight,
	int playerWidth, int playerHeight)
{
	cameraPosition[1] = -(screenHeight)+(playery + playerHeight / 2);

	if (cameraPosition[1] < MAXDEPTH)
	{
		cameraPosition[1] = MAXDEPTH;
	}
	//std::cout << "Pos: " << cameraPosition[1] << ".\n";
}