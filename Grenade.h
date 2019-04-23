#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ToDraw.h"

class Grenade
{
private:
public:
	sf::Clock clock;
	float getSin(int angle);
	float getCos(int angle);
	float velocity;
	float angleOfDir;
	sf::CircleShape dot;
	float * massOfCos;
	float * massOfSin;
	sf::CircleShape grenPrototype;
	Grenade(float vel, float angle, int posX, int posY, float * massOfSin,
		float * massOfCos, ToDraw& map);
	void update(ToDraw &map, sf::RenderWindow &window);
	int hasGrenadeBounced(ToDraw& map, sf::RenderWindow &window);
	void explodeGren(ToDraw &ToDraw, sf::RenderWindow &window);
	bool destroy = 0;
	int counterOfBounce = 0;
	~Grenade();
};

