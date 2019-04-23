#pragma once
# include "ListOfWeapons.h"
# include "Worm.h"
const float pi = 3.1415926535;

ListOfWeapons::ListOfWeapons() {
	massOfSin = new float[360];
	for (int i = 0; i < 360; i++)
	{
		massOfSin[i] = sin((float)i / 360 * 2 * pi);
	}
	massOfCos = new float[360];
	for (int i = 0; i < 360; i++)
	{
		massOfCos[i] = cos((float)i / 360 * 2 * pi);
	}
	//std::cout << "sin 0 = " << massOfSin[0] << std::endl;	
}

float ListOfWeapons::getSin(int angle)
{
	while (angle > 359)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return massOfSin[angle];
}

float ListOfWeapons::getCos(int angle)
{
	while (angle > 359)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return massOfCos[angle];
}


void ListOfWeapons::throwGrenade(float vel, float angle, int posX, int posY, ToDraw& map)
{
	grenade = new Grenade(vel, angle, posX, posY, massOfSin, massOfCos, map);

	
//	std::cout << "_gren  pos.x y  "<< _grenade->grenPrototype.getPosition().x << _grenade->grenPrototype.getPosition().y << std::endl;

}




ListOfWeapons::~ListOfWeapons()
{
	free(massOfSin);
}
