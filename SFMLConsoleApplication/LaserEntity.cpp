#include "LaserEntity.h"

using namespace std;
using namespace sf;

namespace 
{
	const string FILE_NAME = "laser.png";
	const float RADIUS = 5.0f;
}

LaserEntity::LaserEntity(Game *_game, EntityFaction _faction, sf::Vector2f _direction, sf::Vector2f _position) : Entity(_game), faction(_faction), direction(_direction)
{
	laserTexture = mGame->GetTexture(FILE_NAME);
	laser = mGame->CreateSprite(laserTexture, _position);
}

LaserEntity::~LaserEntity()
{
}

EntityType LaserEntity::GetType()
{
	return EntityType::PROJECTILE;
}

EntityFaction LaserEntity::GetFaction()
{
	return faction;
}

void LaserEntity::Update(float deltaTime)
{
	Draw();
	Move(deltaTime);
}

sf::Vector2f LaserEntity::GetPosition()
{
	return laser.getPosition();
}

float LaserEntity::GetRadius()
{
	return RADIUS;
}

void LaserEntity::Collide(Entity *_entity)
{
	EntityFaction faction = _entity->GetFaction();
	EntityType type = _entity->GetType();
	if (faction != GetFaction() && faction != EntityFaction::NEUTRAL && type == EntityType::SHIP)
	{
		mGame->Remove(this);
	}
}

void LaserEntity::Draw()
{
	mGame->Draw(laser);
}

void LaserEntity::Move(float deltaTime)
{
	laser.move(direction * deltaTime);
}
