#pragma once
#include "Snake.hpp"
#include "Constants.hpp"

class Command
{
public:
	virtual ~Command() {};
	virtual void execute(Snake& playerActor) = 0;
};

// TODO: Remove velocity scalar

class MoveUpCommand : public Command
{
public:
	virtual void execute(Snake& playerActor) { playerActor.transform(b2Vec2(0.0f, -Constants::segmentRenderSize*100)); }
};

class MoveDownCommand : public Command
{
public:
	virtual void execute(Snake& playerActor) { playerActor.transform(b2Vec2(0.0f, Constants::segmentRenderSize*100)); }
};

class MoveRightCommand : public Command
{
public:
	virtual void execute(Snake& playerActor) { playerActor.transform(b2Vec2(Constants::segmentRenderSize*100, 0.0f)); }
};

class MoveLeftCommand : public Command
{
public:
	virtual void execute(Snake& playerActor) { playerActor.transform(b2Vec2(-Constants::segmentRenderSize*100, 0.0f)); }
};