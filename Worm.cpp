#pragma once
#include "Worm.h"
#include <iostream>
bool Worm::_wormOnMap(const sf::Vector2f & newPosition, const sf::Image& map)
{
	sf::Vector2f tmp = newPosition + sf::Vector2f(RADIUS - WIDTH_TO_CHECK / 2, RADIUS - HEIGHT_TO_CHECK / 2);
	for (int i = 0; i <= WIDTH_TO_CHECK; i++) {
		tmp += sf::Vector2f(1, 0);
		if (i == 0 || i == RADIUS) {
			for (int j = 0; j <= HEIGHT_TO_CHECK; j++) {
				tmp += sf::Vector2f(0, 1);
				if (map.getPixel(tmp.x, tmp.y) != sf::Color::Transparent) {
					_lastBarrier = (tmp - (newPosition + sf::Vector2f(RADIUS - WIDTH_TO_CHECK / 2, RADIUS - HEIGHT_TO_CHECK / 2)));
					return false;
				}
			}
			tmp -= sf::Vector2f(0, RADIUS);
		}

		if (map.getPixel(tmp.x, tmp.y) != sf::Color::Transparent) {
			_lastBarrier = tmp - (newPosition + sf::Vector2f(RADIUS - WIDTH_TO_CHECK / 2, RADIUS - HEIGHT_TO_CHECK / 2));
			return false;
		}
	}
	return true;
}

 bool Worm::_wormIsFalling(const ToDraw& map) const
{
	if (map.getImage().getPixel(_prototype.getPosition().x + RADIUS, _prototype.getPosition().y + 2 * RADIUS) != sf::Color::Transparent)
		return false;
	else {
		return true;
	}
}

sf::Vector2f Worm::_norm(const sf::Vector2f & toNorm)
{
	return sf::Vector2f(toNorm / sqrt(toNorm.x * toNorm.x + toNorm.y * toNorm.y));
}

Worm::Worm() {

}

Worm::Worm(const std::string & path) {
	_picture = new ToDraw(path);
	_prototype.setRadius(RADIUS);
	_prototype.setPosition(START_POSITION, 0);
	_lastBarrier = sf::Vector2f(0, 1);
}

void Worm::_setStartingVelocity(sf::Vector2f* startingVelocity, const std::string& where)
{
	if (where == "back") {
		if (_isGoingLeft) {
			*startingVelocity = sf::Vector2f(JUMP_BACK_STARTING_SIDE_VELOCITY, JUMP_BACK_STARTING_UP_VELOCITY);
		}
		else {
			*startingVelocity = sf::Vector2f(-JUMP_BACK_STARTING_SIDE_VELOCITY, JUMP_BACK_STARTING_UP_VELOCITY);
		}
	}
	else {
		if (_isGoingLeft) {
			*startingVelocity = sf::Vector2f(-STARTING_SIDE_VELOCITY, STARTING_UP_VELOCITY);
		}
		else {
			*startingVelocity = sf::Vector2f(STARTING_SIDE_VELOCITY, STARTING_UP_VELOCITY);
		}
	}
}

void Worm::_setJumpAction(const std::string& direction, const ToDraw& map){
if (direction == "forward") {
		if (_wormIsFalling(map)) {
			_isJumpingForward = false;
		}
		else {
			_isJumpingForward = true;
		}
	}
	else {
		if (_wormIsFalling(map)) {
			_isJumpingBack = false;
		}
		else {
			_isJumpingBack = true;
		}
	}
}

void Worm::_jump(const ToDraw & map, const std::string& where, float* time) {
	_timeForJumping += *time;
	sf::Vector2f startingVelocity;
	_setStartingVelocity(&startingVelocity, where);
	_velocityForJumping = startingVelocity + sf::Vector2f(0, _timeForJumping / FACTOR_FOR_JUMPING);
	if (_wormOnMap(_prototype.getPosition() + _velocityForJumping, map.getImage())) {
		_prototype.setPosition(_prototype.getPosition() + _velocityForJumping);
		return;
	}
	else {
		_timeForJumping = 0;
		if (where == "back") {
			_isJumpingBack = false;
		}
		else {
			_isJumpingForward = false;
		}
		return;
	}
}

Worm::~Worm() {
	delete _picture;
}

int Worm::update(float *time, ToDraw & map, sf::RenderWindow &window) {
	*time /= FREQUENCY;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		wormListOfWeapons.throwGrenade(5, 280, _prototype.getPosition().x, _prototype.getPosition().y, map);
		//std::cout << "sin 90 = " << wormListOfWeapons.massOfSin[90] << std::endl;
	}
	if (wormListOfWeapons.grenade != nullptr)
	{
		//std::cout << "111" << std::endl;
		wormListOfWeapons.grenade->update(map, window);
		if (wormListOfWeapons.grenade->destroy == 1)
		{
			wormListOfWeapons.grenade->~Grenade();
		}
		//std::cout<< "222"<<std::endl;
	}
	if (_isJumpingBack) {
		_jump(map, "back", time);
		return 0;
	}
	else if (_isJumpingForward) {
		_jump(map, "forward", time);
		return 0;
	}
	else if (_wormIsFalling(map)) {
		_prototype.setPosition(_prototype.getPosition() + sf::Vector2f(0, 1) * (*time));
		return 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			_setJumpAction("forward", map);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			_setJumpAction("back", map);
		}
		_isGoingLeft = false;
		_isGoingRight = true;
		SetSideAction(map, "right", time);
		_isGoingRightPrefer = true;
		_isGoingLeftPrefer = false;
		return 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			_setJumpAction("forward", map);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			_setJumpAction("back", map);
		}
		_isGoingLeft = true;
		_isGoingRight = false;
		SetSideAction(map, "left", time);
		_isGoingLeftPrefer = true;
		_isGoingRightPrefer = false;
		return 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		_setJumpAction("forward", map);
		return 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		_setJumpAction("back", map);
		return 0;
	}
	_isGoingLeft = false;
	_isGoingRight = false;
	return 0;
}


bool Worm::CheckForPlacesAboveAndThenSetPosition(const int& i, const ToDraw & map, float* time, const std::string& direction, const sf::Vector2f& tmp) {
	int dir;
	if (direction == "right") {
		dir = STEP_AHEAD;
	}
	else {
		dir = -STEP_AHEAD;
	}
	for (int j = i; j >= MAX_STEPS_UP * (-1); j--) {
		if (map.getImage().getPixel(tmp.x + dir, tmp.y + j) != sf::Color::Transparent) {
			for (int k = j; k >= MAX_STEPS_UP * (-1); k--) {
				if (map.getImage().getPixel(tmp.x + dir, tmp.y + k) == sf::Color::Transparent) {
					if (_wormOnMap(sf::Vector2f(_prototype.getPosition().x + dir, _prototype.getPosition().y + k), map.getImage())) {
						forDebug.setPosition(_prototype.getPosition() + sf::Vector2f(dir, k) + sf::Vector2f(RADIUS, 2 * RADIUS));
						_prototype.setPosition(_prototype.getPosition() + sf::Vector2f(dir, k) * (*time * EXCEPTION_K));
						return true;
					}
				}
			}
		}
	}
	return false;
}
void Worm::SetSideAction(const ToDraw& map, const std::string& direction, float* time) {
	int dir;
	if (direction == "right") {
		dir = STEP_AHEAD;
	}
	else {
		dir = -STEP_AHEAD;
	}
	sf::Vector2f tmp = _prototype.getPosition() + sf::Vector2f(RADIUS, 2 * RADIUS);
	for (int i = MAX_STEPS_DOWN; i >= MAX_STEPS_UP * (-1); i--) {
		if (map.getImage().getPixel(tmp.x + dir, tmp.y + i) == sf::Color::Transparent) {
			if (CheckForPlacesAboveAndThenSetPosition(i, map, time, direction, tmp)) {
				return;
			}
			if (_wormOnMap(sf::Vector2f(_prototype.getPosition().x + dir, _prototype.getPosition().y + i), map.getImage())) {
				forDebug.setPosition(_prototype.getPosition() + _norm(sf::Vector2f(dir, i)) + sf::Vector2f(RADIUS, 2 * RADIUS));
				_prototype.setPosition(_prototype.getPosition() + _norm(sf::Vector2f(dir, i)) * (*time));
				return;
			}
		}
	}
}

void Worm::drawInWindow(sf::RenderWindow* window, float time) {
	time *= 800;
	if (_isGoingRight) {		
		_picture->getSprite().setTextureRect(sf::IntRect(sf::Vector2i((200+(((int)time)%2)*100), 0), sf::Vector2i(100, 110)));
		_picture->setPos(_prototype.getPosition());
	}
	else if (_isGoingLeft) {
		_picture->getSprite().setTextureRect(sf::IntRect(sf::Vector2i(((int)time%2*100), 0), sf::Vector2i(100, 110)));
		_picture->setPos(_prototype.getPosition());
	}
	else {
		_picture->getSprite().setTextureRect(sf::IntRect(sf::Vector2i(300, 0), sf::Vector2i(100, 110)));
		_picture->setPos(_prototype.getPosition());
	}
	window->draw(_picture->getSprite());
	window->draw(forDebug);
	if (wormListOfWeapons.grenade != nullptr) {

		if (wormListOfWeapons.grenade->destroy == 0)
			window->draw(wormListOfWeapons.grenade->grenPrototype);

	}
}
