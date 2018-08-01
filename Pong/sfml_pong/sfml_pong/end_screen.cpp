#include "end_screen.h"

end_screen::end_screen(std::string str)
{
	this->str = str;
}

void end_screen::Initialize(sf::RenderWindow *window)
{
	this->font = new sf::Font();
	this->font->loadFromFile("Fonts/CarterOne.ttf");

	this->winText = new sf::Text(" ", *this->font, 64U);
	this->winText->setOrigin(this->winText->getGlobalBounds().width / 2, this->winText->getGlobalBounds().height / 2);
	this->winText->setPosition((float)window->getSize().x / 6, (float)window->getSize().y / 2);

	this->mainMenuText = new sf::Text("main menu", *this->font, 32U);
	this->mainMenuText->setOrigin(this->mainMenuText->getGlobalBounds().width / 2, this->mainMenuText->getGlobalBounds().height / 2);
	this->mainMenuText->setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 1.5f);

	this->quitText = new sf::Text("quit", *this->font, 32U);
	this->quitText->setOrigin(this->quitText->getGlobalBounds().width / 2, this->quitText->getGlobalBounds().height / 2);
	this->quitText->setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 1.4f + this->mainMenuText->getGlobalBounds().height);

	this->textSelected = 0;
}

void end_screen::Update(sf::RenderWindow *window)
{
	if (!update)
		return;

	this->winText->setString(str + " has won");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !this->upKeyPressed)
		this->textSelected -= 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !this->downKeyPressed)
		this->textSelected += 1;

	if (this->textSelected > 1)
		this->textSelected = 0;
	else if (this->textSelected < 0)
		this->textSelected = 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		switch (this->textSelected)
		{
		case 0:
			gameState.ActiveState(new menu_screen());
			return;
			break;
		case 1:
			closeGame = true;
			return;
			break;
		}
	}

	this->upKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	this->downKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
}

void end_screen::Render(sf::RenderWindow *window)
{
	this->mainMenuText->setFillColor(sf::Color::White);
	this->quitText->setFillColor(sf::Color::White);
	switch (this->textSelected)
	{
	case 0:
		this->mainMenuText->setFillColor(sf::Color::Blue);
		break;
	case 1:
		this->quitText->setFillColor(sf::Color::Blue);
		break;
	}
	window->draw(*this->winText);
	window->draw(*this->mainMenuText);
	window->draw(*this->quitText);
}

void end_screen::Destroy(sf::RenderWindow *window)
{
	delete this->font;
	delete this->winText;
	delete this->mainMenuText;
	delete this->quitText;
	this->rend = false;
}