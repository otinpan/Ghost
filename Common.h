#pragma once
#include<Siv3D.hpp>

enum class State {
	Game,
};


struct GameDate {
	float ScreenHeight;
	float ScreenWidth;
	float Magnification;
};


using App = SceneManager<State>;
