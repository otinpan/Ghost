#pragma once
#include"Player.h"

class Ghost_Game :public Player{
public:
	Ghost_Game(Vec2 pos,float speed);
	~Ghost_Game();

	void InitializePlayer_Game(class Game* game)override;

	void UpdatePlayer_Game(float deltaTime)override;

private:
	class CircleComponent* cc;
	class InputComponent_Keyboard* ic;

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;

	float StandardSpeed;
};
