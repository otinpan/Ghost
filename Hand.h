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

	InputGroup GetInputUp() { return inputUp; }
	InputGroup GetInputDown() { return inputDown; }
	InputGroup GetInputRight() { return inputRight; }
	InputGroup GetInputLeft() { return inputLeft; }
	InputGroup GetInputGrap() { return inputGrap; }
	InputGroup GetInputBack() { return inputBack; }
	InputGroup GetInputR() { return inputR; }
	InputGroup GetInputL() { return inputL; }
	InputGroup GetInputU() { return inputU; }
	InputGroup GetInputD() { return inputD; }
	InputGroup GetInputChoose() { return inputChoose; }
	InputGroup GetInputDelete() { return inputDelete; }
	InputGroup GetInputPlus() { return inputPlus; }
	InputGroup GetInputMinus() { return inputMinus; }

	class StageObject* & GetChoosing() { return mChoosing; }
	class StageObject*& GetGrapping() { return mGrapping; }

	void InitChoosing(StageObject* stageObject);
	void DeleteChoosing();


private:
	class CircleComponent* cc;
	class InputComponent_Keyboard* ic;
	class StageObject* mGrapping;
	class StageObject* mChoosing;

	float StandardSpeed;

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputRight;
	InputGroup inputLeft;
	InputGroup inputGrap;
	InputGroup inputBack;
	InputGroup inputR;
	InputGroup inputL;
	InputGroup inputU;
	InputGroup inputD;
	InputGroup inputChoose;
	InputGroup inputDelete;
	InputGroup inputPlus;
	InputGroup inputMinus;

	std::vector<int> dx;
	std::vector<int> dy;

	bool mIsGrap;
	bool mIsExpand;
	bool mIsChoose;
	bool mIsDelete;
};

