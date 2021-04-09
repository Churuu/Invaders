#pragma once
#ifndef ENTITY_H
#define ENTITY_H

class Game;
#include "SFML/Graphics.hpp"

enum class EntityType{PROJECTILE, SHIP, EFFECT};
enum class EntityFaction{FRIENDLY, ENEMY, NEUTRAL};

class Entity
{
public:
	Entity(Game *_game);
	virtual ~Entity();
	virtual EntityFaction GetFaction() = 0;
	virtual EntityType GetType() = 0;
	virtual sf::Vector2f GetPosition() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual float GetRadius() = 0;
	virtual void Collide(Entity *_entity) = 0;
protected:
	Game *mGame;
};
#endif // !ENTITY_H

