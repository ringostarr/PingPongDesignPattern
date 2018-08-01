#include "score.h"
#include <iostream>
score::score(sf::Font &font, unsigned int size) : sf::Text("score: 0", font, size)
{
	this->count = 0;
}

void score::AddScore()
{
	this->count += 1;
}

void score::Update()
{
	this->setString("score: " + std::to_string(this->count));
}