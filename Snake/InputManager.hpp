#pragma once

#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Command.hpp"

class InputManager
{
public:
	InputManager(sf::RenderWindow& windowRef);

	// Bind a Keyboard code with a specific Command
	void bindKey(sf::Keyboard::Key keyCode, Command* command);

	// Return Command given a Keyboard code
	Command* getCommand(sf::Keyboard::Key keyCode);

	// Handle Keyboard events and returns Command
	Command* processInput();

private:
	sf::RenderWindow& window;
	std::unordered_map<int, Command*> keyCommandMap;

	// Command types
	MoveUpCommand moveUpCommand;
	MoveDownCommand moveDownCommand;
	MoveRightCommand moveRightCommand;
	MoveLeftCommand moveLeftCommand;
};

