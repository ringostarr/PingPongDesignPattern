#pragma once
#include "game_state.h"
#include "menu_screen.h"
#include <string>
#include <iostream>
class end_screen : public current_state
{
public:
	end_screen(std::string str);
	void Initialize(sf::RenderWindow *window);
	void Update(sf::RenderWindow *window);
	void Render(sf::RenderWindow *window);
	void Destroy(sf::RenderWindow *window);
private:
	sf::Font *font;
	sf::Text *winText;
	sf::Text *mainMenuText;
	sf::Text *quitText;
	std::string str;
	int textSelected;
	bool upKeyPressed, downKeyPressed;
};