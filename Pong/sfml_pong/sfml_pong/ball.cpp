#include "ball.h"
#include "game_state.h"

ball::ball(player *player1, player *player2, score *p1Score, score *p2Score)
{
	this->LoadGraphic("ball.png");
	this->player1 = player1;
	this->player2 = player2;
	this->p1Score = p1Score;
	this->p2Score = p2Score;
	if (isServer)
	{
		this->speed.x = 150.0f;
		this->speed.y = 150.0f;
	}
	else
	{
		this->speed.x = 0.0f;
		this->speed.y = 0.0f;
	}
}

void ball::Update(sf::RenderWindow *window)
{
	if (this->CheckCollisionWith(this->player1) || this->CheckCollisionWith(this->player2))
	{
		this->speed.x *= -1;			//change ball Xdir after collision
	}

	if (this->getPosition().y < 0 || this->getPosition().y + this->getGlobalBounds().height > window->getSize().y)
	{
		this->speed.y *= -1;			//change ball Ydir
	}

	if (this->getPosition().x < this->player1->getGlobalBounds().width - 20.0f)
	{
		this->p2Score->AddScore();
		this->setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);
	}

	if (this->getPosition().x > window->getSize().x - this->player2->getGlobalBounds().width)
	{
		this->p1Score->AddScore();
		this->setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);
	}
	entity::Update();
}