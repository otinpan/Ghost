#pragma once
#include"StageObject.h"

class Brock :public StageObject {
public:
	Brock(Vec2 pos,float width,float height);
	~Brock();

	void InitializeStageObject_CreateStage(class CreateStage* createStage)override;
	void InitializeStage_CreateStage() override;
	void InitializeStageObject_Game(class Game* game)override;
	void InitializeStage_Game() override;

	void UpdateStageObject_CreateStage(float deltaTime)override;
	void UpdateStageObject_Game(float deltaTime)override;


	//Menu
	void InitializeStageMenu_CreateStage()override;
	void UpdateStageMenu_CreateStage(float deltaTime)override;
	void DrawStageMenu_CreateStage()override;
	void ShutdownStageMenu_CreateStage()override;

private:
	class SquareComponent* StoneSC;
	class SquareComponent* WoodSC;
	class SquareComponent* GrassSC;
	class SpriteComponent* scStone;
	class SpriteComponent* scWood;
	class SpriteComponent* scGrass;
	Vec2 StoneRectCenter_StageMenu;
	Vec2 WoodRectCenter_StageMenu;
	Vec2 GrassRectCenter_StageMenu;

	float RectWidth_StageMenu;
	float RectHeight_StageMenu;
	float EachWidth_StageMenu;
	float EachHeight_StageMenu;

	//Material mMaterial;
};
