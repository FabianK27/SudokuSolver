#include "InputManager.h"
namespace Engine
{
	bool Engine::inputManager::isButtonClicked(Button& buttonObj, sf::Mouse::Button mouseButton, sf::RenderWindow& window)
	{
		if (sf::Mouse::isButtonPressed(mouseButton) && buttonObj.getShape().getGlobalBounds().contains(sf::Vector2f{ sf::Mouse::getPosition(window) }))
			return true;
		return false;
	}

	bool Engine::inputManager::isSpriteClicked(sf::Sprite& spriteObj, sf::Mouse::Button mouseButton, sf::RenderWindow& window)
	{
		if (sf::Mouse::isButtonPressed(mouseButton) && spriteObj.getGlobalBounds().contains(sf::Vector2f{ sf::Mouse::getPosition(window) }))
			return true;
		return false;
	}

	bool inputManager::isSpriteHovered(sf::Sprite& spriteObj, sf::RenderWindow& window)
	{
		if (spriteObj.getGlobalBounds().contains(sf::Vector2f{ sf::Mouse::getPosition(window) }))
			return true;
		return false;
	}

	sf::Vector2i Engine::inputManager::getMousePos(const sf::RenderWindow& window) const
	{
		return sf::Mouse::getPosition(window);
	}

}
