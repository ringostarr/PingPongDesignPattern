#include "player.h"
#include <iostream>
bool update = false;

player::player(int playerNum)
{
	this->playerNum = playerNum;
	switch (this->playerNum)
	{
	case 1:
		this->LoadGraphic("player1.png");
		break;
	case 2:
		this->LoadGraphic("player2.png");
	}
}

void player::Update(sf::RenderWindow *window)
{
	if (update)
	{
		switch (this->playerNum)
		{
		case 1:
			this->speed.y = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) * 100.0f;
			break;
		default:
			break;
		}

		entity::Update();
		
		if (this->getPosition().y < 0)
		{
			this->move(0, 1.0f);
		}

		if (this->getPosition().y + this->getGlobalBounds().height > 600)
		{
			this->move(0, -1.0f);
		}
	}
}