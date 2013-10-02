#include "TextureManager.h"

const std::string Texture::OPTIONS_BACKGROUND =	"../Assets/Images/States/Options/OptionsBackground.jpg";
const std::string Texture::HELP_BACKGROUND = "../Assets/Images/States/Help/HelpBackground.jpg";
const std::string Texture::MENU_BACKGROUND = "../Assets/Images/States/Menu/MenuBackground.jpg";

const std::string Texture::PLAY_BUTTON = "../Assets/Images/States/Menu/PlayButton.jpg";
const std::string Texture::QUIT_BUTTON = "../Assets/Images/States/Menu/QuitButton.jpg";
const std::string Texture::HELP_BUTTON = "../Assets/Images/States/Menu/HelpButton.jpg";
const std::string Texture::OPTIONS_BUTTON = "../Assets/Images/States/Menu/OptionsButton.jpg";
const std::string Texture::BACK_BUTTON = "../Assets/Images/States/BackButton.jpg";
const std::string Texture::DISPLAY_BUTTON = "../Assets/Images/States/Options/DisplayButton.jpg";
const std::string Texture::AUDIO_BUTTON = "../Assets/Images/States/Options/AudioButton.jpg";
const std::string Texture::HOW_TO_PLAY_BUTTON = "../Assets/Images/States/Help/ControlsButton.jpg";
const std::string Texture::CONTROLS_BUTTON = "../Assets/Images/States/Help/HowToPlayButton.jpg";

const std::string Texture::OPEN_NODE = "../Assets/Images/DebugImages/OpenNode.png";
const std::string Texture::CLOSED_NODE = "../Assets/Images/DebugImages/ClosedNode.png";

const std::string Texture::EMPTY_TILE = "../Assets/Images/Tiles/EmptyTile.png";
const std::string Texture::GRASS_TILE = "../Assets/Images/Tiles/Grass.png";
const std::string Texture::CLIFF_TILE = "../Assets/Images/Tiles/Cliff.png";

// Empty hash map initially
std::map<std::string, sf::Texture*> TextureManager::textureMap;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

Texture::Texture()
{
}

Texture::~Texture()
{
}

void TextureManager::Close()
{
	if(!textureMap.empty())
	{
		textureMap.clear();
	}

	if(DEBUG_TEXTURE_MANAGER)
	{
		std::cout << "Texture map cleared." << std::endl;
	}
}

bool TextureManager::LoadTexture(std::string filepath)
{
	// Entry not found
	if(textureMap.find(filepath) == textureMap.end())
	{
		return CreateTexture(filepath);
	}

	if(DEBUG_TEXTURE_MANAGER)
	{
		std::cout << "Texture could not be loaded: Texture already exists in texture map." << std::endl;
	}
	return false;
}

bool TextureManager::RemoveTexture(std::string filepath)
{
	// Entry found
	if(textureMap.find(filepath) != textureMap.end())
	{
		textureMap.erase(filepath);
		
		if(DEBUG_TEXTURE_MANAGER)
		{
			std::cout << "Texture successfully removed from texture map." << std::endl;
		}
		return true;
	}

	if(DEBUG_TEXTURE_MANAGER)
	{
		std::cout << "Cannot remove texture: Texture does not exist in the texture map." << std::endl;
	}
	return false;
}

sf::Texture& TextureManager::GetTexture(std::string filepath)
{
	// Entry not found
	if(textureMap.find(filepath) == textureMap.end())
	{
		CreateTexture(filepath);
	}

	return *textureMap.at(filepath);
}

bool TextureManager::CreateTexture(std::string filepath)
{
	// Texture load
	sf::Texture* texture = new sf::Texture();
	if(!texture->loadFromFile(filepath))
	{
		if(DEBUG_TEXTURE_MANAGER)
		{
			std::cout << "TextureManager::CreateTexture() error: Texture failed to load." << std::endl;
		}
		return false;
	}

	textureMap.insert(std::pair<std::string, sf::Texture*>(filepath, texture));

	if(DEBUG_TEXTURE_MANAGER)
	{
		std::cout << "Texture successfully loaded and stored in texture map." << std::endl;
	}
	return true;
}
