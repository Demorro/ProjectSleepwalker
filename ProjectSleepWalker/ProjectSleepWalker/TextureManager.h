#pragma once

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <map>

// Toggles debug couts
#define DEBUG_TEXTURE_MANAGER true

/**
	TEXTURE MANAGER CLASS
	----------------------
	This class ensures each texture used within the game is only loaded and created once.
	This class should not be instantiated as it is intended to work statically.
*/
class TextureManager
{
public:
	/** Clears all hash map entries. */
	static void Close();

	/**
		Loads a texture into the texture map. 
		Returns true if successful, otherwise returns false.
	*/
	static bool LoadTexture(std::string filepath);

	/**
		Removes a texture from the texture map if the entry exists. 
		Returns true if successful, otherwise returns false.
	*/
	static bool RemoveTexture(std::string filepath);

	/**
		Returns a texture from the texture map, if it does not exist it will be created.
		Returns the texture.
	*/
	static sf::Texture& GetTexture(std::string filepath);

private:
	/** 
		Creates an instance of a texture and inserts it into the texture map. 
		Returns true if the texture was created and inserted into the texture map,
		otherwise returns false which may be due to an invalid filetype, incorrect filepath.
	*/
	static bool CreateTexture(std::string filepath);

	/** Hash map of all the textures. */
	static std::map<std::string, sf::Texture*> textureMap;
	
	// Kept in private to prevent instantiation
	TextureManager();
	~TextureManager();
};

// Texture references
class Texture
{
public:
	static const std::string OPTIONS_BACKGROUND;	
	static const std::string HELP_BACKGROUND;		
	static const std::string MENU_BACKGROUND;		

	static const std::string PLAY_BUTTON;
	static const std::string QUIT_BUTTON;
	static const std::string HELP_BUTTON;
	static const std::string OPTIONS_BUTTON;
	static const std::string BACK_BUTTON;
	static const std::string DISPLAY_BUTTON;
	static const std::string AUDIO_BUTTON;
	static const std::string HOW_TO_PLAY_BUTTON;
	static const std::string CONTROLS_BUTTON;

	static const std::string OPEN_NODE;
	static const std::string CLOSED_NODE;

	static const std::string EMPTY_TILE;
	static const std::string GRASS_TILE;
	static const std::string CLIFF_TILE;

private:
	Texture();
	~Texture();
};
