#include "ConcreteGame.h"


using namespace sf;
using namespace std;

namespace
{
	const string windowTitle = "Invaders";
	const VideoMode videoMode = VideoMode(768, 1024);
	const Color backgroundColor = Color::Black;
	const unsigned int FRAMERATE_LIMIT = 60;
	const float SPAWN_INVADER_INCREMENT = 1.5f;
}

ConcreteGame::ConcreteGame() : renderWindow(videoMode, windowTitle, Style::Titlebar | Style::Close), invaderSpawnLevel(1), invaderCounter(0), gameOver(false)
{
	entities.push_back(new PlayerEntity(this));
}

ConcreteGame::~ConcreteGame()
{
}

void ConcreteGame::Run()
{
	Clock frameClock;
	while (renderWindow.isOpen() && !gameOver)
	{
		HandleWindowEvents();
		float deltaTime = frameClock.restart().asSeconds();
		ClearWindow();

		SpawnInvaders();
		IntegrateNewEntities();
		CheckCollisions();
		FindOldEntities();
		RemoveOldEntities();
		UpdateEntities(deltaTime);

		DisplayWindow();
	}
}

void ConcreteGame::HandleWindowEvents()
{
	Event event;
	while (renderWindow.pollEvent(event)) {
		if (event.type == Event::Closed) {
			renderWindow.close();
		}
	}
}



void ConcreteGame::ClearWindow()
{
	renderWindow.clear();
}

void ConcreteGame::DisplayWindow()
{
	renderWindow.display();
}

sf::RenderWindow & ConcreteGame::GetRenderWindow()
{
	return renderWindow;
}

void ConcreteGame::add(Entity * _entity)
{
	newEntities.push_back(_entity);
}

void ConcreteGame::Draw(sf::Sprite & sprite)
{
	renderWindow.draw(sprite);
}

void ConcreteGame::Remove(Entity * _entity)
{
	oldEntities.push_back(_entity);
}

void ConcreteGame::SpawnInvaders()
{
	if (invaderCounter == 0)
	{
		for (size_t i = 0; i < invaderSpawnLevel * SPAWN_INVADER_INCREMENT; i++)
		{
			newEntities.push_back(new InvaderEntity(this));
			invaderCounter++;
			invaderSpawnClock.restart();
		}
		invaderSpawnLevel++;
	}
}

void ConcreteGame::IntegrateNewEntities()
{
	for (entityVector::size_type i = 0; i < newEntities.size(); i++)
	{
		entities.push_back(newEntities[i]);
	}
	newEntities.clear();
}

void ConcreteGame::UpdateEntities(float deltaTime)
{
	UpdateEntities(EntityType::PROJECTILE, deltaTime);
	UpdateEntities(EntityType::SHIP, deltaTime);
	UpdateEntities(EntityType::EFFECT, deltaTime);
}

void ConcreteGame::UpdateEntities(EntityType _type, float deltaTime)
{
	for (entityVector::size_type i = 0; i < entities.size(); i++)
	{
		Entity *entity = entities[i];
		if (entity->GetType() == _type)
		{
			entity->Update(deltaTime);
		}
	}
}

void ConcreteGame::CheckCollisions()
{

	entityVector visibleEntities = GetVisibleEntities();
	for (entityVector::size_type i = 0; i < visibleEntities.size(); i++)
	{
		for (entityVector::size_type j = i + 1; j < visibleEntities.size(); j++)
		{
			if (Overlap(entities[i], entities[j]))
			{
				entities[i]->Collide(entities[j]);
				entities[j]->Collide(entities[i]);
			}
		}
	}
}

std::vector<Entity*> ConcreteGame::GetVisibleEntities()
{
	entityVector visibleEntities;
	for (entityVector::size_type i = 0; i < entities.size(); i++)
	{
		if (IsEntityVisible(entities[i]))
		{
			visibleEntities.push_back(entities[i]);
		}
	}
	return visibleEntities;
}

void ConcreteGame::FindOldEntities()
{
	for (entityVector::size_type i = 0; i < entities.size(); i++)
	{
		if (!IsEntityVisible(entities[i]))
		{
			oldEntities.push_back(entities[i]);
		}
	}
}

bool ConcreteGame::IsEntityVisible(Entity * _entity)
{
	Vector2u screenSize = GetRenderWindow().getSize();
	Vector2f _EntityPos = _entity->GetPosition();
	float maxX = screenSize.x + _entity->GetRadius();
	float maxY = screenSize.y + _entity->GetRadius();
	float minX = 0 - _entity->GetRadius();
	float minY = 0 - _entity->GetRadius() * 2;

	return _EntityPos.x < maxX && _EntityPos.x > minX  && _EntityPos.y < maxY && _EntityPos.y > minY;
}

bool ConcreteGame::IsOld(Entity * _entity)
{
	for (entityVector::size_type i = 0; i < oldEntities.size(); i++)
	{
		if (_entity == oldEntities[i])
			return true;
	}
	return false;
}

void ConcreteGame::RemoveOldEntities()
{
	entityVector remainingEntities;
	for (entityVector::size_type i = 0; i < entities.size(); i++)
	{
		if (IsOld(entities[i]) && entities[i]->GetFaction() == EntityFaction::ENEMY && entities[i]->GetType() == EntityType::SHIP)
		{
			invaderCounter--;
			delete entities[i];
		}
		else if (IsOld(entities[i]))
		{
			delete entities[i];
		}
		else
		{
			remainingEntities.push_back(entities[i]);
		}
	}
	oldEntities.clear();
	entities = remainingEntities;
}

bool ConcreteGame::Overlap(Entity * _entity1, Entity * _entity2)
{
	float radius1 = _entity1->GetRadius();
	float radius2 = _entity2->GetRadius();
	Vector2f position1 = _entity1->GetPosition();
	Vector2f position2 = _entity2->GetPosition();
	float deltaX = position2.x - position1.x;
	float deltaY = position2.y - position1.y;
	return (deltaX * deltaX) + (deltaY * deltaY) < (radius1 + radius2) * (radius1 + radius2);
}

sf::Texture ConcreteGame::GetTexture(string filename)
{
	Texture texture;
	texture.loadFromFile(filename);
	return texture;
}


void ConcreteGame::GameOver()
{
	gameOver = true;
}

sf::Sprite ConcreteGame::CreateSprite(sf::Texture& texture, sf::Vector2f position)
{
	Sprite _sprite(texture);
	float originX = _sprite.getLocalBounds().width / 2;
	float originY = _sprite.getLocalBounds().height / 2;
	Vector2f origin(originX, originY);
	_sprite.setOrigin(origin);
	_sprite.setPosition(position);
	return _sprite;
}




