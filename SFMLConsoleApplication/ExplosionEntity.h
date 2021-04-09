#pragma once
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Entity.h"
#include "game.h"
#include "SFML/Graphics.hpp"
#include <iostream>

class ExplosionEntity : public Entity
{
public:
	ExplosionEntity(Game *game, sf::Vector2f _position);
	virtual ~ExplosionEntity() override;
	virtual EntityType GetType() override;
	virtual EntityFaction GetFaction() override;
	virtual void Update(float deltaTime) override;
	virtual sf::Vector2f GetPosition() override;
	virtual float GetRadius() override;
	virtual void Collide(Entity *_entity) override;
private:
	sf::Texture explosionTexture;
	sf::Sprite explosion;
	sf::Clock removeTimer;
};
#endif // !INCLUDED EXPLOSION_H

