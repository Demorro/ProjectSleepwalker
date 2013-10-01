#pragma once

#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>

// Macro for quickly accessing the singleton instance
#define resourceManager ResourceManager::GetInstance()

/**
	RESOURCE MANAGER CLASS
	----------------------
	Stores instances of most of the resources used in the application.
	This class ensures each resource is only loaded and created once.
*/
class ResourceManager
{
public:
	/** Returns the singleton instance of the class. */
	static ResourceManager& GetInstance();

	/** 
		Loads all of the resources. Returns true if successful, otherwise returns false.
		This operation can only be called if the resources have not been already loaded.
	*/
	bool Load();

	sf::Texture& GetEmptyGrassTileTex();
	sf::Texture& GetGrassTileTex();
	sf::Texture& GetCliffTileTex();

	sf::Texture& GetOpenNodeTex();
	sf::Texture& GetClosedNodeTex();

	sf::Texture& GetMenuBackgroundTex();
	sf::Texture& GetOptionsBackgroundTex();
	sf::Texture& GetHelpBackgroundTex();

	sf::Texture& GetPlayButtonTex();
	sf::Texture& GetHelpButtonTex();
	sf::Texture& GetOptionsButtonTex();
	sf::Texture& GetQuitButtonTex();
	sf::Texture& GetDisplayButtonTex();
	sf::Texture& GetAudioButtonTex();
	sf::Texture& GetBackButtonTex();

private:
	// Map textures
	sf::Texture emptyTileTex;
	sf::Texture grassTileTex;
	sf::Texture cliffTileTex;

	// Debug map textures
	sf::Texture closedNodeTex;
	sf::Texture openNodeTex;

	// Menu textures
	sf::Texture menuBackgroundTex;
	sf::Texture optionsBackgroundTex;
	sf::Texture helpBackgroundTex;
	sf::Texture playButtonTex;
	sf::Texture helpButtonTex;
	sf::Texture optionsButtonTex;
	sf::Texture quitButtonTex;
	sf::Texture displayButtonTex;
	sf::Texture audioButtonTex;
	sf::Texture backButtonTex;

	// Filepath prefixes
	static const std::string PREFIX;
	static const std::string IMAGES_PREFIX;
	static const std::string TILES_PREFIX;
	static const std::string DEBUG_IMAGES_PREFIX;
	static const std::string STATES_PREFIX;
	static const std::string HELP_PREFIX;
	static const std::string MENU_PREFIX;
	static const std::string OPTIONS_PREFIX;

	/** Determines if the resources have been loaded. */
	bool loaded;

	ResourceManager();
	~ResourceManager();

	/* 
		Should not be implemented in ResourceManager.cpp to ensure that no 
		more than one instance of the ResourceManager class is created. 
	*/
    ResourceManager(ResourceManager const&);
    void operator=(ResourceManager const&);
};
