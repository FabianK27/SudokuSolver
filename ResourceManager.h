#pragma once
#include<map> // use a map to control resources
#include<SFML/Graphics.hpp>
#include"Button.h"

namespace Engine
{

	class ResourceManager
	{
	private:
		std::map<std::string, sf::Texture> m_textureMap;
		std::map<std::string, sf::Font> m_fontMap;
		std::map<std::string, Button> m_buttonMap{};


	public:
		ResourceManager() {}
		~ResourceManager() {}

		void loadTexture(const std::string& idName, const std::string& filename);
		sf::Texture& getTexture(const std::string& id);

		void loadFont(const std::string& idName, const std::string& filename);
		sf::Font& getFont(const std::string& id);

		void addButton(const std::string& idName, Button&& button); //rref so that we can use button contructor inplace
		void addButton(const std::string& idName, const Button& button); // or allow an existing button to be referenced..
		Button& getButton(const std::string buttonId);
	};

}