#include"StageObject.h"

class Ghost_CreateStage :public StageObject{
public:
	Ghost_CreateStage(Vec2 pos, float width, float height);
	~Ghost_CreateStage();

	void InitializeStageObject_CreateStage(CreateStage* createStage)override;
	void UpdateStageObject_CreateStage(float deltaTime)override;

	void InitializeStageMenu_CreateStage()override;
	void UpdateStageMenu_CreateStage(float deltaTime)override;
	void DrawStageMenu_CreateStage()override;
	void ShutdownStageMenu_CreateStage()override;

private:
	class SquareComponent* mBarSC_CreateStage;

	Vec2 mBarCenter;
	Vec2 mBarPos;
	float mBarHeight;
	float mBarMax;
	float mBarMin;
	bool mIsBarGripen;

	//Font
	const Font mStageMenuFont{ ConvertToInt(GetScreenHeight() * 0.03) };
};
