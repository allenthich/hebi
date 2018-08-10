#pragma once
#include <Box2D/Box2D.h>

enum GameActorType{
	SEGMENT,
	COLLECTIBLE,
	BORDER
};

class GameActor
{
public:
	GameActor();
	GameActor(b2Body* body, GameActorType actorType);
	GameActorType getType();
	const float32 getXCoordinate();
	const float32 getYCoordinate();
	const b2Vec2 getPosition();
	void translate(const b2Vec2 movementVector);

	void startCollision();
	void endCollision();

	bool isColliding();


private:
	b2Body * _physicalBody;
	GameActorType _type;
	bool _isColliding;
};

