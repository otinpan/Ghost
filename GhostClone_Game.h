#pragma once
#include"Player.h"

class GhostClone_Game :public Player {
public:
	GhostClone_Game(Vec2 pos, float speed);
	~GhostClone_Game();

	void InitializePlayer_Game(class Game* game)override;

	void UpdatePlayer_Game(float deltaTime)override;

private:
	class InputComponent_Keyboard* ic;

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;

	float StandardSpeed;
};
