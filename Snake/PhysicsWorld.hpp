#pragma once
#include <Box2D/Box2D.h>
#include "GameActor.hpp"

class PhysicsWorld : public b2ContactListener
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void initialize();
	void update();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	// Create box body at a position, attaches it to the world, and returns a pointer to it
	b2Body* createBoxBody(float32 x, float32 y, b2BodyType bodyType);

	// Retrieve borders GameActor
	GameActor getBordersActor();

private:
	// World object, which will hold and simulate the rigid bodies.
	b2World* world;

	// Physics body containing the border edges
	GameActor borders;

	// Physics body containing the collectible
	b2Body* triggerBody;

	// Reusable body definition
	b2BodyDef bodyDef;

	// Creates the physical boundaries of the window
	void createBorderEdges();
};

