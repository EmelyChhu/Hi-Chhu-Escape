#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

// initializes the TextureManager class
class TextureManager
{
private:
	// static since only 1 instance of this class is used in memory
	static std::unordered_map<std::string, sf::Texture> textures;
	static void LoadTexture(std::string textureName);
public:
	static sf::Texture& GetTexture(std::string textureName);
	// call this at the end of main()
	static void Clear();
};