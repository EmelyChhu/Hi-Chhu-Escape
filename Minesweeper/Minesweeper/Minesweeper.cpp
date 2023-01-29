#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "TextureManager.h"
#include "Tile.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    // opens the config file
    std::ifstream file("boards/config.cfg");
    std::string line;

    // stores the width and height of the board
    getline(file, line);
    int width = stoi(line);
    getline(file, line);
    int height = stoi(line);

    // creates an instance of the Board class
    Board board(width, height);

    // stores the most recent horizontal keyboard input
    std::string keyboard = "right";

    // initializes in-game music
    sf::SoundBuffer music;
    music.loadFromFile("audio/dream.wav");
    sf::Sound sound;
    sound.setBuffer(music);
    sound.setLoop(true);
    sound.play();

    // stores whether the user has won
    bool win = false;

    // initializes a square 900 x 900 window
    sf::RenderWindow window(sf::VideoMode(900, 900), "Hi-Chhu Escape");

    // runs the program as long as the window is open
    while (window.isOpen())
    {
        // checks the window's events that have been triggered
        sf::Event event;

        // if the game is in the start screen
        if (board.getState() == "start")
        {
            // set the win state to false
            win = false;

            // while there is an event to be processed
            while (window.pollEvent(event))
            {
                // if the window is closed close the window
                if (event.type == sf::Event::Closed)
                    window.close();

                // if a mouse button has been pressed
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    // stores the coordinates of the button press
                    auto coordinates = sf::Mouse::getPosition(window);

                    // if the left mouse button has been pressed
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // if a blue slime has been pressed
                        if (board.getSprite("blue_slime_easy_option").getGlobalBounds().contains(coordinates.x, coordinates.y) || board.getSprite("blue_slime_hard_option").getGlobalBounds().contains(coordinates.x, coordinates.y))
                        {
                            board.setState("play");
                            board.setSlime("blue");
                            board.restartClock();
                            board.initializeBoard();
                            
                        }
                        // if a pink slime has been pressed
                        else if (board.getSprite("pink_slime_easy_option").getGlobalBounds().contains(coordinates.x, coordinates.y) || board.getSprite("pink_slime_hard_option").getGlobalBounds().contains(coordinates.x, coordinates.y))
                        {
                            board.setState("play");
                            board.setSlime("pink");
                            board.restartClock();
                            board.initializeBoard();
                        }
                        // if the switch has been pressed, toggle the difficulty of the game
                        else if (board.getSprite("switch_off").getGlobalBounds().contains(coordinates.x, coordinates.y) || board.getSprite("switch_on").getGlobalBounds().contains(coordinates.x, coordinates.y))
                        {
                            if (board.getHard() == true)
                                board.setHard(false);
                            else
                                board.setHard(true);
                        }
                    }
                }
            }
        }
        // if the game is on the play screen
        else if (board.getState() == "play")
        {
            // checks if the user has won
            board.checkWin();

            // while there is an event to be processed
            while (window.pollEvent(event))
            {
                // if the window is closed close the window
                if (event.type == sf::Event::Closed)
                    window.close();

                // if the left arrow key has been pressed
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    keyboard = "left";
                    // if the left block is not a wall, move the character to the left
                    if (board.getTiles()[board.getCharY()][board.getCharX() - 1].getWall() != true)
                    {
                        board.getTiles()[board.getCharY()][board.getCharX()].setPaint(true);
                        board.setCharX(board.getCharX() - 1);                        
                    }
                }
                // if the right arrow key has been pressed
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    keyboard = "right";
                    // if the right block is not a wall, move the character to the right
                    if (board.getTiles()[board.getCharY()][board.getCharX() + 1].getWall() != true)
                    {
                        board.getTiles()[board.getCharY()][board.getCharX()].setPaint(true);
                        board.setCharX(board.getCharX() + 1);
                    }
                }
                // if the down arrow key has been pressed
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    // if the down block is not a wall, move the character to the right
                    if (board.getTiles()[board.getCharY() + 1][board.getCharX()].getWall() != true)
                    {
                        board.getTiles()[board.getCharY()][board.getCharX()].setPaint(true);
                        board.setCharY(board.getCharY() + 1);
                    }
                }
                // if the up arrow key has been pressed
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    // if the up block is not a wall, move the character to the right
                    if (board.getTiles()[board.getCharY() - 1][board.getCharX()].getWall() != true)
                    {
                        board.getTiles()[board.getCharY()][board.getCharX()].setPaint(true);
                        board.setCharY(board.getCharY() - 1);
                    }
                }
            }
        }
        // if the game is in the end state
        else if (board.getState() == "end")
        {
            // if the user has just won
            if (win == false)
            {
                win = true;
                //std::cout << board.getTime() << std::endl;
            }

            // while there is an event to be processed
            while (window.pollEvent(event))
            {
                // if the window is closed close the window
                if (event.type == sf::Event::Closed)
                    window.close();

                // if a mouse button has been pressed for restarting the game
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    // stores the coordinates of the button press
                    auto coordinates = sf::Mouse::getPosition(window);

                    // if the left mouse button has been pressed
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // if the try again button has been pressed, restart the game
                        if (board.getSprite("tryagain").getGlobalBounds().contains(coordinates.x, coordinates.y))
                        {
                            board = Board(width, height);
                            board.setState("start");
                            
                        }
                    }
                }
            }
        }

        // draws the board
        board.draw(window, keyboard);
    }
    
    // clears the vector of textures in the Texture Manager class
    TextureManager::Clear();

    return 0;
}