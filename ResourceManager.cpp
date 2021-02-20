#include "ResourceManager.h"
#include<iostream>

namespace Engine
{

	void Engine::ResourceManager::loadTexture(const std::string& idName, const std::string& filename)
	{
		sf::Texture tex;
		if (tex.loadFromFile(filename))
		{
			m_textureMap[idName] = tex;
		}
		else
		{
			std::cerr << "ERROR! FAILED TO LOAD TEXTURE FROM LOCATION: " << filename << '\n';
		}
	}

	sf::Texture& Engine::ResourceManager::getTexture(const std::string& id)
	{
		if (!m_textureMap.count(id)) //if key doesnt exist throw an exception
			throw -1;
		return m_textureMap.at(id);
	}

	void Engine::ResourceManager::loadFont(const std::string& idName, const std::string& filename)
	{
		sf::Font font;
		if (font.loadFromFile(filename))
		{
			m_fontMap[idName] = font;
		}
		else
		{
			std::cerr << "ERROR! FAILED TO LOAD FONT FROM LOCATION: " << filename << '\n';
		}
	}

	sf::Font& Engine::ResourceManager::getFont(const std::string& id)
	{
		if (!m_fontMap.count(id)) //if key doesnt exist throw an exception
			throw -1;
		return m_fontMap.at(id);
	}

	void ResourceManager::addButton(const std::string& idName, Button&& button)
	{
		m_buttonMap.insert(std::pair<std::string, Button>(idName, button));
	}

	void ResourceManager::addButton(const std::string& idName, const Button& button)
	{
		m_buttonMap.insert(std::pair<std::string, Button>(idName, button));
	}

	Button& ResourceManager::getButton(const std::string buttonId)
	{
		if (!m_buttonMap.count(buttonId)) //if key doesnt exist throw an exception
			throw -1;
		return m_buttonMap.at(buttonId);
	}

}