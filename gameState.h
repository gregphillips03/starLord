/**
	William (Greg) Phillips
	Star Lord
*/

/**
	The game state class is the game manager. It's the hub of the information for the player. It controls
	the hull damage, player health, and play score. It updates the levels based of the user's performance
	and draws health bars onto the screen.
*/

#ifndef GSTATEH
#define GSTATEH
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "enemy.h"

class GameState
{
public:
	GameState();
	~GameState(){};
	bool updateLevel(Enemy enemy[], int numEnemy, int &level, int kills, int &phase, bool &levelComplete);
	void updateStats(int type); 
	void drawHealth(int width, int height, float camera, ALLEGRO_FONT *font); 
	void drawHullHealth(int width, int height, float camera, ALLEGRO_FONT *font); 
	bool phaseOneCheck(int friendKills, bool &done, bool &levelComplete);
	bool phaseTwoCheck(bool &done, bool &levelComplete); 
	void phaseThreeCheck(bool &done){}; 
	int getScore(){ return playerScore;  }
	void setScore(int i){ playerScore += i; }
	void setHealth(int i){ playerHealth += i; }
	int getHits(){ return hits;  }
	int getHealth(){ return playerHealth; }
	void setHits(int i){ hits += i; }
private: 
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationRows;
	int maxFrame;
	int curFrame;

	int frameWidth_hull;
	int frameHeight_hull;
	int animationColumns_hull;
	int animationRows_hull;
	int maxFrame_hull;
	int curFrame_hull;

	int playerHealth; 
	int playerScore; 
	int hits; 
	int delaypulsered;
	int delaypulseorange; 
	int delaypulseyellow; 
	int msgstart; 
	int msgend; 
	ALLEGRO_SAMPLE *sample;
	ALLEGRO_SAMPLE *p1; 
	ALLEGRO_SAMPLE *speedreduction;
	ALLEGRO_BITMAP *healthBar; 
	ALLEGRO_BITMAP *hullhealth; 
};

#endif