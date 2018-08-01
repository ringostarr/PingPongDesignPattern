#pragma once
#include "game_state.h"
#include <string>

//inherits from current state
class menu_screen : public current_state
{
public:
	//override the current state methods
	void Initialize(sf::RenderWindow *window);
	void Update(sf::RenderWindow *window);
	void Render(sf::RenderWindow *window);
	void Destroy(sf::RenderWindow *window);
private:
	//variables
	sf::Font *font;
	sf::Text *gameText;
	sf::Text *playText;
	sf::Text *quitText;
	sf::Text *hostText;
	sf::Text *joinText;
	sf::Text *setScoreText;
	int pToWin;
	sf::CircleShape *triangle;
	int mainText;
	int dropDownText;
	int textSelected;
	bool upKeyPressed, downKeyPressed, rightArrowPressed, leftArrowPressed, addPressed, subPressed;
	bool dropDownMenu, setScore;
	std::string str;
};