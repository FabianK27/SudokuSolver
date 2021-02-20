#pragma once
#include<SFML/Graphics.hpp>
#include<memory> // for std::shared_ptr
#include<string>

#include"constants.h"
#include"StateMachine.h"
#include"ResourceManager.h"
#include"InputManager.h"

namespace Engine
{
	struct GameData
	{
		StateMachine machine;
		ResourceManager resourceMan;
		inputManager inputMan;
		sf::RenderWindow window;
	};

	using gameDataPtr = std::shared_ptr<GameData>; // gamedata can potentially be owned by more than one instance so shared_ptr instead of unique_ptr

	class GameLoop
	{
	private:
		const float deltaTime{constants::DELTA_TIME}; // delta time to be used for framerate conversion
		sf::Clock m_clock; //required to make use of delta time

		gameDataPtr m_gameDataPtr{ std::make_shared<GameData>() };

		void Run();
	public:
		GameLoop(int windowWidth = constants::windowWidth, int windowHeight = constants::windowHeight, const std::string& title = "Game Application");
		GameLoop(const std::string& title);
 
	};

}