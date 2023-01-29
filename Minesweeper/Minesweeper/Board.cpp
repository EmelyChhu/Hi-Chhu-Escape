#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "TextureManager.h"
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include "Board.h"

// maze maker

// verifies whether the tile is in-bounds
int Board::IsInBounds(int x, int y)
{
    // Returns "true" if x and y are both in-bounds.
    if (x < 3 || x >= width - 3) return false;
    if (y < 3 || y >= height - 3) return false;
    return true;
}

// This is the recursive function we will code in the next project
void Board::Visit(int x, int y)
{
    // Starting at the given index, recursively visits every direction in a
    // randomized order.
    // Set my current location to be an empty passage.
    tiles[y][x].setWall(false);
    // Create an local array containing the 4 directions and shuffle their order.
    int dirs[4];
    dirs[0] = 0;
    dirs[1] = 1;
    dirs[2] = 2;
    dirs[3] = 3;
    for (int i = 0; i < 4; ++i)
    {
        int r = rand() & 3;
        int temp = dirs[r];
        dirs[r] = dirs[i];
        dirs[i] = temp;
    }
    // Loop through every direction and attempt to Visit that direction.
    for (int i = 0; i < 4; ++i)
    {
        // dx,dy are offsets from current location. Set them based
        // on the next direction I wish to try.
        int dx = 0, dy = 0;
        switch (dirs[i])
        {
        case 0: dy = -1; break;
        case 2: dy = 1; break;
        case 1: dx = 1; break;
        case 3: dx = -1; break;
        }
        // Find the (x,y) coordinates of the grid cell 2 spots
        // away in the given direction.
        int x2 = x + (dx << 1);
        int y2 = y + (dy << 1);
        if (IsInBounds(x2, y2))
        {
            if (tiles[y2][x2].getWall() == true)
            {
                // (x2,y2) has not been visited yet... knock down the
                // wall between my current position and that position
                tiles[y2 - dy][x2 - dx].setWall(false);
                // Recursively Visit (x2,y2)
                Visit(x2, y2);
            }
        }
    }
}

// defines the Board class

// constructors

// constructor
Board::Board(int width, int height)
{
    this->width = width;
    this->height = height;
}

// methods

// restarts the clock
void Board::restartClock()
{
    clock.restart();
}

// returns the time elapsed by the clock
int Board::getTime()
{
    sf::Time elapsed = clock.getElapsedTime();
    return int(elapsed.asSeconds() + 0.5);
}

// draws the board
void Board::draw(sf::RenderWindow& window, std::string keyboard)
{
    // clears the window and sets a black background
    window.clear(sf::Color::Black);

    // if the game is on the start screen
    if (state == "start")
    {
        // draws the gray background
        getSprite("background").setPosition(0, 0);
        window.draw(getSprite("background"));

        // set the sprites and positions for the title and start instructions
        getSprite("title").setPosition(50, 50);
        window.draw(getSprite("title"));
        getSprite("start").setPosition(50, 500);
        window.draw(getSprite("start"));

        // if the game is on easy mode
        if (hard == false)
        {
            getSprite("switch_off").setPosition(400, 700);
            window.draw(getSprite("switch_off"));
            getSprite("pink_slime_easy_option").setPosition(50, 625);
            window.draw(getSprite("pink_slime_easy_option"));
            getSprite("blue_slime_easy_option").setPosition(600, 625);
            window.draw(getSprite("blue_slime_easy_option"));
        }
        // if the game is on hard mode
        else if (hard == true)
        {
            getSprite("switch_on").setPosition(400, 700);
            window.draw(getSprite("switch_on"));
            getSprite("blue_slime_hard_option").setPosition(600, 625);
            window.draw(getSprite("blue_slime_hard_option"));
            getSprite("pink_slime_hard_option").setPosition(50, 625);
            window.draw(getSprite("pink_slime_hard_option"));
        }
    }
    // if the game is on the start screen
    else if (state == "play")
    {
        int countY = 0;
        // iterates through all of the tiles that will be shown
        for (unsigned int i = charY - 4; i <= charY + 4; i++)
        {
            int countX = 0;
            for (unsigned int j = charX - 4; j <= charX + 4; j++)
            {
                // draws the tile
                tiles[i][j].setX(countX * 100);
                tiles[i][j].setY(countY * 100);
                tiles[i][j].draw(window, slime);
                countX++;

                // draws character
                if (i == charY && j == charX)
                {
                    if (slime == "blue" && hard == false)
                    {
                        if (keyboard == "right")
                        {
                            getSprite("blue_slime_1right").setPosition(tiles[i][j].getX(), tiles[i][j].getY());
                            window.draw(getSprite("blue_slime_1right"));
                        }
                        else if (keyboard == "left")
                        {
                            getSprite("blue_slime_1left").setPosition(tiles[i][j].getX(), tiles[i][j].getY());
                            window.draw(getSprite("blue_slime_1left"));
                        }
                    }
                    if (slime == "blue" && hard == true)
                    {
                        if (keyboard == "right")
                        {
                            getSprite("blue_slime_hard_1right").setPosition(tiles[i][j].getX(), tiles[i][j].getY());
                            window.draw(getSprite("blue_slime_hard_1right"));
                        }
                        else if (keyboard == "left")
                        {
                            getSprite("blue_slime_hard_1left").setPosition(tiles[i][j].getX(), tiles[i][j].getY());
                            window.draw(getSprite("blue_slime_hard_1left"));
                        }
                    }
                    else if (slime == "pink" && hard == false)
                    {
                        if (keyboard == "right")
                        {
                            getSprite("pink_slime_1right").setPosition(tiles[i][j].getX(), tiles[i][j].getY());
                            window.draw(getSprite("pink_slime_1right"));
                        }
                        else if (keyboard == "left")
                        {
                            getSprite("pink_slime_1left").setPosition(tiles[i][j].getX(), tiles[i][j].getY());
                            window.draw(getSprite("pink_slime_1left"));
                        }
                    }
                    else if (slime == "pink" && hard == true)
                    {
                        if (keyboard == "right")
                        {
                            getSprite("pink_slime_hard_1right").setPosition(tiles[i][j].getX(), tiles[i][j].getY());
                            window.draw(getSprite("pink_slime_hard_1right"));
                        }
                        else if (keyboard == "left")
                        {
                            getSprite("pink_slime_hard_1left").setPosition(tiles[i][j].getX(), tiles[i][j].getY());
                            window.draw(getSprite("pink_slime_hard_1left"));
                        }
                    }
                }

                // if the tile is a wall
                if (tiles[i][j].getWall() == true)
                {
                    // draw a wall image
                    getSprite("wall").setPosition(tiles[i][j].getX(), tiles[i][j].getY());
                    window.draw(getSprite("wall"));
                }
            }
            countY++;
        }

        // draws the filter on the screen
        getSprite("filter").setPosition(0,0);
        window.draw(getSprite("filter"));
        
        // calculates the amount of minutes and seconds elapsed
        minutes = getTime() / 60;
        seconds = getTime() % 60;

        // draws the digit in the 1s place of the seconds
        sf::Sprite digit1(TextureManager::GetTexture(std::to_string(seconds % 10)));
        digit1.setPosition(100, 850);
        window.draw(digit1);

        // draws the digit in the 10s place of the seconds
        sf::Sprite digit2(TextureManager::GetTexture(std::to_string(seconds / 10)));
        digit2.setPosition(60, 850);
        window.draw(digit2);

        // draws the digit in the minutes place
        sf::Sprite digit3(TextureManager::GetTexture(std::to_string(minutes)));
        digit3.setPosition(0, 850);
        window.draw(digit3);

        // draws the colon
        getSprite("colon").setPosition(40, 850);
        window.draw(getSprite("colon"));
    }
    // if the game is on the end screen
    else if (state == "end")
    {
        // set the sprites and positions for the background and end information
        getSprite("background").setPosition(0, 0);
        window.draw(getSprite("background"));
        getSprite("end").setPosition(2, 200);
        window.draw(getSprite("end"));

        getSprite("in").setPosition(300, 390);
        window.draw(getSprite("in"));
        getSprite("colon").setPosition(465, 400);
        window.draw(getSprite("colon"));

        getSprite("tryagain").setPosition(325, 570);
        window.draw(getSprite("tryagain"));
        getSprite("credits").setPosition(450, 750);
        window.draw(getSprite("credits"));

        // draws the digit in the 1s place of the seconds
        sf::Sprite digit1(TextureManager::GetTexture(std::to_string(seconds % 10)));
        digit1.setPosition(535, 400);
        window.draw(digit1);

        // draws the digit in the 10s place of the seconds
        sf::Sprite digit2(TextureManager::GetTexture(std::to_string(seconds / 10)));
        digit2.setPosition(490, 400);
        window.draw(digit2);

        // draws the digit in the minutes place
        sf::Sprite digit3(TextureManager::GetTexture(std::to_string(minutes)));
        digit3.setPosition(420, 400);
        window.draw(digit3);
    }

    // displays the window
    window.display();
}

// adds Tile objects to the tiles vector and randomizes maze placement
void Board::initializeBoard()
{
    // if the game is on hard mode
    if (hard == true)
    {
        width = 81;
        height = 81;
    }
    // if the game is on easy mode
    else 
    {
        width = 31;
        height = 31;
    }

    // iterates through each row in the board
    for (unsigned int i = 0; i < height; i++)
    {
        // initializes a vector of Tile objects
        std::vector<Tile> tileRow;

        // iterates through Tile in the row
        for (unsigned int j = 0; j < width; j++)
        {
            // initializes a Tile object with the given coordinates and adds it to the vector of Tile objects
            Tile tile = Tile(100 * j, 100 * i);
            tile.setWall(true);
            tileRow.push_back(tile);
           
        }

        // adds the vector of Tile objects to the tiles vector
        tiles.push_back(tileRow);
    }

    // calls the maze generation algorithm and sets the end goal
    Visit(4, 4);
    tiles[4][4].setGold(true);
    tiles[height - 5][width - 5].setGold(true);
    }

// check whether the user has won
bool Board::checkWin()
{
    if (charX == width - 5 && charY == height - 5)
    {
        state = "end";
        minutes = getTime() / 60;
        seconds = getTime() % 60;
        return true;
    }
    return false;
}

// loads the board's sprite for the given sprite name
void Board::loadSprite(std::string spriteName)
{
    sf::Sprite sprite;
    sprite.setTexture(TextureManager::GetTexture(spriteName));
    sprites[spriteName] = sprite;
}

// setters

// sets the state of the game
void Board::setState(std::string state)
{
    this->state = state;
}

// sets the slime for the game
void Board::setSlime(std::string slime)
{
    this->slime = slime;
}

// sets the difficulty of the game
void Board::setHard(bool difficulty)
{
    hard = difficulty;
}

// sets the x-coordinate of the character
void Board::setCharX(int x)
{
    charX = x;
}
// sets the x-coordinate of the character
void Board::setCharY(int y)
{
    charY = y;
}


// accessors

// returns the state the game is in
std::string Board::getState()
{
    return state;
}

// returns which slime the game is using
std::string Board::getSlime()
{
    return slime;
}

// returns whether the game is in hard mode
bool Board::getHard()
{
    return hard;
}

// returns the x-coordinate of the character
int Board::getCharX()
{
    return charX;
}
// returns the y-coordinate of the character
int Board::getCharY()
{
    return charY;
}

// returns the board's sprite for the given sprite name
sf::Sprite& Board::getSprite(std::string spriteName)
{
    // if the texture doesn't exist
    if (sprites.find(spriteName) == sprites.end())
        loadSprite(spriteName);

    return sprites[spriteName];
}

// returns the tiles vector of the board
std::vector <std::vector <Tile> >& Board::getTiles()
{
    return tiles;
}