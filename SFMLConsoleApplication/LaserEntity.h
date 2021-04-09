#pragma once
#ifndef LASERENTITY_H
#define LASERENTITY_H
#include "Entity.h"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include <iostream>

class LaserEntity : public Entity
{
public:
	LaserEntity(Game *game, EntityFaction _faction, sf::Vector2f direction, sf::Vector2f _position);
	virtual ~LaserEntity() override;
	virtual EntityType GetType() override;
	virtual EntityFaction GetFaction() override;
	virtual void Update(float deltaTime) override;
	virtual sf::Vector2f GetPosition() override;
	virtual float GetRadius() override;
	virtual void Collide(Entity *_entity) override;


private:
	EntityFaction faction;
	sf::Texture laserTexture;
	sf::Sprite laser;
	sf::Vector2f direction;
	void Draw();
	void Move(float deltaTime);
};
#endif // !LASERENTITY_H

