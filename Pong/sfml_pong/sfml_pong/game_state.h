#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#define DEBUG(s) std::cout<<__FILE__<<":"<<__LINE__<<":"<<s<<std::endl;

//empty base class to be overridden
class current_state
{
private:
	
	virtual void Initialize(sf::RenderWindow *window)
	{

	}

	virtual void Update(sf::RenderWindow *window)
	{

	}

	virtual void Render(sf::RenderWindow *window)
	{

	}

	virtual void Destroy(sf::RenderWindow *window)
	{

	}
	
public:
	bool rend;
	void TemplateMethod(sf::RenderWindow *window)
	{
		Update(window);
		if(rend)
		Render(window);
	}
	friend class game_state;
};

class game_state
{
public:
	game_state()
	{
		this->currentState = NULL;			//initialize current state to null
	}
	void faketmethod()
	{
		if(this->currentState!=NULL)
		this->currentState->TemplateMethod(this->window);
	}
	void CreateWindow(sf::RenderWindow *window)
	{
		this->window = window;				//set the render window
	}

	void ActiveState(current_state *currentState)
	{
		if (this->currentState != NULL)
		{
			this->currentState->Destroy(this->window);//clear the previous state
			this->currentState->rend = false;//cannot render destroyed state
		}
		this->currentState = currentState;
		
		//set the new state
		if (this->currentState != NULL)
		{
			this->currentState->Initialize(this->window);//initialize the current state
			this->currentState->rend =true;		//Enable Render
		}
	}

	void Update()
	{
		if (this->currentState != NULL)
		{
			this->currentState->Update(this->window);		//update the current state
		}
	}

	void Render()
	{
		if (this->currentState != NULL)
		{
			this->currentState->Render(this->window);		//render the current state
		}
	}

	~game_state()
	{
		if (this->currentState != NULL)
		{
			this->currentState->Destroy(this->window);		//destroy the current state
		}
	}
	friend class current_state;
private:
	current_state *currentState;		// p to current state
	sf::RenderWindow *window;			// p to render window
	
};

//Globals
extern game_state gameState;
extern bool closeGame;
extern bool update;
extern bool isServer;
//extern bool pause;