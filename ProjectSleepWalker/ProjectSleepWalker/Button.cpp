#include "Button.h"

Button::Button(sf::Texture& buttonTex, sf::RenderWindow& window, const unsigned int BUTTON_WIDTH, const unsigned int BUTTON_HEIGHT) 
	:	BUTTON_WIDTH(BUTTON_WIDTH), BUTTON_HEIGHT(BUTTON_HEIGHT), window(window)
{
	setTexture(buttonTex);
	SetState(BUTTON_DEFAULT);
	active = true;
	prevState = BUTTON_DEFAULT;
}

Button::~Button()
{
}

void Button::SetState(Button::ButtonState state)
{
	if(state != prevState)
	{
		int start = (int)state;
		const sf::IntRect texRect(start * BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
		setTextureRect(texRect);

		prevState = state;
	}
}

void Button::Update(sf::Mouse::Button mouseButton)
{
	if(active)
	{
		if(Over())
		{
			if(Down(mouseButton))
			{
				SetState(BUTTON_DOWN);
			}
			else if(Up(mouseButton))
			{
				SetState(BUTTON_UP);
			}
			else
			{
				SetState(BUTTON_OVER);
			}
		}
		else
		{
			SetState(BUTTON_DEFAULT);
		}
	}
	else
	{
		SetState(BUTTON_DISABLED);
	}
}

bool Button::Up(sf::Mouse::Button mouseButton)
{
	if(Over())
	{
		if(!Down(mouseButton))
		{
			if(prevState == BUTTON_DOWN)
			{
				return true;
			}
		}
	}

	return false;
}

bool Button::Over()
{
	if(getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
	{
		return true;
	}

	return false;
}

bool Button::Down(sf::Mouse::Button mouseButton)
{
	if(Over())
	{
		if(sf::Mouse::isButtonPressed(mouseButton))
		{
			return true;
		}
	}

	return false;
}

bool Button::Pressed(sf::Mouse::Button mouseButton)
{
	if(Up(mouseButton))
	{
		return true;
	}

	return false;
}

void Button::Enable()
{
	if(!active)
	{
		active = true;
		SetState(BUTTON_DEFAULT);
	}
}

void Button::Disable()
{
	if(active)
	{
		active = false;
		SetState(BUTTON_DISABLED);
	}
}
