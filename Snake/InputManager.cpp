#include "InputManager.hpp"

InputManager::InputManager(sf::RenderWindow& windowRef)
	: window(windowRef), keyCommandMap({})
{
	bindKey(sf::Keyboard::Up, &moveUpCommand);
	bindKey(sf::Keyboard::Down, &moveDownCommand);
	bindKey(sf::Keyboard::Right, &moveRightCommand);
	bindKey(sf::Keyboard::Left, &moveLeftCommand);
};

void InputManager::bindKey(sf::Keyboard::Key keyCode, Command* command)
{
	keyCommandMap.emplace(keyCode, command);
}

Command* InputManager::getCommand(sf::Keyboard::Key keyCode)
{
	try {
		return keyCommandMap.at(keyCode);
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "ERROR: UNBOUND_KEYCODE " << keyCode << oor.what() << std::endl;
	}
	return nullptr;
}

Command* InputManager::processInput()
{
	sf::Event event;

	if (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			else {
				return getCommand(event.key.code);
			}
		}
		else if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
	return nullptr;
}

