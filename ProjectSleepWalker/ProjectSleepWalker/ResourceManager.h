#pragma once

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <map>

// Toggles debug couts
#define DEBUG_RESOURCE_MANAGER true

/**
	RESOURCE MANAGER CLASS
	----------------------
	This class ensures each resource is only loaded and created once.
	This class should not be instantiated as it is intended to work statically.
*/
class ResourceManager
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

	// References
	static const std::string OPTIONS_BACKGROUND_TEXTURE;	
	static const std::string HELP_BACKGROUND_TEXTURE;		
	static const std::string MENU_BACKGROUND_TEXTURE;		

	static const std::string PLAY_BUTTON_TEXTURE;
	static const std::string QUIT_BUTTON_TEXTURE;
	static const std::string HELP_BUTTON_TEXTURE;
	static const std::string OPTIONS_BUTTON_TEXTURE;
	static const std::string BACK_BUTTON_TEXTURE;
	static const std::string DISPLAY_BUTTON_TEXTURE;
	static const std::string AUDIO_BUTTON_TEXTURE;
	static const std::string HOW_TO_PLAY_BUTTON_TEXTURE;
	static const std::string CONTROLS_BUTTON_TEXTURE;

	static const std::string OPEN_NODE_TEXTURE;
	static const std::string CLOSED_NODE_TEXTURE;

	static const std::string EMPTY_TILE_TEXTURE;
	static const std::string GRASS_TILE_TEXTURE;
	static const std::string CLIFF_TILE_TEXTURE;

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
	ResourceManager();
	~ResourceManager();
};
