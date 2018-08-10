#include "Snake.hpp"

Snake::Snake()
	: numSegments(0)
{
}

Snake::~Snake()
{
	// Delete each segment
	for (auto segmentIt = segments.begin(); segmentIt != segments.end(); ++segmentIt)
	{
		GameActor& currSegment = **segmentIt;
		delete &currSegment;
	}
}

void Snake::addSegment(GameActor* newSegment)
{
	segments.emplace_front(newSegment);
	increaseSegmentSize();
}

std::forward_list<GameActor*>& Snake::getSegments()
{
	return segments;
}

void Snake::transform(b2Vec2 transformVec)
{
	// TODO: Consider instead of transformVec, take in a state enum, then apply force
	b2Vec2 currPositionVec;
	b2Vec2 newTransformVec = transformVec;
	for (auto segmentIt = segments.begin(); segmentIt != segments.end(); ++segmentIt)
	{
		// Get current position for next segment and set the new position
		GameActor& currSegment = **segmentIt;
		currPositionVec = currSegment.getPosition();
		currSegment.translate(newTransformVec);
		newTransformVec = currPositionVec;
	}
}

void Snake::increaseSegmentSize()
{
	++numSegments;
}

// Private
void Snake::transformSegment(GameActor & segment, b2Vec2 transformVec)
{
	segment.translate(transformVec);
}