#pragma once
#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include "Entity.h"
#include "Game.h"
#include "LaserEntity.h"

class PlayerEntity : public Entity
{
public:
	PlayerEntity(Game *_game);
	virtual void Update(float deltaTime) override;
	virtual sf::Vector2f GetPosition() override;
	virtual float GetRadius() override;
	virtual	EntityType GetType() override;
	virtual EntityFaction GetFaction() override;
	virtual void Collide(Entity *_entity) override;

private:
	sf::Sprite ship;
	sf::Texture shipTexture;
	sf::Clock shootCooldown;
	void Draw();
	void Input(float deltaTime);
	void ConstrainShip();
	void Shoot();

};

#endif // !PLAYERENTITY_H
