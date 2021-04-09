#pragma once
#ifndef CONCRETEGAME_H
#define CONCRETEGAME_H

#include "Game.h"
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include "PlayerEntity.h"
#include "InvaderEntity.h"

class ConcreteGame : public Game
{
public:
	ConcreteGame();
	~ConcreteGame();
	virtual void Run() override;
	virtual sf::RenderWindow& GetRenderWindow() override;
	virtual void add(Entity *entity) override;
	virtual void Draw(sf::Sprite &sprite) override;
	virtual void Remove(Entity *entity) override;
	virtual sf::Sprite CreateSprite(sf::Texture &texture, sf::Vector2f position) override;
	virtual sf::Texture GetTexture(std::string _filename) override;
	virtual bool IsEntityVisible(Entity *_entity) override;
	virtual void GameOver() override;
private:
	sf::RenderWindow renderWindow;
	typedef std::vector<Entity*> entityVector;
	int invaderCounter;
	sf::Clock invaderSpawnClock;
	entityVector entities;
	entityVector newEntities;
	entityVector oldEntities;
	float invaderSpawnLevel;
	void DisplayWindow();
	void ClearWindow();
	void HandleWindowEvents();
	void SpawnInvaders();
	void IntegrateNewEntities();
	void RemoveOldEntities();
	void UpdateEntities(float deltaTime);
	void UpdateEntities(EntityType _type, float deltaTime);
	void FindOldEntities();
	bool IsOld(Entity *_entity);
	void CheckCollisions();
	std::vector<Entity*> GetVisibleEntities();
	bool Overlap(Entity *_entity1, Entity *_entity2);
	bool gameOver;


};

#endif // !CONCRETEGAME_H

