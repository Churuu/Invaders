#include "InvaderEntity.h"

using namespace std;
using namespace sf;

namespace
{
	const float INVADER_RADIUS = 30;
	const string FILE_NAME = "invader.png";
}

InvaderEntity::InvaderEntity(Game * _game) : Entity(_game), shootCooldownClock()
{
	invaderTexture = _game->GetTexture(FILE_NAME);
	invaderSprite = _game->CreateSprite(invaderTexture, Vector2f(rand() % 768, 0 - GetRadius()));
	invaderSprite.setScale(0.4f, 0.4f);
	invaderVelocityY = rand() % 100 + 30;
	shootCooldown = rand() % 600 + 300;

	if (rand() % 1+2 == 1)
	{
		invaderVelocityX = 200;
	}
	else
	{
		invaderVelocityX = -200;
	}

}

InvaderEntity::~InvaderEntity()
{
}

void InvaderEntity::Update(float deltaTime)
{
	Draw();
	Move(deltaTime);
	HandleFire();
}

void InvaderEntity::Draw()
{
	mGame->Draw(invaderSprite);
}

void InvaderEntity::Move(float deltaTime)
{
	invaderSprite.move(invaderVelocityX * deltaTime, invaderVelocityY * deltaTime);

	if (GetPosition().x >= mGame->GetRenderWindow().getSize().x - GetRadius())
	{
		invaderVelocityX = -200;
	}
	if (GetPosition().x <= 0 + GetRadius())
	{
		invaderVelocityX = 200;
	}

}


sf::Vector2f InvaderEntity::GetPosition()
{
	return invaderSprite.getPosition();
}

EntityType InvaderEntity::GetType()
{
	return EntityType::SHIP;
}

EntityFaction InvaderEntity::GetFaction()
{
	return EntityFaction::ENEMY;
}

float InvaderEntity::GetRadius()
{
	return INVADER_RADIUS;
}

void InvaderEntity::Collide(Entity *_entity)
{
	EntityFaction faction = _entity->GetFaction();
	EntityType type = _entity->GetType();
	if (faction == EntityFaction::FRIENDLY && type == EntityType::PROJECTILE)
	{
		mGame->Remove(this);
		mGame->add(new ExplosionEntity(mGame, GetPosition()));
	}
}

void InvaderEntity::HandleFire()
{
	if (shootCooldownClock.getElapsedTime().asMilliseconds() > shootCooldown && mGame->IsEntityVisible(this))
	{
		mGame->add(new LaserEntity(mGame, EntityFaction::ENEMY, Vector2f(0, 400), GetPosition()));
		shootCooldownClock.restart();
		shootCooldown = rand() % 600 + 300;
	}
}

