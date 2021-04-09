#pragma once
#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include <iostream>
class Entity;


class Game
{
public:
	Game();
	virtual ~Game();
	virtual void Run() = 0;
	virtual sf::RenderWindow& GetRenderWindow() = 0;
	virtual void add(Entity *entity) = 0;
	virtual void Draw(sf::Sprite &sprite) = 0;
	virtual void Remove(Entity *entity) = 0;
	virtual sf::Sprite CreateSprite(sf::Texture& texture, sf::Vector2f position) = 0;
	virtual sf::Texture GetTexture(std::string _filename) = 0;
	virtual bool IsEntityVisible(Entity *_entity) = 0;
	virtual void GameOver() = 0;
};

#endif // !GAME_H

