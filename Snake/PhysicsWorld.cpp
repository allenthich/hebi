#include "PhysicsWorld.hpp"
#include "Constants.hpp"

PhysicsWorld::PhysicsWorld()
{
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	world = new b2World(gravity);
	world->SetContactListener(this);
}

PhysicsWorld::~PhysicsWorld()
{
	delete world;
}

void PhysicsWorld::initialize()
{
	createBorderEdges();
}

void PhysicsWorld::update()
{
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 8;
	int32 positionIterations = 3;

	// Instruct the world to perform a single step of simulation.
	// It is generally best to keep the time step and iterations fixed.
	world->Step(timeStep, velocityIterations, positionIterations);
}

void PhysicsWorld::BeginContact(b2Contact * contact)
{
	// Check if fixture A was a segment
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData) {
		if (static_cast<GameActor*>(bodyUserData)->getType() == GameActorType::SEGMENT)
			static_cast<GameActor*>(bodyUserData)->startCollision();
	}

	// Check if fixture B was a segment
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData) {
		if (static_cast<GameActor*>(bodyUserData)->getType() == GameActorType::SEGMENT)
			static_cast<GameActor*>(bodyUserData)->startCollision();
	}
}

void PhysicsWorld::EndContact(b2Contact * contact)
{
	// Check if fixture A was a segment
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData) {
		if (static_cast<GameActor*>(bodyUserData)->getType() == GameActorType::SEGMENT)
			static_cast<GameActor*>(bodyUserData)->endCollision();
	}

	// Check if fixture B was a segment
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData) {
		if (static_cast<GameActor*>(bodyUserData)->getType() == GameActorType::SEGMENT)
			static_cast<GameActor*>(bodyUserData)->endCollision();
	}
}

b2Body* PhysicsWorld::createBoxBody(float32 x, float32 y, b2BodyType bodyType)
{
	// Set body position
	bodyDef.type = bodyType;
	bodyDef.position.Set(x, y);
	b2Body* newBody = world->CreateBody(&bodyDef);

	// Define another box shape for our body
	b2PolygonShape newBox;

	// SetAsBox takes half-widths
	newBox.SetAsBox((Constants::segmentRenderSize / 2), (Constants::segmentRenderSize / 2));

	// Define the dynamic body fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &newBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	newBody->CreateFixture(&fixtureDef);

	return newBody;
}

GameActor PhysicsWorld::getBordersActor()
{
	return borders;
}

void PhysicsWorld::createBorderEdges()
{
	// Define border vertices
	b2Vec2 topLeftVertex(0.0f, 0.0f);
	b2Vec2 topRightVertex(Constants::windowWidth, 0.0f);
	b2Vec2 botLeftVertex(0.0f, Constants::windowHeight);
	b2Vec2 botRightVertex(Constants::windowWidth, Constants::windowWidth);

	// Define a border body with position
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.0f, 0.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* borderBody = world->CreateBody(&bodyDef);

	// Define shape and fixture
	b2EdgeShape edge;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &edge;

	// Define and attach the edges
	edge.Set(topLeftVertex, topRightVertex); // Top Edge
	borderBody->CreateFixture(&fixtureDef);

	edge.Set(botLeftVertex, botRightVertex); // Bottom Edge
	borderBody->CreateFixture(&fixtureDef);

	edge.Set(topLeftVertex, botLeftVertex); // Left Edge
	borderBody->CreateFixture(&fixtureDef);

	edge.Set(topRightVertex, botRightVertex); // Right Edge
	borderBody->CreateFixture(&fixtureDef);

	borders = GameActor(borderBody, GameActorType::BORDER);
}
