#include "TextureManager.h"
#include <unordered_map>
#include <string>

// redeclare variable because it is static
std::unordered_map<std::string, sf::Texture> TextureManager::textures;

// takes in a file name and adds images/ and .png
// adds it to the map
void TextureManager::LoadTexture(std::string textureName)
{
	std::string path = "images/";
	path += textureName + ".png";

	textures[textureName].loadFromFile(path);
}

// returns the texture for a given texture name
// if name doesn't exist load it then return
// if textures.find(textureName) == textures.end(), pass it into LoadTexture
sf::Texture& TextureManager::GetTexture(std::string textureName)
{
	// if the texture doesn't exist
	if (textures.find(textureName) == textures.end())
		LoadTexture(textureName);

	return textures[textureName];
}

// call this at the end of main()
void TextureManager::Clear()
{
	textures.clear();
}