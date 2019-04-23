#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grenade.h"
class ListOfWeapons
{
private:
public:
	int posOfWormX;
	int posOfWormY;
	Grenade* grenade;
	ListOfWeapons();
	void throwGrenade(float vel, float angle, int posX, int posY, ToDraw& map);
	~ListOfWeapons();

	float * massOfCos;
	float * massOfSin;
	float getSin(int angle);
	float getCos(int angle);

};

