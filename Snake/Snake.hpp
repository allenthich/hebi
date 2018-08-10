#pragma once
#include <forward_list>
#include "Box2D/Box2D.h"
#include "GameActor.hpp"

// Higher entity containing actors

class Snake
{
public:
	Snake();
	~Snake();
	
	// Insert new head segment at the front
	void addSegment(GameActor* newSegment);

	// Retrieve reference to segments
	std::forward_list<GameActor*>& getSegments();

	// Apply transformation to head and update the following segments' positions
	void transform(b2Vec2 transformVec);

private:
	unsigned int numSegments;

	// Contains list of GameActors
	std::forward_list<GameActor*> segments;

	// Increases segment size by 1
	void increaseSegmentSize();

	// Given a segment, apply transformation
	void transformSegment(GameActor& segment, b2Vec2 transformVec);
};

