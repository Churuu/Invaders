#include "PlayerEntity.h"

using namespace sf;
using namespace std;

namespace
{
	const float SHIP_RADIUS = 30;
	const float SHIP_VELOCITY = 500;
	const string FILE_NAME = "Player.png";
}


PlayerEntity::PlayerEntity(Game *_game) : Entity(_game), shootCooldown()
{
	shipTexture = _game->GetTexture(FILE_NAME);
	ship = _game->CreateSprite(shipTexture, Vector2f(384, 800));
	ship.setScale(0.8f, 0.8f);
}

void PlayerEntity::Update(float deltaTime)
{
	Draw();
	Input(deltaTime);
	ConstrainShip();
	Shoot();
}

void PlayerEntity::Draw()
{
	mGame->Draw(ship);
}

void PlayerEntity::Input(float deltaTime)
{
	float x = 0.0f; 
	float y = 0.0f;
	
	if (Keyboard::isKeyPressed(Keyboard::W)) 
	{
		y -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		y += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		x += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		x -= 1;
	}
	Vector2f movement(x,y);
	ship.move(movement * deltaTime * SHIP_VELOCITY); 

}

void PlayerEntity::ConstrainShip()
{
	Vector2u window = mGame->GetRenderWindow().getSize();
	float maxX = window.x - GetRadius(), minX = 0 + GetRadius();
	float maxY = 0 + GetRadius(), minY = window.y - GetRadius();
	Vector2f shipPosition = ship.getPosition();

	if (shipPosition.x > maxX)
		ship.setPosition(maxX, shipPosition.y);
	if (shipPosition.x < minX)
		ship.setPosition(minX, shipPosition.y);
	if (shipPosition.y < maxY)
		ship.setPosition(shipPosition.x, maxY);
	if (shipPosition.y > minY)
		ship.setPosition(shipPosition.x, minY);
		
}

void PlayerEntity::Shoot()
{
	if (Keyboard::isKeyPressed(Keyboard::Space) && shootCooldown.getElapsedTime().asMilliseconds() > 250)
	{
		mGame->add(new LaserEntity(mGame, EntityFaction::FRIENDLY, Vector2f(0, -1000), GetPosition()));
		mGame->add(new LaserEntity(mGame, EntityFaction::FRIENDLY, Vector2f(350, -1000), GetPosition()));
		mGame->add(new LaserEntity(mGame, EntityFaction::FRIENDLY, Vector2f(-350, -1000), GetPosition()));
		shootCooldown.restart();
	}
}

sf::Vector2f PlayerEntity::GetPosition()
{
	return ship.getPosition();
}

float PlayerEntity::GetRadius()
{
	return SHIP_RADIUS;
}

EntityType PlayerEntity::GetType()
{
	return EntityType::SHIP;
}

EntityFaction PlayerEntity::GetFaction()
{
	return EntityFaction::FRIENDLY;
}

void PlayerEntity::Collide(Entity *_entity)
{
	EntityFaction faction = _entity->GetFaction();
	if (faction == EntityFaction::ENEMY)
	{
		mGame->GameOver();
	}
}


