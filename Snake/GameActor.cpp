#include "GameActor.hpp"

GameActor::GameActor()
{
}

GameActor::GameActor(b2Body* body, GameActorType actorType)
	: _physicalBody(body), _type(actorType), _isColliding(false)
{
	body->SetUserData(this);
}

GameActorType GameActor::getType()
{
	return _type;
}

const float32 GameActor::getXCoordinate()
{
	return _physicalBody->GetPosition().x;
}

const float32 GameActor::getYCoordinate()
{
	return _physicalBody->GetPosition().y;
}

void GameActor::translate(const b2Vec2 movementVector)
{
	_physicalBody->SetLinearVelocity(movementVector);
}

void GameActor::startCollision()
{
	_isColliding = true;
}

void GameActor::endCollision()
{
	_isColliding = false;
}

bool GameActor::isColliding()
{
	return _isColliding;
}

const b2Vec2 GameActor::getPosition()
{
	return _physicalBody->GetPosition();
}