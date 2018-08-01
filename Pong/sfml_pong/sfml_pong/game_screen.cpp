#include "game_screen.h"

void game_screen::Initialize(sf::RenderWindow *window)
{	

	this->ip = sf::IpAddress::getLocalAddress();		//set ip address to the local ip
	//initialize network variables
	this->listener = new sf::TcpListener();								
	this->tcpSocket = new sf::TcpSocket();
	this->packet = new sf::Packet();
	this->tcpSocket->setBlocking(false);				//set socket to non-blocking mode

	//initialize font
	this->font = new sf::Font();
	this->font->loadFromFile("Fonts/CarterOne.ttf");

	//initialize and set wait text
	this->waitText = new sf::Text("waiting for other players", *this->font, 64U);
	this->waitText->setOrigin(this->waitText->getGlobalBounds().width / 2, this->waitText->getGlobalBounds().height / 2);
	this->waitText->setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);

	this->waitingDot = new sf::CircleShape();
	this->waitingDot->setRadius(10.0f);
	this->waitingDot->setFillColor(sf::Color::Blue);
	this->waitingDot->setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2 + this->waitText->getGlobalBounds().height);

	this->p1Score = new score(*this->font, 32U);
	this->p2Score = new score(*this->font, 32U);
	this->p2Score->setPosition((float)window->getSize().x - this->p2Score->getGlobalBounds().width, 0);

	if (!isServer)
	{
		this->status = this->tcpSocket->connect(ip, 2000);
	}

	this->player1 = new player(1);
	this->player1->setPosition(0, window->getSize().y / 2 - this->player1->getGlobalBounds().height / 2);
	this->player2 = new player(2);
	this->player2->setPosition(window->getSize().x - this->player2->getGlobalBounds().width, window->getSize().y / 2 - this->player2->getGlobalBounds().height / 2);
	this->ballObj = new ball(this->player1, this->player2, this->p1Score, this->p2Score);
	this->ballObj->setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);

	this->timer = 0;
	this->once = false;
	//this->pToWin = 0;
	this->c_pToWin = -1;
	this->dt = new sf::Time();
	this->clock = new sf::Clock();
	this->fixedDeltaTime = new sf::Time(sf::seconds(1.0f / 60.0f));

	this->c_p1 = 0;
	this->c_p2 = 0;
}

void game_screen::Update(sf::RenderWindow *window)
{
	/*if (!this->pause)
	{
		this->prevPosition = this->player1->getPosition();
		this->player1->Update(window);
		this->player2->Update(window);
	}*/
	this->prevPosition = this->player1->getPosition();
	this->player1->Update(window);
	this->player2->Update(window);
	this->dt = &this->clock->restart();
	//DEBUG(this->dt.asMilliseconds());
	//this->fpsText->setString("fps: " + std::to_string(this->dt->asMilliseconds()));

	if (isServer)
	{
		ServerUpdate(window);
		//this->fps = getFps(this->clock.restart());
		//this->fpsText->setString("fps: " + std::to_string(this->fps));
		//this->fps = getFps(this->clock.restart());
	}
	else
	{
		ClientUpdate(window);
		//this->fps = getFps(this->clock.restart());
		//this->fpsText->setString("fps: " + std::to_string(this->fps));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && update)
	{
		gameState.ActiveState(new menu_screen());
	}
}

void game_screen::Render(sf::RenderWindow *window)
{
	if (this->clientHasConnected)
	{
		window->draw(*this->player1);
		window->draw(*this->player2);
		window->draw(*this->ballObj);
		window->draw(*this->p1Score);
		window->draw(*this->p2Score);
		//window->draw(*this->fpsText);
	}
	else
	{
		window->draw(*this->waitText);
		window->draw(*this->waitingDot);
	}
}

void game_screen::ServerUpdate(sf::RenderWindow *window)
{
	if (!clientHasConnected)
	{
		this->listener->setBlocking(false);
		this->dotTimer += this->dt->asSeconds() * 2.0f;
		//std::cout << this->dotTimer << std::endl;
		if (this->dotTimer >= 1.0f && this->dotTimer < 2.0f)
		{
			//std::cout << " 2 and 4" << std::endl;
			this->waitingDot->setPosition((float)window->getSize().x / 2 + 20.0f, (float)window->getSize().y / 2 + this->waitText->getGlobalBounds().height);
			//this->waitingDot->setFillColor(sf::Color(0, 0, 255U, 255U));
		}
		else if (this->dotTimer >= 2.0f)
		{
			//std::cout << " greater than 4" << std::endl;
			this->waitingDot->setPosition((float)window->getSize().x / 2 + 40.0f, (float)window->getSize().y / 2 + this->waitText->getGlobalBounds().height);
			//this->waitingDot->setFillColor(sf::Color(0, 0, 255U, 255U));
		}
		else if (this->dotTimer < 1.0f)
		{
			//std::cout << " less than 2" << std::endl;
			this->waitingDot->setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2 + this->waitText->getGlobalBounds().height);
			//this->waitingDot->setFillColor(sf::Color(0, 90U, 255U, 128U));
		}

		if (this->dotTimer >= 3.0f)
		{
			//std::cout << "greater than 6" << std::endl;
			this->dotTimer = 0;
		}
		if (this->listener->listen(2000) != sf::Socket::Done)
		{
			//std::cout << "listening failed" << std::endl;
		}

		if (this->listener->accept(*this->tcpSocket) != sf::Socket::Done)
		{
			//std::cout << "cannot accept client" << std::endl;
		}
		else
		{
			std::cout << "client has connected" << std::endl;
			this->clientHasConnected = true;
		}
	}

	if (clientHasConnected)
	{
		if (!once)
		{
			*this->packet << this->pToWin;
			this->tcpSocket->send(*this->packet);
			DEBUG(this->packet->getDataSize());
			this->packet->clear();
			this->once = true;
		}
		this->p1Count = this->p1Score->count;
		this->p2Count = this->p2Score->count;
		//if(!pause)
		this->ballObj->Update(window);
		this->p1Score->Update();
		this->p2Score->Update();

		/*this->timer += this->fixedDeltaTime->asSeconds();
		this->dirTimer += this->fixedDeltaTime->asSeconds();*/
		this->timer += this->dt->asMilliseconds();
		this->dirTimer += this->dt->asMilliseconds();

		if (this->dirTimer >= 0.1f)
		{
			*this->packet << this->ballObj->speed.x << this->ballObj->speed.y;
			this->tcpSocket->send(*this->packet);
			this->packet->clear();
			this->dirTimer = 0;
		}

		if (this->timer >= 0.1f)
		{
			if (this->prevPosition == this->player1->getPosition() || this->p1Count != this->p1Score->count || this->p2Count != this->p2Score->count)
			{
				*this->packet << this->ballObj->getPosition().x << this->ballObj->getPosition().y << this->p1Score->count << this->p2Score->count;
				this->tcpSocket->send(*this->packet);
				this->packet->clear();
			}
			else if (this->prevPosition != this->player1->getPosition() || this->p1Count != this->p1Score->count || this->p2Count != this->p2Score->count)
			{
				*this->packet << this->player1->getPosition().y << this->ballObj->getPosition().x << this->ballObj->getPosition().y << this->p1Score->count << this->p2Score->count;
				this->tcpSocket->send(*this->packet);
				this->packet->clear();
			}
			this->timer = 0;
		}

		if (this->p1Score->count == this->pToWin)
		{
			*this->packet << this->ballObj->getPosition().x << this->ballObj->getPosition().y << this->p1Score->count << this->p2Score->count;
			this->tcpSocket->send(*this->packet);
			this->packet->clear();
			gameState.ActiveState(new end_screen("player1"));
			return;
		}
		else if (this->p2Score->count == this->pToWin)
		{
			*this->packet << this->ballObj->getPosition().x << this->ballObj->getPosition().y << this->p1Score->count << this->p2Score->count;
			this->tcpSocket->send(*this->packet);
			this->packet->clear();
			gameState.ActiveState(new end_screen("player2"));
			return;
		}
		
		while (true)
		{
			this->data = this->tcpSocket->receive(*packet);
			if (this->data != sf::Socket::Done)
			{
				break;
			}
			//this->tcpSocket->receive(packet);
			if (*packet >> otherPlayerPos)
			{
				this->player2->setPosition(window->getSize().x - this->player2->getGlobalBounds().width, otherPlayerPos);
				this->packet->clear();
			}
		}
	}
}

void game_screen::ClientUpdate(sf::RenderWindow *window)
{
	this->clientHasConnected = true;
	this->c_p1 = this->p1Score->count;
	this->c_p2 = this->p2Score->count;

	if (prevPosition != this->player1->getPosition())
	{
		*this->packet << this->player1->getPosition().y;
		this->tcpSocket->send(*this->packet);
		this->packet->clear();
	}

	this->ballObj->Update(window);
	while (true) 
	{
		this->data = this->tcpSocket->receive(*this->packet);
		if (this->data != sf::Socket::Status::Done)
		{
			break;
		}
		size_t p = this->packet->getDataSize();
		if (p == 4)
		{
			*this->packet >> this->c_pToWin;
			this->packet->clear();
		}

		if (this->c_pToWin <= 0)
			return;

		if (p == 8)
		{
			if (*this->packet >> this->ballDir.x >> this->ballDir.y)
			{
				if (this->ballDir.x > 0 && this->ballDir.y > 0)
				{
					this->ballObj->speed.x = (this->ballDir.x * -1);
					this->ballObj->speed.y = this->ballDir.y;
				}
				else if (this->ballDir.x > 0 && this->ballDir.y < 0)
				{
					this->ballObj->speed.x = (this->ballDir.x * -1);
					this->ballObj->speed.y = this->ballDir.y;
				}
				else if (this->ballDir.x < 0 && this->ballDir.y < 0)
				{
					this->ballObj->speed.x = (this->ballDir.x * -1);
					this->ballObj->speed.y = this->ballDir.y;
				}
				else if (this->ballDir.x < 0 && this->ballDir.y > 0)
				{
					this->ballObj->speed.x = (this->ballDir.x * -1);
					this->ballObj->speed.y = this->ballDir.y;
				}
				this->packet->clear();
			}
		}

		if (p == 16)
		{
			if (*this->packet >> lastBallPos.x >> lastBallPos.y >> temp >> temp2)
			{
				this->lastBallPos.x = window->getSize().x - this->lastBallPos.x;
				this->ballObj->setPosition(lastBallPos);
				this->p2Score->count = temp;
				this->p2Score->Update();
				this->p1Score->count = temp2;
				this->p1Score->Update();
				this->packet->clear();
			}
		}

		if (p > 16)
		{
			if (*this->packet >> otherPlayerPos >> lastBallPos.x >> lastBallPos.y >> temp >> temp2)
			{
				this->player2->setPosition(window->getSize().x - this->player2->getGlobalBounds().width, otherPlayerPos);
				this->lastBallPos.x = window->getSize().x - this->lastBallPos.x;
				this->ballObj->setPosition(lastBallPos);
				this->p2Score->count = temp;
				this->p2Score->Update();
				this->p1Score->count = temp2;
				this->p1Score->Update();
				this->packet->clear();
			}
		}
	}

	if (this->p1Score->count == this->c_pToWin)
	{
	 	this->tcpSocket->disconnect();
		gameState.ActiveState(new end_screen("player1"));
		return;
	}
	else if (this->p2Score->count == this->c_pToWin)
	{
		this->tcpSocket->disconnect();
		gameState.ActiveState(new end_screen("player2"));
		return;
	}
}

float game_screen::getFps(const sf::Time& time)
{
	return(1000000.0f / time.asMicroseconds());
}

void game_screen::Destroy(sf::RenderWindow *window)
{
	delete this->player1;
	delete this->player2;
	delete this->ballObj;
	delete this->fixedDeltaTime;
	delete this->listener;
	delete this->tcpSocket;
	delete this->packet;
	delete this->font;
	delete this->waitingDot;
	delete this->waitText;
	this->rend = false;
}