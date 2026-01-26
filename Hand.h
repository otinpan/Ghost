#pragma once
#include"Actor.h"

class Hand :public Actor {
public:
	Hand();
	~Hand();

	void InitializeActor_CreateStage(class CreateStage* createstage) override;

	void UpdateActor_CreateStage(float deltaTime)override;
	void ActorInput(std::vector<Input> keyState)override;

	class CircleComponent* GetCircleComponent() { return cc; }

	bool GetIsGrap() { return mIsGrap; }
	void SetIsGrap(bool isGrap) { mIsGrap = isGrap; }
	bool GetIsExpand() { return mIsExpand; }
	void SetIsExpand(bool isExpand) { mIsExpand = isExpand; }
	bool GetIsChoose() { return mIsChoose; }
	void SetIsChoose(bool isChoose) { mIsChoose = isChoose; }
	bool GetIsDelete() { return mIsDelete; }
	void SetIsDelete(bool isDelete) { mIsDelete = isDelete; }

	Input GetInputUp() { return inputUp; }
	Input GetInputDown() { return inputDown; }
	Input GetInputRight() { return inputRight; }
	Input GetInputLeft() { return inputLeft; }
	Input GetInputGrap() { return inputGrap; }
	Input GetInputBack() { return inputBack; }
	Input GetInputR() { return inputR; }
	Input GetInputL() { return inputL; }
	Input GetInputU() { return inputU; }
	Input GetInputD() { return inputD; }
	Input GetInputChoose() { return inputChoose; }
	Input GetInputDelete() { return inputDelete; }
	Input GetInputPlus() { return inputPlus; }
	Input GetInputMinus() { return inputMinus; }

	class StageObject* & GetChoosing() { return mChoosing; }
	class StageObject*& GetGrapping() { return mGrapping; }

	void InitChoosing(StageObject* stageObject);
	void DeleteChoosing();


private:
	class CircleComponent* cc;
	class InputComponent_Keyboard* ic;
	class StageObject* mGrapping;
	class StageObject* mChoosing;
	class SpriteComponent* sc;
	Vec2 cursorOffset;

	float StandardSpeed;

	Input inputUp;
	Input inputDown;
	Input inputRight;
	Input inputLeft;
	Input inputGrap;
	Input inputBack;
	Input inputR;
	Input inputL;
	Input inputU;
	Input inputD;
	Input inputChoose;
	Input inputDelete;
	Input inputPlus;
	Input inputMinus;

	std::vector<int> dx;
	std::vector<int> dy;

	bool mIsGrap;
	bool mIsExpand;
	bool mIsChoose;
	bool mIsDelete;
	bool mIsSetOnStage;
};

