#include "ToDraw.h"


ToDraw::ToDraw(){
	std::cout << "Picture isn't initialized" << std::endl;
}

ToDraw::ToDraw(const std::string path)
{
	_image.loadFromFile(path);
	_image.createMaskFromColor(sf::Color(161,161,159));
	_texture.loadFromImage(_image);
	_texture.setSmooth(true);
	if (path == "background.png") {
		update();
	}
	_sprite.setTexture(_texture);
}

ToDraw::ToDraw(const std::string && path, const sf::Vector2f& scale){
	_image.loadFromFile(path);
	_texture.loadFromImage(_image);
	_texture.setSmooth(true);
	_sprite.setTexture(_texture);
	_sprite.setScale(scale.x, scale.y);
}

ToDraw::ToDraw(const std::string && path, const sf::Vector2f & scale, const sf::Color && toMask){
	_image.loadFromFile(path);
	_image.createMaskFromColor(toMask);
	_texture.loadFromImage(_image);
	_texture.setSmooth(true);
	_sprite.setTexture(_texture);
	_sprite.setScale(scale.x, scale.y);
}