#pragma once
#include<string>
namespace Engine
{
	namespace constants
	{
		constexpr int windowWidth{ 1200 };
		constexpr int windowHeight{ 800 };

		constexpr float MAX_FRAME_TIME{ 0.25f };
		constexpr float DELTA_TIME{ 1.0f / 60.0f };
	}
}

namespace gameConstants
{
	const std::string defaultFont{ "resources/sansation.ttf" };
	const std::string currentVersion{ "1.0" };
	constexpr int splash_welcome_time{ 1 };
	const std::string defaultButtonTexture{ "resources/defaultButton.png" };	
	const std::string defaultBackgroundTexture{ "resources/defaultBackground.png" };
	const std::string IconPath{ "resources/icon.png" };

	//sudoku game definitins
	constexpr int GAME_DIM{ 9 };
	constexpr float MARGIN{ 2.0f };
	constexpr int BLOCK{ 3 };

}