#pragma once
#include <SFML/Graphics.hpp>
#include "InputManager.hpp"
#include "GameWorld.hpp"

class GameManager
{
public:
	GameManager();

	// Initialize game window
	void start();

	// Returns whether the game is running
	const bool isRunning();

	// Main game loop
	void run();

	// Render game state
	void draw();

	void update();

private:
	sf::RenderWindow window;
	InputManager inputManager;
	GameWorld gameWorld;
};

