#include"Hand.h"
#include"CircleComponent.h"
#include"InputComponent_Keyboard.h"
#include"CreateStage.h"
#include"StageObject.h"
#include<Siv3D.hpp>

Hand::Hand()
	:StandardSpeed(0.6)
	,ic(nullptr)
	,cc(nullptr)
	,mIsGrap(false)
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
	cc->SetRadius(0.04f);
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
	if (nowPos.y > 0.9)nowPos.x = 0.9;
	SetPosition(nowPos);
	cc->SetCenter(nowPos);

	if (!mIsGrap) {
		if (inputDecision.down()) {
			mIsGrap = true;
			for (auto stageObject : GetCreateStage()->GetStageObjects()) {

			}
		}
	}
}

void Hand::ActorInput(std::vector<Input> keyState) {

}

