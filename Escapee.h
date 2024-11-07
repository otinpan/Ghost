#include"Player.h"

class Escapee :public Player {
public:
	Escapee(Vec2 pos);
	~Escapee();

	void InitializePlayer_CreateStage(CreateStage* createStage)override;
	void UpdatePlayer_CreateStage(float deltaTime)override;

private: 
};
