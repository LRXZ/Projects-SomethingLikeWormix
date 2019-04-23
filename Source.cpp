#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ToDraw.h"
#include "Worm.h"
using namespace sf;
int main() {
	ToDraw map(".../Resourses/map.png");
	ToDraw background(".../Resourses/background.png");
	RenderWindow window (VideoMode(1366, 768), "Wormix");
	window.setFramerateLimit(150);
	Worm Worm (".../Resourses/Demon.png");
	View view;
	Clock clock;
	view.reset(sf::FloatRect(0, 0, 1367, 768));
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
			}
		}
		Worm.update(&time, map, window);
		view.setCenter(Worm.getPosition());
		window.setView(view);
		window.clear();
		window.draw(map.getSprite());
		Worm.drawInWindow(&window, time);
		window.display();
	}
	return 0;
}