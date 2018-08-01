#pragma once
#include "player.h"
#include "score.h"

class ball : public entity
{
public:
	ball(player *player1, player *player2, score *p1Score, score *p2Score);
	void Update(sf::RenderWindow *window);
private:
	player *player1;
	player *player2;
	score *p1Score;
	score *p2Score;
};