#include "GameLoop.h"
#include"constants.h"
#include<memory>
#include"SplashState.h"
#include<string>

namespace Engine
{


	Engine::GameLoop::GameLoop(int windowWidth, int windowHeight, const std::string& title)
	{
		m_gameDataPtr->window.create(sf::VideoMode(windowWidth, windowHeight), title);

		//add icon
		try
		{
			sf::Image icon;
			if (!icon.loadFromFile(gameConstants::IconPath))
				throw "Error! Couldnt load icon from location";
			m_gameDataPtr->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		}
		catch (const char* exception)
		{
			std::cout << exception << '\n';
		}

		//set initial state (which will be splash) and recall that states are controlled by smart pointers
		m_gameDataPtr->machine.addState(std::make_unique<SplashState>(m_gameDataPtr));

		Run();
	}

	GameLoop::GameLoop(const std::string& title)
	{
		m_gameDataPtr->window.create(sf::VideoMode(constants::windowWidth, constants::windowHeight), title);
		m_gameDataPtr->machine.addState(std::make_unique<SplashState>(m_gameDataPtr));

		Run();
	}

	void Engine::GameLoop::Run()
	{
		//creates the game loop
		float newTime, frameTime, interpolation;
		float currentTime{ m_clock.getElapsedTime().asSeconds() }; //initialized time
		float accumulator{ 0.0f };

		while (m_gameDataPtr->window.isOpen()) //main game loop
		{
			m_gameDataPtr->machine.processStateChange();

			newTime = m_clock.getElapsedTime().asSeconds(); //get now time
			frameTime = newTime - currentTime; // time that has passed between frames
			currentTime = newTime; //update the current time

			if (frameTime > constants::MAX_FRAME_TIME)
				frameTime = constants::MAX_FRAME_TIME;

			accumulator += frameTime;
			while (accumulator >= deltaTime)
			{
				m_gameDataPtr->machine.getActiveState()->handleInput();
				m_gameDataPtr->machine.getActiveState()->update(deltaTime);

				accumulator -= deltaTime;
			}
			interpolation = accumulator / deltaTime;
			m_gameDataPtr->machine.getActiveState()->draw(interpolation);

		}
	}
}