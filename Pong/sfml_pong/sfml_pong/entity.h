#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

class entity : public sf::Sprite
{
public:
	sf::Vector2f speed;
	entity()
	{
		this->spriteTexture = new sf::Texture();
		this->fixedDeltaTime = new sf::Time(sf::seconds(1.0f / 120.0f));
		this->dt = new sf::Time();
		this->clock = new sf::Clock();
	}

	void LoadGraphic(std::string filename)
	{
		this->spriteTexture->loadFromFile("Sprites/" + filename);
		this->setTexture(*this->spriteTexture);
	}

	void Update()
	{
		this->dt = &this->clock->restart();
		//this->move(speed * this->fixedDeltaTime->asSeconds());
		this->move(speed * dt->asSeconds());
		//std::cout << this->dt->asSeconds() << std::endl;
	}

	bool CheckCollisionWith(entity *entityObj)
	{
		return this->getGlobalBounds().intersects(entityObj->getGlobalBounds());
	}

	~entity()
	{
		delete this->spriteTexture;
		//delete this->dt;
		//delete this->clock;
		//delete this->fixedDeltaTime;
	}
private:
	sf::Texture *spriteTexture;
	sf::Time *fixedDeltaTime;
	sf::Time *dt;
	sf::Clock *clock;
protected:
	//sf::Vector2f speed;
};