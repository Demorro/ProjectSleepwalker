#include "PlayerInterface.h"
#include "Application.h"


PlayerInterface::PlayerInterface()
{
	//Cursor stuff
	cursorNormalUV = sf::IntRect(0,0,32,32);
	cursorClickedUV = sf::IntRect(32,0,32,32);
	cursor.setTexture(TextureManager::GetTexture(Texture::CURSOR));
	cursor.setTextureRect(cursorNormalUV);
	customCursorEnabled = true;
	cursorBeingClicked = false;
	EnableCustomCursor(Application::GetWindow());

	//Boxing stuff
	boxingEnabled = true;
	isDraggingBox = false;
	minimumBoxDragDistance = 5.0f;
	selectionBoxActive = false;
	selectionBox.setOutlineThickness(1);
	selectionBox.setOutlineColor(sf::Color::White);
	selectionBox.setFillColor(sf::Color::Transparent);
}

PlayerInterface::~PlayerInterface(void)
{
}

void PlayerInterface::Update(sf::RenderWindow& window)
{
	HandleCustomCursor(window);
	HandleSelectionBoxDrags(window);
}

void PlayerInterface::Draw(sf::RenderWindow& window)
{
	//only render the box if it is active
	if((selectionBoxActive) && (boxingEnabled))
	{
		window.draw(selectionBox);
	}
	if(customCursorEnabled)
	{
		window.draw(cursor);
	}
}

void PlayerInterface::HandleSelectionBoxDrags(sf::RenderWindow& window)
{
	if(boxingEnabled)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (isDraggingBox == false))
		{
			boxStartPos = sf::Mouse::getPosition(window);
			isDraggingBox = true;
			selectionBox.setPosition((float)boxStartPos.x,(float)boxStartPos.y);
		}
		//you are dragging the box if the mouse is down, but the box isnt active until you have moved a certain distance
		else if(isDraggingBox == true)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			//So the box only appears after a minimum distance has been dragged, to stop it appearing on clicks.
			if(VectorDistance(boxStartPos,mousePos) > minimumBoxDragDistance)
			{
				selectionBoxActive = true;
				//Do the sizing of the box
				selectionBox.setSize(sf::Vector2f(mousePos.x - boxStartPos.x, mousePos.y - boxStartPos.y));
			}
		}

		//Check for mouseup
		if(isDraggingBox)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
			{
				isDraggingBox = false;
				selectionBoxActive = false;
			}
		}
	}
}

void PlayerInterface::EnableBoxing()
{
	boxingEnabled = true;
}

void PlayerInterface::DisableBoxing()
{
	boxingEnabled = false;
}

void PlayerInterface::HandleCustomCursor(sf::RenderWindow &window)
{
	if(customCursorEnabled)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		cursor.setPosition(mousePos.x,mousePos.y);

		if(cursorBeingClicked == false)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				cursor.setTextureRect(cursorClickedUV);
				cursorBeingClicked = true;
			}
		}
		else if(cursorBeingClicked == true)
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
			{
				cursor.setTextureRect(cursorNormalUV);
				cursorBeingClicked = false;
			}
		}
	}
}

void PlayerInterface::EnableCustomCursor(sf::RenderWindow &window)
{
	customCursorEnabled = true;
	window.setMouseCursorVisible(false);
}

void PlayerInterface::DisableCustomCursor(sf::RenderWindow &window)
{
	customCursorEnabled = false;
	window.setMouseCursorVisible(true);
}