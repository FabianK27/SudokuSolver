#pragma once
#include"GameLoop.h"
#include<SFML/Graphics.hpp>
#include"State.h"

class SplashState : public Engine::State
{
private:
	Engine::gameDataPtr m_gameData;
	sf::Clock m_clock;
	sf::Text m_welcomeText;


public:
	SplashState(Engine::gameDataPtr gameData);

	virtual bool init() override;
	virtual void handleInput() override;
	virtual void update(float deltaTime) override;
	virtual void draw(float deltaTime) override;
};

