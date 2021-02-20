#pragma once
#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
#include"Button.h"
#include"constants.h"
#include"MainMenu.h"


class utility
{
public:
	static sf::Vector2f centralPosition(const sf::Text& textObj, const sf::RenderWindow& window);
	static sf::Vector2f centralPosition(const Engine::Button& buttonObj, const sf::RenderWindow& window);


	template<typename T>
	static sf::Vector2f centralPosition(const T& obj, const sf::RenderWindow& window);

	template<typename T>
	static sf::Vector2f resizeRelToWindow(const T& obj, const sf::RenderWindow& window, float relX = 0.2f, float relY = 0.2f);

	template<typename T>
	static float tileSizeConstraint(const T& obj, const sf::RenderWindow& window)
	{
		float possX{ (window.getSize().x - obj.getGlobalBounds().width - gameConstants::MARGIN) / gameConstants::GAME_DIM };
		float possY{( window.getSize().y - 2.0f * gameConstants::MARGIN) / gameConstants::GAME_DIM };

		if (possX < possY)
			return possX;
		return possY;

	}


	template<typename T1, typename T2>
	static sf::Vector2f centralPosRelativeTo(const T1& obj1, const T2& obj2)
	{
		return { obj2.getPosition().x + obj2.getGlobalBounds().width / 2.0f - (obj1.getGlobalBounds().width / 2.0f), obj2.getPosition().y + obj2.getGlobalBounds().height / 2.0f - (obj1.getGlobalBounds().height / 2.0f) };
	}
	
	//template spec for numbers and tiles
	template<>
	static sf::Vector2f centralPosRelativeTo(const sf::Text& obj1, const sf::RectangleShape& obj2)
	{
		return { obj2.getPosition().x + obj2.getGlobalBounds().width / 2.0f - (obj1.getGlobalBounds().width / 2.0f), obj2.getPosition().y + obj2.getGlobalBounds().height / 2.0f - (obj1.getGlobalBounds().height) };
	}
	
	static void threadCaller(MainMenuState* mainmenuPtr);


};

template<typename T>
inline sf::Vector2f utility::centralPosition(const T& obj, const sf::RenderWindow& window)
{
	return { window.getSize().x / 2.0f - (obj.getGlobalBounds().width / 2.0f), window.getSize().y / 2.0f - (obj.getGlobalBounds().height / 2.0f) };
}

template<typename T>
inline sf::Vector2f utility::resizeRelToWindow(const T& obj, const sf::RenderWindow& window, float relX, float relY)
{
	return { window.getSize().x / obj.getGlobalBounds().width * relX, window.getSize().y / obj.getGlobalBounds().height * relY };
}
