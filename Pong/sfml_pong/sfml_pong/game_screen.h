#pragma once
#include "game_state.h"
#include "player.h"
#include "ball.h"
#include "score.h"
#include "end_screen.h"
#include "menu_screen.h"
#include <SFML/Network.hpp>
#include <string>
#include <vector>

//inherits from current state
class game_screen : public current_state
{
public:
	game_screen(int pToWin)
	{
		this->pToWin = pToWin;
	}
	//override the current state methods
	void Initialize(sf::RenderWindow *window);
	void Update(sf::RenderWindow *window);
	void Render(sf::RenderWindow *window);
	void Destroy(sf::RenderWindow *window);
private:
	player *player1;
	player *player2;
	ball *ballObj;
	sf::TcpListener *listener;
	sf::TcpSocket *tcpSocket;
	sf::IpAddress ip;
	sf::Socket::Status status;
	sf::Packet *packet;
	sf::Vector2f lastBallPos, prevPosition, ballDir;
	float otherPlayerPos, timer, dotTimer, dirTimer, fps;
	sf::Time *dt;
	sf::Clock *clock;
	sf::Time *fixedDeltaTime;
	bool clientHasConnected;
	sf::Font *font;
	sf::Text *waitText;
	sf::Text *fpsText;
	sf::CircleShape *waitingDot;
	sf::Socket::Status data;
	score *p1Score;
	score *p2Score;
	int p1Count;
	int p2Count;
	int temp, temp2;
	int pToWin;
	int c_pToWin;
	bool once, pKeyPressed;
	int c_p1, c_p2;
	float tempf, tempf2;
	void ServerUpdate(sf::RenderWindow *window);
	void ClientUpdate(sf::RenderWindow *window);
	float getFps(const sf::Time& time);
};