#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
class ToDraw
{
protected:
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
public:
	ToDraw();
	~ToDraw() {};
	ToDraw(const std::string path);
	ToDraw(const std::string && path, const sf::Vector2f & scale);
	ToDraw(const std::string && path, const sf::Vector2f & scale, const sf::Color&& toMask);
	inline const sf::Image& getImage() const { return _image; }; 
	inline sf::Image& getImage() { return _image; };
	inline sf::Texture getTexture() const { return _texture; };
	inline void update() { _texture.loadFromImage(_image); _sprite.setTexture(_texture); };
	inline sf::Sprite& getSprite() { return _sprite; };
	inline void drawInWindow(sf::RenderWindow* window) { window->draw(_sprite); };
	inline void setPos(const sf::Vector2f&& position) { _sprite.setPosition(position); };
	inline void setPos(const sf::Vector2f& position) { _sprite.setPosition(position); };
};

