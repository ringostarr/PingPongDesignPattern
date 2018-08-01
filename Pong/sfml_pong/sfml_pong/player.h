#pragma once
#include "entity.h"

class player : public entity
{
public:
	player(int playerNum);
	void Update(sf::RenderWindow *window);
private:
	int playerNum;
};