#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include "Tile.h"
#include "TextureManager.h"

// defines the Tile class

// constructors

// default constructor
Tile::Tile()
{
	wall = false;
	x = 0;
	y = 0;
	sf::Sprite sprite;
}

// constructor
Tile::Tile(int x, int y)
{
	wall = false;
	this->x = x;
	this->y = y;
	this->setSprite(x, y, "floor");
}

// methods

// draws the tile
void Tile::draw(sf::RenderWindow& window, std::string slime)
{
	setSprite(x, y, "floor");
	sprite.setTexture(TextureManager::GetTexture("floor"));
	window.draw(sprite);
 
	if (paint == true)
	{
		if (slime == "blue")
		{
			sprite.setTexture(TextureManager::GetTexture("blue_paint1"));
		}
		else if (slime == "pink")
		{
			sprite.setTexture(TextureManager::GetTexture("pink_paint1"));
		}
		
		window.draw(sprite);
	}

	if (gold == true)
	{
		sprite.setTexture(TextureManager::GetTexture("portal"));
		window.draw(sprite);
	}
}

// setters

// sets whether the tile contains a mine
void Tile::setWall(bool state)
{
	wall = state;
}

// sets whether the tile contains paint
void Tile::setPaint(bool state)
{
	paint = state;
}

// sets whether the tile contains the character
void Tile::setGold(bool state)
{
	gold = state;
}

// sets the tile's sprite to the given texture at the given coordinates
void Tile::setSprite(int x, int y, std::string textureName)
{
	sprite.setTexture(TextureManager::GetTexture(textureName));
	sprite.setPosition(x, y);
}

// sets the x-coordinate of the tile
void Tile::setX(int x)
{
	this->x = x;
}

// sets the y-coordinate of the tile
void Tile::setY(int y)
{
	this->y = y;
}

// accessors

// returns whether the tile is a mine
bool Tile::getWall()
{
	return wall;
}

// returns whether the tile contains paint
bool Tile::getPaint()
{
	return paint;
}

// returns whether the tile contains the character
bool Tile::getGold()
{
	return gold;
}

// returns the tile's x coordinate
int Tile::getX()
{
	return x;
}

// returns the tile's y coordinate
int Tile::getY()
{
	return y;
}

// returns the tile's sprite
sf::Sprite Tile::getSprite()
{
	return sprite;
}