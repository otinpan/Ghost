#pragma once
#include<Siv3D.hpp>

enum class State {
	Game,
	CreateStage,
};


struct GameDate {
	float ScreenHeight;
	float ScreenWidth;
	float Magnification;
};


using App = SceneManager<State>;

bool DeleteStageData(const String& stageName);

std::string NormalizePromptToSafeAscii(std::string_view s);
