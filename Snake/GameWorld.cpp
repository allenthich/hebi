#include "GameWorld.hpp"

GameWorld::GameWorld()
{
	collectibleActor = nullptr;
	// Construct a trivial random generator engine from a time-based seed:
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	generator = std::default_random_engine(seed);
	distributor = std::uniform_int_distribution<int>(10, 490);
}

GameWorld::~GameWorld()
{
	delete collectibleActor;
}

void GameWorld::initialize()
{
	physicsWorld.initialize();

	// Define center of SnakeBox at (10, 10)
	b2Body* headBox = physicsWorld.createBoxBody(10.0f, 10.0f, b2_dynamicBody);
	playerActor.addSegment(new GameActor(headBox, GameActorType::SEGMENT));

	// Define random position for collectible
	int randYCoord = distributor(generator);
	int randXCoord = distributor(generator);

	// Ensure it is placed away from snake starting position
	while (!((randXCoord > 50) && randYCoord > 50))
	{
		randXCoord = distributor(generator);
		randYCoord = distributor(generator);
	}

	std::cout << "FINAL randXCoord: " << randXCoord << "randYCoord: " << randYCoord << std::endl;

	// Create a collectible box
	b2Body* collectibleBox = physicsWorld.createBoxBody(randXCoord, randYCoord, b2_staticBody);
	collectibleActor = new GameActor(collectibleBox, GameActorType::COLLECTIBLE);
}

void GameWorld::update(Command* command)
{
	// Check player position and detect any collisions before processing input
	// Is the new Command going to collide?
	// physicsWorld.checkCollision();

	if (command != nullptr) {
		// Apply command to the player
		command->execute(playerActor);
	}
	physicsWorld.update();
}

Snake & GameWorld::getPlayer()
{
	return playerActor;
}

GameActor & GameWorld::getCollectible()
{
	return *collectibleActor;
}
