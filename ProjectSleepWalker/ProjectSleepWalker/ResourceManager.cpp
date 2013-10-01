#include "ResourceManager.h"

const std::string ResourceManager::PREFIX = "../Assets/";
const std::string ResourceManager::IMAGES_PREFIX = PREFIX + "Images/";
const std::string ResourceManager::TILES_PREFIX = IMAGES_PREFIX + "Tiles/";
const std::string ResourceManager::DEBUG_IMAGES_PREFIX = IMAGES_PREFIX + "DebugImages/";
const std::string ResourceManager::STATES_PREFIX = IMAGES_PREFIX + "States/";
const std::string ResourceManager::HELP_PREFIX = STATES_PREFIX + "Help/";
const std::string ResourceManager::MENU_PREFIX = STATES_PREFIX + "Menu/";
const std::string ResourceManager::OPTIONS_PREFIX = STATES_PREFIX + "Options/";

ResourceManager::ResourceManager()
{
	loaded = false;
}

ResourceManager::~ResourceManager()
{
}

ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager instance;
	return instance;
}

bool ResourceManager::Load()
{
	if(!loaded)
	{
		if(!emptyTileTex.loadFromFile(TILES_PREFIX + "EmptyTile.png"))
		{
			return false;
		}

		if(!grassTileTex.loadFromFile(TILES_PREFIX + "Grass.png"))
		{
			return false;
		}

		if(!cliffTileTex.loadFromFile(TILES_PREFIX + "Cliff.png"))
		{
			return false;
		}

		if(!openNodeTex.loadFromFile(DEBUG_IMAGES_PREFIX + "OpenNode.png"))
		{
			return false;
		}

		if(!closedNodeTex.loadFromFile(DEBUG_IMAGES_PREFIX + "ClosedNode.png"))
		{
			return false;
		}

		if(!menuBackgroundTex.loadFromFile(MENU_PREFIX + "MenuBackground.jpg"))
		{
			return false;
		}

		if(!optionsBackgroundTex.loadFromFile(OPTIONS_PREFIX + "OptionsBackground.jpg"))
		{
			return false;
		}

		if(!helpBackgroundTex.loadFromFile(HELP_PREFIX + "HelpBackground.jpg"))
		{
			return false;
		}

		if(!playButtonTex.loadFromFile(MENU_PREFIX + "PlayButton.jpg"))
		{
			return false;
		}

		if(!helpButtonTex.loadFromFile(MENU_PREFIX + "HelpButton.jpg"))
		{
			return false;
		}

		if(!optionsButtonTex.loadFromFile(MENU_PREFIX + "OptionsButton.jpg"))
		{
			return false;
		}

		if(!quitButtonTex.loadFromFile(MENU_PREFIX + "QuitButton.jpg"))
		{
			return false;
		}

		if(!displayButtonTex.loadFromFile(OPTIONS_PREFIX + "DisplayButton.jpg"))
		{
			return false;
		}

		if(!audioButtonTex.loadFromFile(OPTIONS_PREFIX + "AudioButton.jpg"))
		{
			return false;
		}

		if(!backButtonTex.loadFromFile(STATES_PREFIX + "BackButton.jpg"))
		{
			return false;
		}
	}
	
	loaded = true;
	return loaded;
}

sf::Texture& ResourceManager::GetEmptyGrassTileTex()
{
	return emptyTileTex;
}

sf::Texture& ResourceManager::GetGrassTileTex()
{
	return grassTileTex;
}

sf::Texture& ResourceManager::GetCliffTileTex()
{
	return cliffTileTex;
}

sf::Texture& ResourceManager::GetOpenNodeTex()
{
	return openNodeTex;
}

sf::Texture& ResourceManager::GetClosedNodeTex()
{
	return closedNodeTex;
}

sf::Texture& ResourceManager::GetMenuBackgroundTex()
{
	return menuBackgroundTex;
}

sf::Texture& ResourceManager::GetOptionsBackgroundTex()
{
	return optionsBackgroundTex;
}

sf::Texture& ResourceManager::GetHelpBackgroundTex()
{
	return helpBackgroundTex;
}

sf::Texture& ResourceManager::GetPlayButtonTex()
{
	return playButtonTex;
}

sf::Texture& ResourceManager::GetHelpButtonTex()
{
	return helpButtonTex;
}

sf::Texture& ResourceManager::GetOptionsButtonTex()
{
	return optionsButtonTex;
}

sf::Texture& ResourceManager::GetQuitButtonTex()
{
	return quitButtonTex;
}

sf::Texture& ResourceManager::GetDisplayButtonTex()
{
	return displayButtonTex;
}

sf::Texture& ResourceManager::GetAudioButtonTex()
{
	return audioButtonTex;
}

sf::Texture& ResourceManager::GetBackButtonTex()
{
	return backButtonTex;
}
