#pragma once

#include "SFML\Graphics.hpp"
#include "VectorMath.h"
#include "TextureManager.h"

class PlayerInterface
{
public:
	PlayerInterface();
	~PlayerInterface(void);

	//Runs all the update logic for the interface
	void Update(sf::RenderWindow& window);

	//Draws the interface
	void Draw(sf::RenderWindow& window);

	//Enables and Disabled box dragging
	void EnableBoxing();
	void DisableBoxing();

	//Enabled and Disables the custom cursor;
	void EnableCustomCursor(sf::RenderWindow &window);
	void DisableCustomCursor(sf::RenderWindow &window);

	sf::RectangleShape GetSelectionBox();
	bool SelectionBoxIsBeingDragged();

private:

	//If the custom cursor is enabled or not, if not it will just be a reg'lar old windows cursor
	bool customCursorEnabled;
	//if the cursor is being clicked at the mo
	bool cursorBeingClicked;
	sf::Sprite cursor;
	//The uv co-ords for the unclicked/clicked cursors on the texture
	sf::IntRect cursorNormalUV;
	sf::IntRect cursorClickedUV;


	//The actual box shape that is drawn
	sf::RectangleShape selectionBox;

	bool boxingEnabled;
	//The difference between these two is that just clicking shouldnt start the box unless you start dragging properly. Beleive it or not, removing this differentiation causes some subtle graphical bugs when spam clicking and moving.
	bool isDraggingBox;
	bool selectionBoxActive;
	sf::Vector2i boxStartPos;
	//This is the minimum value you need to drag to make the box appear
	float minimumBoxDragDistance;


	void HandleSelectionBoxDrags(sf::RenderWindow &window);
	void HandleCustomCursor(sf::RenderWindow &window);

};

