# hebi
	Notes
	7/20/2018
	InputManaager should not have specific move commands bound to keys
	 - should have bindKey(Key, Command) method
	 - should store map of {Key, Command} KeyPressed, SpecificCommand

	7/21/2018
	Physics body for attaching to Snake

	7/24/2018
	Correctly rendered Snake head in both coordinates of SFML and Box2D

	7/26/2018
	Created Collectible class, determined it should exist in the GameWorld
	Command should return a moveState
	physicsWorld.checkCollision(player, moveState);
	TODO: Read type inheritance because Collectible is identical to SnakeSegment
	I think I could get rid of SnakeSegment and Collectible and use GameActor

	7/28/2018
	randomBox creation


	Tasks
	1. Connect input with updateSegment
		updateSegment(Position newPos)
		- checks valid position
		- updates all segments
	2. Physical border edges
