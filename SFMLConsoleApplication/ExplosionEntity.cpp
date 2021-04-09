#include "ExplosionEntity.h"

using namespace std;
using namespace sf;

namespace 
{
	const string FILE_NAME = "explosion.png";
}

ExplosionEntity::ExplosionEntity(Game * game, sf::Vector2f _position) : Entity(game), removeTimer()
{
	explosionTexture = mGame->GetTexture(FILE_NAME);
	explosion = mGame->CreateSprite(explosionTexture, _position);
	explosion.setScale(0.5f, 0.5f);
}

ExplosionEntity::~ExplosionEntity()
{
}

EntityType ExplosionEntity::GetType()
{
	return EntityType::EFFECT;
}

EntityFaction ExplosionEntity::GetFaction()
{
	return EntityFaction::NEUTRAL;
}

void ExplosionEntity::Update(float deltaTime)
{
	mGame->Draw(explosion);

	if (removeTimer.getElapsedTime().asSeconds() > 1)	
	{
		mGame->Remove(this);
	}
}

sf::Vector2f ExplosionEntity::GetPosition()
{
	return explosion.getPosition();
}

float ExplosionEntity::GetRadius()
{
	return 0.0f;
}

void ExplosionEntity::Collide(Entity * _entity)
{
}
