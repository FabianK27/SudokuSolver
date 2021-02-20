#include "utility.h"

sf::Vector2f utility::centralPosition(const sf::Text& textObj, const sf::RenderWindow& window) 
{
    return { window.getSize().x / 2.0f - (textObj.getGlobalBounds().width / 2.0f), window.getSize().y / 2.0f - (textObj.getGlobalBounds().height / 2.0f) };
}

sf::Vector2f utility::centralPosition(const Engine::Button& buttonObj, const sf::RenderWindow& window) 
{
    return { window.getSize().x / 2.0f - (buttonObj.getShape().getGlobalBounds().width / 2.0f), window.getSize().y / 2.0f - (buttonObj.getShape().getGlobalBounds().height / 2.0f) };

}

void utility::threadCaller(MainMenuState* mainmenuPtr)
{
    mainmenuPtr->manualInput();
}


