#include "game_state.h"
#include "menu_screen.h"

game_state gameState;
bool closeGame;
//bool pause = false;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "pong");
	gameState.CreateWindow(&window);
	gameState.ActiveState(new menu_screen());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::GainedFocus)
				update = true;
			else if (event.type == sf::Event::LostFocus)
				update = false;
		}
		window.clear(sf::Color::Black);
		//gameState.Update();
		//gameState.Render();
		gameState.faketmethod();
		window.display();

		if (closeGame)
		{
			window.close();
		}
	}

	return 0;
}