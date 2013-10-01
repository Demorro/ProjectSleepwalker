#include "ResourceManager.h"

const std::string ResourceManager::OPTIONS_BACKGROUND_TEXTURE =	"../Assets/Images/States/Options/OptionsBackground.jpg";
const std::string ResourceManager::HELP_BACKGROUND_TEXTURE = "../Assets/Images/States/Help/HelpBackground.jpg";
const std::string ResourceManager::MENU_BACKGROUND_TEXTURE = "../Assets/Images/States/Menu/MenuBackground.jpg";

const std::string ResourceManager::PLAY_BUTTON_TEXTURE = "../Assets/Images/States/Menu/PlayButton.jpg";
const std::string ResourceManager::QUIT_BUTTON_TEXTURE = "../Assets/Images/States/Menu/QuitButton.jpg";
const std::string ResourceManager::HELP_BUTTON_TEXTURE = "../Assets/Images/States/Menu/HelpButton.jpg";
const std::string ResourceManager::OPTIONS_BUTTON_TEXTURE = "../Assets/Images/States/Menu/OptionsButton.jpg";
const std::string ResourceManager::BACK_BUTTON_TEXTURE = "../Assets/Images/States/BackButton.jpg";
const std::string ResourceManager::DISPLAY_BUTTON_TEXTURE= "../Assets/Images/States/Options/DisplayButton.jpg";
const std::string ResourceManager::AUDIO_BUTTON_TEXTURE= "../Assets/Images/States/Options/AudioButton.jpg";
const std::string ResourceManager::HOW_TO_PLAY_BUTTON_TEXTURE= "../Assets/Images/States/Help/ControlsButton.jpg";
const std::string ResourceManager::CONTROLS_BUTTON_TEXTURE= "../Assets/Images/States/Help/HowToPlayButton.jpg";

const std::string ResourceManager::OPEN_NODE_TEXTURE = "../Assets/Images/DebugImages/OpenNode.png";
const std::string ResourceManager::CLOSED_NODE_TEXTURE = "../Assets/Images/DebugImages/ClosedNode.png";

const std::string ResourceManager::EMPTY_TILE_TEXTURE = "../Assets/Images/Tiles/EmptyTile.png";
const std::string ResourceManager::GRASS_TILE_TEXTURE = "../Assets/Images/Tiles/Grass.png";
const std::string ResourceManager::CLIFF_TILE_TEXTURE = "../Assets/Images/Tiles/Cliff.png";

// Empty hash map initially
std::map<std::string, sf::Texture*> ResourceManager::textureMap;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Close()
{
	if(!textureMap.empty())
	{
		textureMap.clear();
	}

	if(DEBUG_RESOURCE_MANAGER)
	{
		std::cout << "Texture map cleared." << std::endl;
	}
}

bool ResourceManager::LoadTexture(std::string filepath)
{
	// Entry not found
	if(textureMap.find(filepath) == textureMap.end())
	{
		return CreateTexture(filepath);
	}

	if(DEBUG_RESOURCE_MANAGER)
	{
		std::cout << "Texture could not be loaded: Texture already exists in texture map." << std::endl;
	}
	return false;
}

bool ResourceManager::RemoveTexture(std::string filepath)
{
	// Entry found
	if(textureMap.find(filepath) != textureMap.end())
	{
		textureMap.erase(filepath);
		
		if(DEBUG_RESOURCE_MANAGER)
		{
			std::cout << "Texture successfully removed from texture map." << std::endl;
		}
		return true;
	}

	if(DEBUG_RESOURCE_MANAGER)
	{
		std::cout << "Cannot remove texture: Texture does not exist in the texture map." << std::endl;
	}
	return false;
}

sf::Texture& ResourceManager::GetTexture(std::string filepath)
{
	// Entry not found
	if(textureMap.find(filepath) == textureMap.end())
	{
		CreateTexture(filepath);
	}

	return *textureMap.at(filepath);
}

bool ResourceManager::CreateTexture(std::string filepath)
{
	// Texture load
	sf::Texture* texture = new sf::Texture();
	if(!texture->loadFromFile(filepath))
	{
		if(DEBUG_RESOURCE_MANAGER)
		{
			std::cout << "ResourceManager::CreateTexture() error: Texture failed to load." << std::endl;
		}
		return false;
	}

	textureMap.insert(std::pair<std::string, sf::Texture*>(filepath, texture));

	if(DEBUG_RESOURCE_MANAGER)
	{
		std::cout << "Texture successfully loaded and stored in texture map." << std::endl;
	}
	return true;
}
