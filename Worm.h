#pragma once
#include "ToDraw.h"
#include "Grenade.h"
#include "ListOfWeapons.h"
const float FREQUENCY = 5000;
const int MAX_STEPS_UP = 14;
const int MAX_STEPS_DOWN = 3;
const float RADIUS = 50;
const float HEIGHT_TO_CHECK = 30;
const float WIDTH_TO_CHECK = 1;
const float STEP_AHEAD = 1;
const float START_POSITION = 500;
const float EXCEPTION_K = 4;
const float FACTOR_FOR_JUMPING = 100;
const float STARTING_UP_VELOCITY = -1.5;
const float STARTING_SIDE_VELOCITY = 0.5 / 1.5;
const float JUMP_BACK_STARTING_UP_VELOCITY = -2;
const float JUMP_BACK_STARTING_SIDE_VELOCITY = 0.2 / 2;

class Worm
{
private:
	bool _wormOnMap(const sf::Vector2f& newPosition, const sf::Image& map);
	ToDraw* _picture;
	sf::CircleShape _prototype;
	bool _isGoingLeft = false;
	bool _isGoingRight = false;
	bool _isGoingRightPrefer = false;
	bool _isGoingLeftPrefer = false;
	sf::Vector2f _lastBarrier;
	inline bool _wormIsFalling(const ToDraw & map) const;
	sf::Vector2f _norm(const sf::Vector2f& toNorm);
	sf::CircleShape forDebug;
	ListOfWeapons wormListOfWeapons;




	void SetSideAction(const ToDraw& map, const std::string& direction, float* time);
	void _setJumpAction(const std::string& direction, const ToDraw& map);
	void _jump(const ToDraw & map, const std::string& where, float* time);
	void _setStartingVelocity(sf::Vector2f* startingVelocity, const std::string& where);
	bool _isJumpingBack = false;
	sf::Vector2f _velocityForJumping;
	float _timeForJumping;
	bool _isJumpingForward = false;
	bool CheckForPlacesAboveAndThenSetPosition(const int& i, const ToDraw & map, float* time, const std::string& direction, const sf::Vector2f& tmp);

public:
	Worm();
	Worm(const std::string& path);
	~Worm();
	int update(float* time, ToDraw& map, sf::RenderWindow &window);
	inline sf::Vector2f getPosition() const { return _prototype.getPosition(); };
	void drawInWindow(sf::RenderWindow* window, float time);
	inline sf::Sprite getSprite() const { return _picture->getSprite(); };
};

