#include"Hand.h"
#include"CircleComponent.h"
#include"InputComponent_Keyboard.h"
#include"CreateStage.h"
#include"StageObject.h"
#include"Stage.h"
#include<Siv3D.hpp>

Hand::Hand()
	:StandardSpeed(0.6)
	,ic(nullptr)
	,cc(nullptr)
	,mIsGrap(false)
	,mGrapping(nullptr)
{

}

Hand::~Hand()
{

}

void Hand::InitializeActor_CreateStage(CreateStage* createstage) {
	Initialize_CreateStage(createstage);
	SetPosition({ 0.0f,0.0f });

	cc = new CircleComponent(this);
	cc->Initialize_CreateStage();
	cc->SetRadius(0.01f);
	cc->SetColor({ 0.0,0.0,0.0 });

	inputUp = KeyW;
	inputDown = KeyS;
	inputRight = KeyD;
	inputLeft = KeyA;
	inputDecision = KeyK;
	inputBack = KeyL;

	ic = new InputComponent_Keyboard(this);
	ic->SetUpKey(inputUp);
	ic->SetDownKey(inputDown);
	ic->SetRightKey(inputRight);
	ic->SetLeftKey(inputLeft);
	ic->SetMaxXSpeed(StandardSpeed);
	ic->SetMaxYSpeed(StandardSpeed);

}

void Hand::UpdateActor_CreateStage(float deltaTime) {
	Vec2 nowPos = GetPosition();
	if (nowPos.x < -0.9)nowPos.x = -0.9;
	if (nowPos.x > 0.9)nowPos.x = 0.9;
	if (nowPos.y < -0.9)nowPos.y = -0.9;
	if (nowPos.y > 0.9)nowPos.y = 0.9;
	SetPosition(nowPos);
	cc->SetCenter(nowPos);

	if (!mIsGrap) {
		for (auto stageObject : GetCreateStage()->GetStageObjects()) {
			if (stageObject->GetSquareComponent()->GetRect().
				contains(cc->GetCircle()) && inputDecision.pressed()) {
				stageObject->SetIsGripen(true);
				mGrapping = stageObject;
				mIsGrap = true;
			}
		}
	}
	else {
		if (!inputDecision.pressed()) {
			mGrapping->SetIsGripen(false);
			//StageのmRectsとの当たり判定
			for (int i = 0; i < GetCreateStage()->GetStage()->GetVerticalSize(); i++) {
				for (int j = 0; j < GetCreateStage()->GetStage()->GetSideSize();j++) {
					if (GetCreateStage()->GetStage()->GetRects()[i][j]
						.contains(cc->GetCircle())) {
						GetCreateStage()->GetStage()->SetNewStageObject(i, j);
					}
				}
			}
			mIsGrap = false;
			delete mGrapping;
		}
	}
}

void Hand::ActorInput(std::vector<Input> keyState) {

}

