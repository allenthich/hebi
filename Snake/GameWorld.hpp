#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include "Command.hpp"
#include "PhysicsWorld.hpp"
#include "Snake.hpp"

class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	void initialize();
	void update(Command* command);

	Snake& getPlayer();
	GameActor& getCollectible();

private:
	PhysicsWorld physicsWorld;
	Snake playerActor;
	GameActor* collectibleActor;

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distributor;
};