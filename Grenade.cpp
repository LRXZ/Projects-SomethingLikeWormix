#pragma once
#include "Grenade.h"
#include <vector>
#include <cmath>
const float pi = 3.1415926535;

Grenade::Grenade(float vel, float angle, int posX, int posY, float * oldMassOfSin, float * oldMassOfCos, ToDraw& map){
	massOfSin = oldMassOfSin;
	massOfCos = oldMassOfCos;
	grenPrototype.setPosition(posX, posY);
	grenPrototype.setRadius(3);
	grenPrototype.setFillColor(sf::Color(169,169,151));
	velocity = vel;
	angleOfDir = angle;
}


int normalizeAngle(int angle){
	while (angle > 359)
		angle -= 360;
	while (angle < 0)
		angle += 360;

	return angle;
}

float normalizeAngle(float angle){
	while (angle > 359)
		angle -= 360;
	while (angle < 0)
		angle += 360;

	return angle;
}

float Grenade::getSin(int angle)
{
	if (destroy == 1)
		return 2;
	angle = normalizeAngle(angle);
	return massOfSin[angle];
}

float Grenade::getCos(int angle)
{

	if (destroy == 1)
		return 2;
	angle = normalizeAngle(angle);
	return massOfCos[angle];
}


int makeAngleFromVect(sf::Vector2f vect)
{
	int res = 0;
	if ((vect.x > 0) && (vect.y > 0))
	{
		res = (int)abs((atan(abs(vect.x / vect.y))) / pi * 180);
	}
	if ((vect.x > 0) && (vect.y < 0))
	{
		res = 270 + (int)abs((atan(vect.x / vect.y)) / pi * 180);
	}
	if ((vect.x < 0) && (vect.y > 0))
	{
		res = 90 + (int)abs((atan(vect.x / vect.y)) / pi * 180);
	}
	if ((vect.x < 0) && (vect.y < 0))
	{
		res = 180 + (int)abs((atan(vect.x / vect.y)) / pi * 180);
	}

	return res;
}

sf::Vector2f makeVectFromAngle(int angle, float * massOfSin, float * massOfCos)
{
	sf::Vector2f res(0, 0);
	res.x = massOfSin[angle];
	res.y = massOfCos[angle];
	return res;
}

void Grenade::update(ToDraw& map, sf::RenderWindow &window)
{
	if (destroy == 1)
		return;
	if (clock.getElapsedTime().asSeconds() >= 3)
	{
		std::cout << "EXPLOSION" << std::endl;
		explodeGren(map, window);
	}
	if (counterOfBounce > 0)
		counterOfBounce--;
	grenPrototype.move(velocity * getCos(angleOfDir), velocity * getSin(angleOfDir));
	float newAngleOfDir = 180 / pi * atan((float)(0.1 + (float)velocity * sin(angleOfDir / 180 * pi)) / ((float)velocity * cos(angleOfDir / 180 * pi)));
	float newVel = velocity * cos(angleOfDir / 180 * pi) / cos(newAngleOfDir / 180 * pi);
	newAngleOfDir = normalizeAngle(newAngleOfDir);
	angleOfDir = newAngleOfDir;
	velocity = newVel;
	int angleOfBounce = 400;
	if (counterOfBounce == 0)
		angleOfBounce = hasGrenadeBounced(map, window);
	if (angleOfBounce == 500)
	{
		explodeGren(map, window);
	}
	if ((angleOfBounce != 400))
	{		
		angleOfBounce = normalizeAngle(angleOfBounce + 270);
		int resAngle = angleOfDir - 2 * (angleOfDir - angleOfBounce);
		angleOfDir = resAngle;
		velocity *= 0.7;
		counterOfBounce += 5;
	}
}
int Grenade::hasGrenadeBounced(ToDraw& map, sf::RenderWindow &window)
{
	if (destroy == 1)
		return 400;
	int rad = grenPrototype.getRadius();
	if (map.getImage().getPixel(grenPrototype.getPosition().x + rad / 2 ,
		grenPrototype.getPosition().y + rad / 2) != sf::Color::Transparent)
	{
			return 500;
	}
	std::vector<int> Vect;
	int j = 0;
	while (map.getImage().getPixel(grenPrototype.getPosition().x + rad / 2 + rad * 3 * getCos(j),
		grenPrototype.getPosition().y + rad / 2 + rad * 3 * getSin(j)) != sf::Color::Transparent)
	{
		j++;
		if (j > 360)
			break;
	}
	for (int i = j; i < j + 360; i++)
	{
		int x = grenPrototype.getPosition().x + rad / 2 + rad * 3 * getCos(i);
		int y = grenPrototype.getPosition().y + rad / 2 + rad * 3 * getSin(i);

		if (map.getImage().getPixel(x, y) != sf::Color::Transparent)
		{
			Vect.push_back(i);
		}
	}
	if ((Vect.size() < 50) || (Vect.size() > 150))
		return 400;
	int resAng = (Vect[0] + Vect[Vect.size() - 1]) / 2;
	return resAng;
}
void drawCircle(ToDraw& map, int x0, int y0, int r)
{
	for (int x = x0 - r; x < x0 + r; x++)
	{
		for (int y = -sqrt(pow(r, 2) - pow((x - x0), 2)) + y0; y < sqrt(pow(r, 2) - pow((x - x0), 2)) + y0; y++)
		{
			map.getImage().setPixel(x, y, sf::Color::Transparent);
		}
	}
}
void Grenade::explodeGren(ToDraw& map, sf::RenderWindow &window)
{
	int rad = 50;
	int x = grenPrototype.getPosition().x;
	int y = grenPrototype.getPosition().y;

	drawCircle(map, x, y, rad);
	map.update();
	destroy = 1;
}
Grenade::~Grenade() {}
