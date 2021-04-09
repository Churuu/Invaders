#pragma once
#ifndef INVADERENTITY_H
#define INVADERENTITY_H
#include "SFML/Graphics.hpp"
#include <iostream>
#include "game.h"
#include "Entity.h"
#include "LaserEntity.h"
#include "ExplosionEntity.h"


class InvaderEntity : public Entity
{
public:
	InvaderEntity(Game *_game);
	virtual ~InvaderEntity() override;
	virtual void Update(float deltaTime) override;
	virtual sf::Vector2f GetPosition() override;
	virtual EntityType GetType() override;
	virtual EntityFaction GetFaction() override;
	virtual float GetRadius() override;
	virtual void Collide(Entity *_entity) override;
private:
	sf::Texture invaderTexture;
	sf::Sprite invaderSprite;
	sf::Clock shootCooldownClock;
	float shootCooldown;
	float invaderVelocityY;
	float invaderVelocityX;
	void Draw();
	void Move(float deltaTime);
	void HandleFire();
};


#endif // !INVADERENTITY_H

