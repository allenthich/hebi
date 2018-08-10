#include "GameManager.hpp"
#include "Constants.hpp"

GameManager::GameManager()
	: inputManager(window)
{
}

void GameManager::start()
{
	// Initialize game
	gameWorld.initialize();

	// Create window
	window.create(sf::VideoMode((unsigned int)Constants::windowWidth, (unsigned int)Constants::windowHeight), "Snake");
	window.setFramerateLimit(60);
}

const bool GameManager::isRunning()
{
	return window.isOpen();
}

void GameManager::run()
{
	start();

	while (isRunning())
	{
		draw();
		update();
	}
}

void GameManager::update()
{
	// Update the calculations
	Command* command = inputManager.processInput();
	gameWorld.update(command);
}

void GameManager::draw()
{	
	// Update window frame
	window.clear();

	GameActor& collectible = gameWorld.getCollectible();
	Snake& player = gameWorld.getPlayer();
	float segmentRenderHalfSize = (Constants::segmentRenderSize / 2);

	// Define a 20x20 collectible rectangle
	sf::RectangleShape collectibleRectangle(sf::Vector2f(Constants::segmentRenderSize, Constants::segmentRenderSize));
	collectibleRectangle.setFillColor(sf::Color::Cyan);

	// Draw collectible box that will trigger growth
	// Half width is subtracted to begin rendering at the top left corner of the box instead of the center
	collectibleRectangle.setPosition((collectible.getXCoordinate() - segmentRenderHalfSize), (collectible.getYCoordinate() - segmentRenderHalfSize));
	window.draw(collectibleRectangle);

	// Define a 20x20 snake segment rectangle
	sf::RectangleShape segmentRectangle(sf::Vector2f(Constants::segmentRenderSize, Constants::segmentRenderSize));

	// Draw all snake segments
	for (auto segmentIt = player.getSegments().cbegin(); segmentIt != player.getSegments().cend(); ++segmentIt)
	{
		GameActor& currentSegment = **segmentIt;
		//std::cout << "X: " << currentSegment.getXCoordinate() << " | " << "Y: " << currentSegment.getYCoordinate() << std::endl;
		// Subtract half width to begin rendering at the top left corner of the box instead of the center
		segmentRectangle.setPosition((currentSegment.getXCoordinate() - segmentRenderHalfSize), (currentSegment.getYCoordinate() - segmentRenderHalfSize));

		if (currentSegment.isColliding())
			segmentRectangle.setFillColor(sf::Color::Red);
		else 
			segmentRectangle.setFillColor(sf::Color::White);
		window.draw(segmentRectangle);
	}

	window.display();
}
