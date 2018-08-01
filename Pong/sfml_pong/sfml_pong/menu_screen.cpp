#include "menu_screen.h"
#include "game_screen.h"
#include <iostream>

bool isServer = false;

void menu_screen::Initialize(sf::RenderWindow *window)
{
	//initialize font
	this->font = new sf::Font();
	this->font->loadFromFile("Fonts/CarterOne.ttf");
	
	//initialize and set the game text
	this->gameText = new sf::Text("pong", *this->font, 200U);
	this->gameText->setOrigin(this->gameText->getGlobalBounds().width / 2, this->gameText->getGlobalBounds().height / 2);
	this->gameText->setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 8);

	//initialize and set the play text
	this->playText = new sf::Text("play", *this->font, 64U);
	this->playText->setOrigin(this->playText->getGlobalBounds().width / 2, this->playText->getGlobalBounds().height / 2);
	this->playText->setPosition((float)window->getSize().x / 6, (float)window->getSize().y / 2);

	//initialize and set the host text
	this->hostText = new sf::Text("host", *this->font, 64U);
	this->hostText->setOrigin(this->hostText->getGlobalBounds().width / 2, this->hostText->getGlobalBounds().height / 2);
	this->hostText->setPosition((float)window->getSize().x / 2.5f, (float)window->getSize().y / 2);

	//initialize and set the join text
	this->joinText = new sf::Text("join", *this->font, 64U);
	this->joinText->setOrigin(this->hostText->getGlobalBounds().width / 2, this->hostText->getGlobalBounds().height / 2);
	this->joinText->setPosition((float)window->getSize().x / 2.5f, (float)window->getSize().y / 2 + (this->hostText->getGlobalBounds().height * 1.5f));

	//initialize and set the host text
	this->quitText = new sf::Text("quit", *this->font, 64U);
	this->quitText->setOrigin(this->quitText->getGlobalBounds().width / 2, this->quitText->getGlobalBounds().height / 2);
	this->quitText->setPosition((float)window->getSize().x / 6, (float)window->getSize().y / 2 + (this->playText->getGlobalBounds().height * 1.5f));
	
	//set points to win
	this->pToWin = 0;
	//initialize and set the score text
	this->setScoreText = new sf::Text("set score: "+ std::to_string(this->pToWin), *this->font, 32U);
	this->setScoreText->setOrigin(this->setScoreText->getGlobalBounds().width / 2, this->setScoreText->getGlobalBounds().height / 2);
	this->setScoreText->setPosition((float)window->getSize().x / 2.0f + this->hostText->getGlobalBounds().width, (float)window->getSize().y / 2 + 10.0f);

	//create triangle for drop down menu
	this->triangle = new sf::CircleShape;
	this->triangle->setPointCount(3);
	this->triangle->setRadius(15);
	this->triangle->setPosition((float)window->getSize().x / 6 + this->playText->getGlobalBounds().width / 1.4f, (float)window->getSize().y / 2);
	this->triangle->setRotation(90.0f);
	//set variables
	this->dropDownMenu = false;
	this->setScore = false;
	this->str = "";
}

void menu_screen::Update(sf::RenderWindow *window)
{
	if (!update)
		return;

	if (!dropDownMenu)
	{
		//scroll between play and quit
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !this->upKeyPressed)
			this->mainText -= 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !this->downKeyPressed)
			this->mainText += 1;

		if (this->mainText < 0)
			this->mainText = 1;
		else if (this->mainText > 1)
			this->mainText = 0;
	}
	else
	{
		//scroll between host and join(client)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !this->upKeyPressed)
			this->dropDownText -= 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !this->downKeyPressed)
			this->dropDownText += 1;

		if (this->dropDownText > 1)
			this->dropDownText = 0;
		else if (this->dropDownText < 0)
			this->dropDownText = 1;
	}

	//activate drop down menu
	if (this->mainText == 0 && this->rightArrowPressed)
	{
		this->dropDownMenu = true;
		this->dropDownText = 0;
		this->triangle->setFillColor(sf::Color::Blue);
		//this->rightArrowPressed = false;
	}

	//de-activate drop down menu
	if (this->leftArrowPressed)
	{
		this->dropDownMenu = false;
		this->triangle->setFillColor(sf::Color::White);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		if (!dropDownMenu)
		{
			switch (this->mainText)
			{
			case 0:
				break;
			case 1:
				closeGame = true;			//close the window
				break;
			}
		}
		else
		{
			switch (this->dropDownText)
			{
			case 0:
				isServer = true;
				gameState.ActiveState(new game_screen(this->pToWin));	//change state to game screen
				return;
				break;
			case 1:
				isServer = false;
				gameState.ActiveState(new game_screen(this->pToWin));	//change state to game screen
				return;
				break;
			}
		}
	}

	if (this->setScore)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) && !this->addPressed)
		{
			//add score to win
			this->pToWin += 1;
			//update score to win onto screen
			this->setScoreText->setString("set score: " + std::to_string(this->pToWin));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) && !this->subPressed)
		{
			//reduce score to win
			this->pToWin -= 1;
			if (this->pToWin < 0)
				this->pToWin = 0;
			//update score to win onto screen
			this->setScoreText->setString("set score: " + std::to_string(this->pToWin));
		}
	}
	//check for keyboard input
	this->upKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	this->downKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
	this->rightArrowPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
	this->leftArrowPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
	this->addPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T);
	this->subPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G);
}

void menu_screen::Render(sf::RenderWindow *window)
{
	
	//set text fill color to white(not selected)
	
	this->playText->setFillColor(sf::Color::White);
	this->quitText->setFillColor(sf::Color::White);
	this->hostText->setFillColor(sf::Color::White);
	this->joinText->setFillColor(sf::Color::White);
	switch (this->mainText)
	{
	case 0:
		this->playText->setFillColor(sf::Color::Blue);		//set play text to blue when selected
		break;
	case 1:
		this->quitText->setFillColor(sf::Color::Blue);		//set quit text to blue when selected
		break;
	}

	switch (this->dropDownText)
	{
	case 0:
		this->setScore = true;
		this->hostText->setFillColor(sf::Color::Blue);		//set host text to blue when selected
		break;
	case 1:
		this->setScore = false;
		this->joinText->setFillColor(sf::Color::Blue);		//set join text to blue when selected 
		break;
	}
	//draw the text onto the screen
	window->draw(*this->gameText);
	window->draw(*this->playText);
	window->draw(*this->quitText);
	if (this->dropDownMenu)
	{
		window->draw(*this->hostText);
		window->draw(*this->joinText);
		if (this->setScore)
		{
			//std::cout << "draw score" << std::endl;
			window->draw(*this->setScoreText);
		}
	}
	window->draw(*this->triangle);
}

void menu_screen::Destroy(sf::RenderWindow *window)
{
	//clear memory
	delete this->font;
	delete this->gameText;
	delete this->playText;
	delete this->quitText;
	delete this->hostText;
	delete this->joinText;
	delete this->triangle;
	this->rend = false;
}