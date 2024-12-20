#pragma once
#include"StageObject.h"

class Door:public StageObject {
public:
	Door(Vec2 pos, float widht, float height);
	~Door();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;
	void InitializeStageObject_Game(class Game* game)override;
	void InitializeStage_Game()override;

	void UpdateStageObject_CreateStage(float deltaTime)override;
	void UpdateStageObject_Game(float deltaTime)override;

	void InitializeStageMenu_CreateStage()override;
	void UpdateStageMenu_CreateStage(float dletaTime)override;
	void DrawStageMenu_CreateStage()override;
	void ShutdownStageMenu_CreateStage()override;

	


private:
	SquareComponent* sc;
	CircleComponent* mUpCC;
	CircleComponent* mDownCC;
	CircleComponent* mRightCC;
	CircleComponent* mLeftCC;

	std::vector<float> DoorRel_dy;
	std::vector<float> DoorRel_dx;
	std::vector<float> DoorWidth;
	std::vector<float> DoorHeight;

	Vec2 mTriCenter;
	Vec2 mUpTriPos;
	Vec2 mDownTriPos;
	Vec2 mRightTriPos;
	Vec2 mLeftTriPos;
	float mTriLength;
	float mTriLengthFromCenter;


	
};
