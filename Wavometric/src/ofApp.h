#pragma once

#include "ofMain.h"
#include <math.h>
#include <time.h>
#include "TileHandler.h"
#include "MapGrid.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	int gameState = 0;

	//Menu Caracteristics
	ofImage teamLogo;
	float teamLogoWidth;
	float teamLogoHeight;
	float teamLogoScale;
	float teamLogoIncrease;
	float teamLogoIncreaseDelay;

	bool mouseOverPlay;
	bool mouseOverCredits;

	ofImage creditsActive;

	ofImage bigCredits;

	float fadeCounter;
	float fadeDelay;

	ofImage logo;
	int delay;

	ofTrueTypeFont arialBlack54;
	ofTrueTypeFont arialBlack36;
	ofTrueTypeFont arialBlack25;

	ofTrueTypeFont racer25;
	ofTrueTypeFont racer36;
	ofTrueTypeFont racer54;

	ofRectangle fontRect;

	ofRectangle playRect;
	ofPoint playPos;

	ofRectangle creditsRect;
	ofPoint creditsPos;

	ofRectangle backRect;
	bool mouseOverBack;
	ofPoint backPos;


	string write;

	//Game Caracteristics
	class Shape
	{
	public:
		ofVec2f position;
		float speed;
		ofVec2f direction;
		int HP;
		int damage;
		ofImage image;
		float width, height;
		int scale;
		bool isMoving;
		bool isAlive;
		bool shooting;
		bool canShoot;
		int shootingDelay;
		int inc; //InimigoVoltas

		int afterDyingDelay;
		int afterDyingInc; //InimigoVoltas

		void kill()
		{
			bool isAlive = false;
		}

		void setSize(float width, float height)
		{
			this->width = width;
			this->height = height;
		}

		float getSize()
		{
			return this->width;
		}

		void setSize(float size)
		{
			this->width = size;
			this->height = size;
		}

		void setPosition(float x, float y)
		{
			this->position.x = x;
			this->position.y = y;
		}

		void setSpeed(float speed)
		{
			this->speed = speed;
		}

		void setHp(int hp)
		{
			this->HP = hp;
		}

		void applyDamage(int damage)
		{
			this->HP -= damage;
		}

		void setDamage(int damage) 
		{
			this->damage = damage;
		}

		void destroy()
		{
			this->isAlive = false;
		}
	};
	ofVec2f mouse;

	Shape player;

	Shape enemy[100];
	ofImage triangle;

	class Bullet
	{
	public:
		ofVec2f position;
		ofVec2f direction;
		ofImage image;
		float speed;
		bool isOnScreen;

		void destroy()
		{
			isOnScreen = false;
		}
	};
	Bullet bullet[50];
	int bulletID;

	struct input
	{
		bool w, a, s, d;
		bool up, left, down, right;
		bool space;
		bool k;
		bool click;
		int keyAmount;
	};
	input pressing;

	ofImage tracer;
	int tracerDelay;

	ofVec2f copyPosition[12];
	float copyWidth[12];
	float copyHeight[12];
	int n;
	int rate;

	bool waveStart;
	int wave;
	int waveEnemies;
	int livingEnemies;
	int enemiesAllowed;
	int maxLivingEnemies;
	int enemiesSpawned;
	int enemiesKilled;
	bool onWave;
	int totalEnemiesKilled;

	int spawnCorner;

	ofImage background;
	ofImage HUD;
	
	ofImage cursor;
	
	ofTrueTypeFont arial;

	ofRectangle backToMenu;
	bool mouseOverBackToMenu;
	ofVec2f backToMenuPos;

	ofRectangle retry;
	bool mouseOverRetry;
	ofVec2f retryPos;
	
	float deltaTime = ofGetLastFrameTime();

	int light;

	//Music
	ofSoundPlayer menuMusic;
	ofSoundPlayer inGameMusic;

	//Sounds
	ofSoundPlayer shot;
	ofSoundPlayer playerDeath;
	ofSoundPlayer enemyDeath;


	TileHandler* tileHandler;
	ofImage tileSheet;

	MapGrid* map;

	ofImage fundo;
};