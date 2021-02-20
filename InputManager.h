#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include"Button.h"

namespace Engine
{
	class inputManager
	{
	public:
		inputManager() {}
		~inputManager() {}

		bool isButtonClicked(Button& buttonObj, sf::Mouse::Button mouseButton, sf::RenderWindow& window);
		bool isSpriteClicked(sf::Sprite& spriteObj, sf::Mouse::Button mouseButton, sf::RenderWindow& window);
		bool isSpriteHovered(sf::Sprite& spriteObj, sf::RenderWindow& window);

		sf::Vector2i getMousePos(const sf::RenderWindow& window) const;

	};

}


#endif // for once a standard header guard
