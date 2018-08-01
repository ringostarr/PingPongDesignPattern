#pragma once
#include <SFML/Graphics.hpp>

class score : public sf::Text
{
public:
	score(sf::Font &font, unsigned int size);
	void AddScore();
	void Update();
	int count;
private:
	//int count;
};