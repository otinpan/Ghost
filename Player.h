#pragma once
#include"Actor.h"

class Player :public Actor {
public:
	Player(Vec2 pos, float speed);
	~Player();

	enum Attribute {
		Ghost,
		Escapee1,
		Escapee2,
		Escapee3,
	};

	void InitializeActor_Game(class Game* game)override;
	virtual void InitializePlayer_Game(class Game* game);

	void UpdateActor_Game(float deltaTime)override;
	virtual void UpdatePlayer_Game(float deltaTime);

	void SetAttribute(Attribute attribute) { mAttribute = attribute; }
	Attribute GetAttribute() { return mAttribute; }

private:
	class CircleComponent* cc;

	Attribute mAttribute;
};
