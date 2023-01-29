#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "TextureManager.h"
#include "Tile.h"
#include <iostream>
#include <vector>

#pragma once

// initializes the Board class
class Board
{
private:
	unsigned int width;
	unsigned int height;
	bool hard = false;
	int minutes = 0;
	int seconds = 0;
	sf::Clock clock;
	std::string slime = "pink";
	std::string state = "start";
	sf::Sprite background;
	sf::Sprite switch_off;
	sf::Sprite switch_on;
	sf::Sprite blue_slime1;
	sf::Sprite wall;
	sf::Sprite gold;
	sf::Sprite paint;
	sf::Sprite title;
	sf::Sprite start;
	sf::Sprite end;
	sf::Sprite blue_button;
	sf::Sprite pink_button;
	std::unordered_map<std::string, sf::Sprite> sprites;
	std::vector<std::vector <Tile> > tiles;
	int charX = 4;
	int charY = 4;
public:
	// for variables to track character
	int getCharX();
	int getCharY();
	void setCharX(int x);
	void setCharY(int y);

	// maze maker
	int IsInBounds(int x, int y);
	void Visit(int x, int y);

	// constructors
	Board(int width, int height);
	// methods
	void restartClock();
	int getTime();
	void draw(sf::RenderWindow& window, std::string keyboard);
	void initializeBoard();
	bool checkWin();
	void loadSprite(std::string spriteName);
	// setters
	void setState(std::string state);
	void setSlime(std::string slime);
	void setHard(bool difficulty);
	// accessors
	std::string getState();
	std::string getSlime();
	bool getHard();
	sf::Sprite& getSprite(std::string spriteName);
	std::vector < std::vector <Tile> >& getTiles();
};