#include "ofApp.h"
#include <time.h>

#define OPENING 0
#define MENU 1
#define GAME 2
#define CREDITS 3
#define GAME_OVER 4

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(false);
	ofSetFrameRate(60);

	cursor.loadImage("images/cursor.png");

	srand(time(NULL));

	gameState = OPENING;

	//Music Config
	menuMusic.load("music/menuMusic.ogg");
	menuMusic.setVolume(0.5);
	menuMusic.setLoop(true);

	inGameMusic.load("music/inGameMusic.ogg");
	inGameMusic.setVolume(0.5);
	inGameMusic.setLoop(true);

	//Sounds
	shot.load("sounds/shot.ogg");
	shot.setVolume(0.2);

	playerDeath.load("sounds/playerDeath.ogg");
	playerDeath.setVolume(0.3);

	enemyDeath.load("sounds/enemyDeath.ogg");
	enemyDeath.setVolume(0.3);

	switch (gameState)
	{
	case OPENING:
		menuMusic.play();
		break;
	case MENU:
		menuMusic.play();
		break;
	case CREDITS:
		menuMusic.play();
		break;
	case GAME_OVER:
		menuMusic.play();
		break;
	case GAME:
		inGameMusic.play();
	}

	//Font Confing 
	arialBlack54.loadFont("fonts/ARIBLK.TTF", 54);
	arialBlack36.loadFont("fonts/ARIBLK.TTF", 36);
	arialBlack25.loadFont("fonts/ARIBLK.TTF", 25);

	racer25.loadFont("fonts/Racer.TTF", 25);
	racer36.loadFont("fonts/Racer.TTF", 36);
	racer54.loadFont("fonts/Racer.TTF", 54);
	//End of Font Config

	//Opening Settings 
	light = 0;
	ofBackground(light, light, light);
	teamLogo.loadImage("images/dancingflaglogo.png");
	teamLogoWidth = teamLogo.getWidth();
	teamLogoHeight = teamLogo.getHeight();
	teamLogoScale = 0.5f;
	teamLogoIncrease = 0.003f;
	teamLogoIncreaseDelay = 5;
	delay = 0;


	fadeCounter = 0;
	fadeDelay = 250;
	//End of Opening Settings

	//Menu Settings
	//Play Button
	mouseOverPlay = false;

	//Credits Button

	bool mouseOverCredits = false;

	//End of menu settings


	//Background Settings
	ofBackground(light, light, light);
	//End of Background Settings

	//Logo Settings
	logo.loadImage("images/logo.png");
	//End of Logo Settings

	//Background Settings
	ofBackground(light, light, light);
	//End of Background Settings

	//Credits Config
	mouseOverBack = false;
	//End of Credits Config

	//Tracer Configuration
	tracerDelay = 0;
	rate = 2;
	n = 0;
	tracer.loadImage("images/tracer.png");
	//End of Tracer Configuration

	//Player Configuration
	player.image.loadImage("images/player.png");

	player.position.x = ofGetWidth() / 2;
	player.position.y = ofGetHeight() / 2;
	player.scale = 2;
	player.width = 25 * player.scale;
	player.height = 25 * player.scale;

	player.setDamage(1);
	player.speed = 4 * player.scale * deltaTime;

	player.HP = 1;
	if (player.HP > 0)
		player.isAlive = true;

	player.canShoot = true;
	player.shooting = false;
	player.isMoving = false;
	//End of Player Configuration

	//Bullet Configuration
	for (int i = 0; i < 50; i++)
	{
		bullet[i].image.loadImage("images/bullet.png");
		bullet[i].isOnScreen = false;
	}
	player.shootingDelay = 15;
	player.inc = player.shootingDelay;
	bulletID = 0;
	//End of Bullet Configuration

	//Enemy Configuration

	//End of Enemy Configuration
	triangle.loadImage("images/triangle.png");
	//Input Configuration
	pressing.up = false;
	pressing.left = false;
	pressing.down = false;
	pressing.right = false;

	pressing.w = false;
	pressing.a = false;
	pressing.s = false;
	pressing.d = false;

	pressing.k = false;

	pressing.space = false;
	pressing.click = false;
	//End of Input Configuration

	//Wave System Configuration (WIP)
	wave = 0;
	waveEnemies = 2 * wave;
	livingEnemies = 0;
	maxLivingEnemies = 1 * wave;
	enemiesSpawned = 0;
	totalEnemiesKilled = 0;

	waveStart = false;
	onWave = false;
	//End of Wave System Configuration

	player.afterDyingDelay = 60;
	player.afterDyingInc = 0;

	//Game Over Screen

	//Background
	background.loadImage("Images/bg.png");
	HUD.loadImage("Images/hud.png");

	//Importando TileSheet no TileHandler
	/*tileSheet.loadImage("images/kenney.png");
	tileHandler = new TileHandler();
	tileHandler->addTiles(tileSheet, 27, 20);

	map = new MapGrid(16, 16, ofGetWidth(), ofGetHeight());
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		ifstream arquivo(path);
		for (int y = 0; y < map->getRows(); y++)
		{
			for (int x = 0; x < map->getColumns(); x++)
			{
				int tile;
				arquivo >> tile;
				map->setTile(x, y, tile);
				cout << map->getTile(x, y) << " ";
			}
			cout << endl;
		}
		arquivo.close();
	}*/

	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		fundo.loadImage(path);
	}
}
//--------------------------------------------------------------
void ofApp::update() {
	switch (gameState)
	{
	case OPENING:
		ofShowCursor();
		if (pressing.space || pressing.click)
		{
			gameState = MENU;
		}
		fadeCounter++;
		if (fadeCounter < fadeDelay)
		{
			delay++;
			if (delay == teamLogoIncreaseDelay)
			{
				teamLogoScale += teamLogoIncrease;
				teamLogoWidth = teamLogo.getWidth() * teamLogoScale;
				teamLogoHeight = teamLogo.getHeight() * teamLogoScale;
				delay = 0;
			}
		}
		else 
		{
			delay++;
			if (delay == teamLogoIncreaseDelay)
			{
				teamLogoScale += teamLogoIncrease;
				teamLogoWidth = teamLogo.getWidth() * teamLogoScale;
				teamLogoHeight = teamLogo.getHeight() * teamLogoScale;
				delay = 0;
			}
			if (light < 255)
			{
				light += 8;
				if (light > 255)
					light = 255;
				ofBackground(light, light, light);
			}
			else {
				gameState = MENU;
			}
		}
		break;
	case MENU:
		ofShowCursor();
		mouseOverPlay = false;
		mouseOverCredits = false;
		light = 255;
		ofBackground(light, light, light);
		if (ofGetMouseX() > playPos.x && ofGetMouseX() < playPos.x + playRect.width && ofGetMouseY() > playPos.y - playRect.height && ofGetMouseY() < playPos.y)
			mouseOverPlay = true;
		else
			mouseOverPlay = false;

		if (ofGetMouseX() > creditsPos.x && ofGetMouseX() < creditsPos.x + creditsRect.width && ofGetMouseY() > creditsPos.y - creditsRect.height && ofGetMouseY() < creditsPos.y)
			mouseOverCredits = true;
		else
			mouseOverCredits = false;
		break;
	case CREDITS:
		ofShowCursor();
		light = 255;
		ofBackground(light, light, light);

		if (ofGetMouseX() > backPos.x && ofGetMouseX() < backPos.x + backRect.width && ofGetMouseY() > backPos.y - backRect.height && ofGetMouseY() < backPos.y)
			mouseOverBack = true;
		else
			mouseOverBack = false;
		break;
	case GAME:
		ofHideCursor();

		//Background 
		if (light > 25)
		{
			light -= 5;
			ofBackground(light, light, light);
		}
		//End of Background

		//Player isAlive check
		if (player.HP <= 0)
		{
			player.isAlive = false;
			playerDeath.play();
		}
		//End of Player isAlive check

		//Player Movement
		if (player.isAlive)
		{
			if (pressing.w || pressing.up)
			{
				player.isMoving = true;
				player.position.y -= player.speed;
			}
			if (pressing.a || pressing.left)
			{
				player.isMoving = true;
				player.position.x -= player.speed;
			}
			if (pressing.s || pressing.down)
			{
				player.isMoving = true;
				player.position.y += player.speed;
			}
			if (pressing.d || pressing.right)
			{
				player.isMoving = true;
				player.position.x += player.speed;
			}
			if (!pressing.w && !pressing.up && !pressing.a && !pressing.left && !pressing.s && !pressing.down && !pressing.d && !pressing.right)
			{
				player.isMoving = false;
			}

			if ((pressing.w && pressing.a) || (pressing.up && pressing.left) ||
				(pressing.a && pressing.s) || (pressing.left && pressing.down) ||
				(pressing.s && pressing.d) || (pressing.down && pressing.right) ||
				(pressing.d && pressing.w) || (pressing.right && pressing.up))
			{
				player.speed = (4 * player.scale) * 0.75;
			}
			else
			{
				player.speed = 4 * player.scale;
			}
		}
		//End of Player Movement

		//Player Position Restriction
		if (player.isAlive)
		{
			if (player.position.x < 0)
				player.position.x = 0;

			if (player.position.x + player.width > ofGetWidth())
				player.position.x = ofGetWidth() - player.width;

			if (player.position.y < 0)
				player.position.y = 0;

			if (player.position.y + player.height > ofGetHeight())
				player.position.y = ofGetHeight() - player.height;
		}
		//End of Player Postition Restriction

		//Player Tracer
		tracerDelay++;
		if (tracerDelay >= rate)
		{
			tracerDelay = 0;
			copyPosition[n].x = player.position.x;
			copyPosition[n].y = player.position.y;
			copyWidth[n] = player.width * 2;
			copyHeight[n] = player.height * 2;
			n++;
		}
		for (int i = 0; i < 12; i++)
		{
			copyPosition[i].x += 0.5;
			copyPosition[i].y += 0.5;
			copyWidth[i] -= 1;
			copyHeight[i] -= 1;
		}

		if (n == 12)
			n = 0;
		//End of Player Tracer

		//Enemy Configuration
		
		//End of Enemy Configuration

		//Wave System
		waveEnemies = 2 * wave;
		maxLivingEnemies = wave;
		if (onWave && enemiesSpawned < waveEnemies)
		{
			if (livingEnemies < maxLivingEnemies)
			{ 
				enemiesAllowed = maxLivingEnemies - livingEnemies;
				for (int i = 0; i < enemiesAllowed; i++)
				{
					if (!enemy[i].isAlive)
					{
						enemy[i].image.loadImage("images/square.png");
						enemiesSpawned++;
						enemy[i].setSize(30);
						enemy[i].setHp(3);
						enemy[i].setDamage(1);
						enemy[i].setSpeed(3);

						switch (rand() % 4)
						{
						case 0:
							enemy[i].setPosition(rand() % ofGetWidth(), 0);
							break;
						case 1:
							enemy[i].setPosition(rand() % ofGetWidth(), ofGetHeight() - enemy[i].getSize());
							break;
						case 2:
							enemy[i].setPosition(0, rand() % ofGetHeight());
							break;
						case 3:
							enemy[i].setPosition(ofGetWidth() - enemy[i].getSize(), rand() % ofGetHeight());
							break;
						}

						enemy[i].isAlive = true;
						livingEnemies++;
					}
				}
			}
			waveStart = false;
		}

		if (enemiesKilled >= waveEnemies)
		{
			onWave = false;
			enemiesKilled = 0;
			enemiesSpawned = 0;
		}
		//End of Wave System

		//Enemy Movement
		for (int i = 0; i < waveEnemies; i++)
		{
			ofVec2f dist = ofVec2f(player.position + ofVec2f(player.width / 2, player.height / 2) - enemy[i].position - ofVec2f(enemy[i].width / 2, enemy[i].height / 2));
			enemy[i].direction = dist.normalized() * enemy[i].speed;
			enemy[i].position += enemy[i].direction;
			for (int o = 0; o < 50; o++)
			{
				if (bullet[o].isOnScreen)
				{
					if ((bullet[o].position + ofVec2f(20 / 2, 20 / 2)).distance(enemy[i].position + ofVec2f(enemy[i].getSize() / 2, enemy[i].getSize() / 2)) < 20 + enemy[i].getSize() / 2 && enemy[i].isAlive)
					{
						if (enemy[i].HP - player.damage <= 0)
						{
							enemyDeath.play();
							enemiesKilled++;
							totalEnemiesKilled++;
						}
						bullet[o].destroy();
						enemy[i].applyDamage(player.damage);
					}
				}
			}
			if (enemy[i].isAlive)
			{
				if (player.isAlive && (enemy[i].position + ofVec2f(enemy[i].width / 2, enemy[i].height / 2)).distance(player.position + ofVec2f(player.width / 2, player.height / 2)) < player.width / 2)
				{
					enemy[i].destroy();
					player.applyDamage(1);
					enemiesKilled++;
					totalEnemiesKilled++;
				}
			}
			if (enemy[i].HP <= 0)
			{
				enemy[i].destroy();
			}
		}

		//End of Enemy Movement
		
		//Checking amount of enemies
		for (int i = 0; i < waveEnemies; i++)
		{
			livingEnemies = 0;
			if (enemy[i].isAlive)
				livingEnemies++;
		}
		//End of that shit

		//Bullet 
		if (pressing.click && player.isAlive)
			player.shooting = true;
		else
			player.shooting = false;

		if(!player.canShoot)
			player.inc++;

		if (player.inc >= player.shootingDelay)
		{
			player.canShoot = true;
		}

		if (player.canShoot && player.shooting)
		{
			player.canShoot = false;
			player.inc = 0;
			if (bulletID >= 50)
			{
				bulletID = 0;
			}
			shot.play();
			bullet[bulletID].isOnScreen = true;
			bullet[bulletID].speed = 4;
			bullet[bulletID].position.x = (player.position.x + player.width/2) - 20 /2;
			bullet[bulletID].position.y = (player.position.y + player.height/2) - 20 /2;
			ofVec2f dist = ofVec2f(ofGetMouseX(), ofGetMouseY()) - bullet[bulletID].position;
			bullet[bulletID].direction = dist.normalized() * bullet[bulletID].speed;
			bulletID++;
		}

		for (int i = 0; i < 50; i++)
		{
			if(bullet[i].isOnScreen)
				bullet[i].position += bullet[i].direction * bullet[i].speed;
		}
		//End of Bullet
		cout << "HP:" << player.HP << endl;
	/*	cout << "onWave: " << onWave << endl;
		cout << "Enemies killed: " << enemiesKilled << endl;
		cout << "enemiesSpawned: " << enemiesSpawned << endl;
		cout << "waveEnemies: "  << waveEnemies<< endl;*/
		
		if (!player.isAlive)
		{
			player.position.x = 8000;
			player.afterDyingInc++;
			if (player.afterDyingInc >= player.afterDyingDelay)
			{
				player.afterDyingInc = 0;
				gameState = GAME_OVER;
				inGameMusic.stop();
				menuMusic.play();
			}
		}
		
		cout << totalEnemiesKilled << endl;

		break;
		case GAME_OVER:
			ofBackground(light);
			ofShowCursor();

			if ( light <= 255 )
			{
				light += 5;
				if (light > 255)
					light = 255;
			}

			if (ofGetMouseX() > retryPos.x && ofGetMouseX() < retryPos.x + retry.width && ofGetMouseY() > retryPos.y - retry.height && ofGetMouseY() < retryPos.y)
				mouseOverRetry = true;
			else
				mouseOverRetry = false;

			if (ofGetMouseX() > backToMenuPos.x && ofGetMouseX() < backToMenuPos.x + backToMenu.width && ofGetMouseY() > backToMenuPos.y - backToMenu.height && ofGetMouseY() < backToMenuPos.y)
				mouseOverBackToMenu = true;
			else
				mouseOverBackToMenu = false;

			break;

	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	switch (gameState)
	{
	case OPENING:
		teamLogo.draw((ofGetWidth() / 2) - (teamLogoWidth / 2), (ofGetHeight() / 2) - (teamLogoHeight / 2), teamLogoWidth, teamLogoHeight);
		break;

	case MENU:
		ofBackground(0);
		ofSetColor(255, 255, 255);
		background.draw(0, 0, ofGetWidth(), ofGetHeight());
		logo.draw((ofGetWidth() / 2) - (logo.getWidth() / 2), (ofGetHeight() / 4) - (logo.getHeight() / 2), logo.getWidth(), logo.getHeight());
		
		if (!mouseOverPlay)
		{
			ofSetColor(255, 255, 255);
		}
		else {
			ofSetColor(54, 188, 255);
		}
		playRect = racer36.getStringBoundingBox("PLAY", 0, 0);
		playPos.x = ofGetWidth() / 2 - playRect.width / 2;
		playPos.y = ofGetHeight() / 2 - playRect.height / 2;
		racer36.drawString("PLAY", playPos.x, playPos.y);

		if(!mouseOverCredits)
			ofSetColor(255, 255, 255);
		else
			ofSetColor(54, 188, 255);
		
		creditsRect = racer36.getStringBoundingBox("CREDITS", 0, 0);
		creditsPos.x = ofGetWidth() / 2 - creditsRect.width / 2;
		creditsPos.y = ofGetHeight() / 1.5 - creditsRect.height / 2;
		racer36.drawString("CREDITS", creditsPos.x, creditsPos.y);
		break;
	
	case CREDITS:
		ofBackground(0);
		ofSetColor(255, 255, 255);
		background.draw(0, 0, ofGetWidth(), ofGetHeight());
		write = "CREDITS";
		fontRect = racer54.getStringBoundingBox(write, 0, 0);
		racer54.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 8.00 - fontRect.height / 2);

		ofSetColor(54, 188, 255);
		write = "CODING";
		fontRect = racer36.getStringBoundingBox(write, 0, 0);
		racer36.drawString(write, ofGetWidth()/2 - fontRect.width/2,ofGetHeight()/4.60 - fontRect.height/2);

		write = "GUILHERME BASSA";
		fontRect = racer25.getStringBoundingBox(write, 0, 0);
		racer25.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 3.70 - fontRect.height / 2);

		write = "JOAO MATHEUS";
		fontRect = racer25.getStringBoundingBox(write, 0, 0);
		racer25.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 3.25 - fontRect.height / 2);

		write = "SOUND EFFECTS";
		fontRect = racer36.getStringBoundingBox(write, 0, 0);
		racer36.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 2.45 - fontRect.height / 2);

		write = "LEONARDO NEVES";
		fontRect = racer25.getStringBoundingBox(write, 0, 0);
		racer25.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 2.20 - fontRect.height / 2);

		write = "MUSIC";
		fontRect = racer36.getStringBoundingBox(write, 0, 0);
		racer36.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 1.80 - fontRect.height / 2);

		write = "THIAGO FELIPE";
		fontRect = racer25.getStringBoundingBox(write, 0, 0);
		racer25.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 1.65 - fontRect.height / 2);

		write = "ART";
		fontRect = racer36.getStringBoundingBox(write, 0, 0);
		racer36.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 1.40 - fontRect.height / 2);

		write = "GABRIELA PARIZOTTO";
		fontRect = racer25.getStringBoundingBox(write, 0, 0);
		racer25.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 1.30 - fontRect.height / 2);
		

		if (mouseOverBack)
			ofSetColor(54, 188, 255);
		else
			ofSetColor(255);

		backRect = racer54.getStringBoundingBox("BACK", 0, 0);
		backPos.x = ofGetWidth() / 2 - backRect.width / 2;
		backPos.y = ofGetHeight() / 1.10 - backRect.height / 2;
		racer54.drawString("BACK", backPos.x , backPos.y);
		
		break;

	case GAME:
		background.draw(0, 0, ofGetWidth(), ofGetHeight());
		//map->draw(*tileHandler);
		fundo.draw(0, 0, ofGetWidth(), ofGetHeight());
		HUD.draw(0, 0, ofGetWidth(), ofGetHeight());

		//Draw Tracer
		tracer.draw(player.position.x - player.width / 2, player.position.y - player.height / 2, player.width * 2, player.height * 2);
		for (int i = 0; i < 12; i++)
		{
			tracer.draw(copyPosition[i].x - player.width / 2, copyPosition[i].y - player.width / 2, copyWidth[i], copyHeight[i]);
		}

		//Draw Bullet
		for (int i = 0; i < 50; i++)
		{
			if(bullet[i].isOnScreen)
				bullet[i].image.draw(bullet[i].position.x, bullet[i].position.y, 20, 20);
		}

		//Draw Enemies
		for (int i = 0; i < waveEnemies; i++)
		{
			if (enemy[i].isAlive)
			{
				enemy[i].image.draw(enemy[i].position.x, enemy[i].position.y, enemy[i].getSize(), enemy[i].getSize());
			}
		}

		//Draw Player
		//player.image.draw(player.position.x, player.position.y, player.width, player.height);

		//Draw HUD
		ofSetColor(255);
		write = "WAVE";
		if (!onWave && wave > 0)
		{
			ofSetColor(0,255,0);
			fontRect = racer36.getStringBoundingBox(write, 0, 0);
			racer36.drawString(write, ofGetWidth() / 2.5 - fontRect.width / 2, ofGetHeight() / 15 - fontRect.height / 2);

			ofSetColor(0, 255, 0);
			fontRect = racer36.getStringBoundingBox(std::to_string(wave), 0, 0);
			racer36.drawString(std::to_string(wave), ofGetWidth() / 2.5 + ofGetWidth() / 5 - fontRect.width / 2, ofGetHeight() / 15 - fontRect.height / 2);
		}
		else
		{
			ofSetColor(54, 188, 255);
			fontRect = racer36.getStringBoundingBox(write, 0, 0);
			racer36.drawString(write, ofGetWidth() / 2.5 - fontRect.width / 2, ofGetHeight() / 15 - fontRect.height / 2);

			ofSetColor(54, 188, 255);
			fontRect = racer36.getStringBoundingBox(std::to_string(wave), 0, 0);
			racer36.drawString(std::to_string(wave), ofGetWidth() / 2.5 + ofGetWidth() / 5 - fontRect.width / 2, ofGetHeight() / 15 - fontRect.height / 2);
		}
		if (!onWave)
		{
			ofSetColor(54, 188, 255);
			write = "PRESS E TO START WAVE";
			fontRect = racer36.getStringBoundingBox(write, 0, 0);
			racer36.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 1.1 - fontRect.height / 2);
		}
		//Draw Cursor
		ofSetColor(255);
		cursor.draw(ofGetMouseX() - cursor.getWidth()/2, ofGetMouseY() - cursor.getHeight()/2);
		break;
	case GAME_OVER:
		ofSetColor(25);
		write = "GAME OVER!";
		fontRect = arialBlack54.getStringBoundingBox(write, 0, 0);
		arialBlack54.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 3 - fontRect.height / 2);

		write = "YOU SURVIVED " + std::to_string(wave -1) + " WAVES";
		fontRect = arialBlack25.getStringBoundingBox(write, 0, 0);
		arialBlack25.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 2 - fontRect.height / 2);

		write = "YOU KILLED " + std::to_string(totalEnemiesKilled) + " ENEMIES";
		fontRect = arialBlack25.getStringBoundingBox(write, 0, 0);
		arialBlack25.drawString(write, ofGetWidth() / 2 - fontRect.width / 2, ofGetHeight() / 1.75 - fontRect.height / 2);

		if (mouseOverRetry)
			ofSetColor(0, 136, 204);
		else
			ofSetColor(25);
		write = "RETRY";
		retry = arialBlack36.getStringBoundingBox(write, 0, 0);
		retryPos.x = ofGetWidth() / 2 - retry.width / 2;
		retryPos.y = ofGetHeight() / 1.50 - retry.height / 2;
		arialBlack36.drawString(write, retryPos.x, retryPos.y);

		if (mouseOverBackToMenu)
			ofSetColor(0, 136, 204);
		else
			ofSetColor(25);
		write = "BACK TO MENU";
		backToMenu = arialBlack36.getStringBoundingBox(write, 0, 0);
		backToMenuPos.x = ofGetWidth() / 2 - backToMenu.width / 2;
		backToMenuPos.y = ofGetHeight() / 1.35 - backToMenu.height / 2;
		arialBlack36.drawString(write, backToMenuPos.x, backToMenuPos.y);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == OF_KEY_UP || key == 'w')
	{
		pressing.up = true;
		pressing.w = true;
	}
	if (key == OF_KEY_LEFT || key == 'a')
	{
		pressing.left = true;
		pressing.a = true;
	}
	if (key == OF_KEY_DOWN || key == 's')
	{
		pressing.down = true;
		pressing.s = true;
	}
	if (key == OF_KEY_RIGHT || key == 'd')
	{
		pressing.right = true;
		pressing.d = true;
	}
	if (key == GLFW_KEY_SPACE)
	{
		pressing.space = true;
	}
	if (key == 'e' && !onWave && player.isAlive)
	{
		wave++;
		waveStart = true;
		onWave = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == OF_KEY_UP || key == 'w')
	{
		pressing.up = false;
		pressing.w = false;
	}
	if (key == OF_KEY_LEFT || key == 'a')
	{
		pressing.left = false;
		pressing.a = false;
	}
	if (key == OF_KEY_DOWN || key == 's')
	{
		pressing.down = false;
		pressing.s = false;
	}
	if (key == OF_KEY_RIGHT || key == 'd')
	{
		pressing.right = false;
		pressing.d = false;
	}
	if (key == GLFW_KEY_SPACE)
	{
		pressing.space = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (pressing.click)
		mouse = ofVec2f(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (button == OF_MOUSE_BUTTON_1)
		pressing.click = true;


	if (button == OF_MOUSE_BUTTON_1 && mouseOverPlay && gameState == MENU)
	{
		menuMusic.stop();
		inGameMusic.play();

		player.position.x = ofGetWidth() / 2;
		player.position.y = ofGetHeight() / 2;
		player.scale = 2;
		player.width = 25 * player.scale;
		player.height = 25 * player.scale;

		player.setDamage(1);
		player.speed = 4 * player.scale * deltaTime;

		player.HP = 1;
		player.isAlive = true;

		player.canShoot = true;
		player.shooting = false;
		player.isMoving = false;

		wave = 0;
		waveEnemies = 2 * wave;
		livingEnemies = 0;
		maxLivingEnemies = 1 * wave;
		enemiesSpawned = 0;
		totalEnemiesKilled = 0;

		waveStart = false;
		onWave = false;

		for (int i = 0; i < 50; i++)
		{
			enemy[i].isAlive = false;
		}


		gameState = GAME;

		gameState = GAME;
	}

	if (button == OF_MOUSE_BUTTON_1 && mouseOverCredits && gameState == MENU)
		gameState = CREDITS;

	if (button == OF_MOUSE_BUTTON_1 && mouseOverBack && gameState == CREDITS)
		gameState = MENU;

	if (button == OF_MOUSE_BUTTON_1 && mouseOverBackToMenu && gameState == GAME_OVER)
		gameState = MENU;

	if (button == OF_MOUSE_BUTTON_1 && mouseOverRetry && gameState == GAME_OVER)
	{
		player.position.x = ofGetWidth() / 2;
		player.position.y = ofGetHeight() / 2;
		player.scale = 2;
		player.width = 25 * player.scale;
		player.height = 25 * player.scale;

		player.setDamage(1);
		player.speed = 4 * player.scale * deltaTime;

		player.HP = 1;
		player.isAlive = true;

		player.canShoot = true;
		player.shooting = false;
		player.isMoving = false;

		wave = 0;
		waveEnemies = 2 * wave;
		livingEnemies = 0;
		maxLivingEnemies = 1 * wave;
		enemiesSpawned = 0;
		totalEnemiesKilled = 0;

		waveStart = false;
		onWave = false;

		for (int i = 0; i < 50; i++)
		{
			enemy[i].isAlive = false;
		}

		gameState = GAME;
		menuMusic.stop();
		inGameMusic.play();
	}


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (button == OF_MOUSE_BUTTON_1)
		pressing.click = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}