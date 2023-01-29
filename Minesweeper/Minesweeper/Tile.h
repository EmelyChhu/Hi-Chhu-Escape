#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

// initializes the Tile class
class Tile
{
private:
	bool wall = false;
	bool paint = false;
	bool gold = false;
	unsigned int x = 0;
	unsigned int y = 0;
	sf::Sprite sprite;
public:
	// constructors
	Tile();
	Tile(int x, int y);
	// methods
	void draw(sf::RenderWindow& window, std::string slime);
	// setters
	void setWall(bool state);
	void setPaint(bool state);
	void setGold(bool state);
	void setX(int x);
	void setY(int y);
	void setSprite(int x, int y, std::string textureName);
	// accessors
	bool getWall();
	bool getPaint();
	bool getGold();
	int getX();
	int getY();
	sf::Sprite getSprite();
};