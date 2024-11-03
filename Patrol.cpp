#include"Patrol.h"
#include"CreateStage.h"
#include"StageMenu.h"

Patrol::Patrol(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
{
	SetAttribute(Attribute::Patrol);
}

void Patrol::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
}

void Patrol::UpdateStageObject_CreateStage(float deltaTime) {
}

Patrol::~Patrol() {

}

void Patrol::InitializeStageMenu_CreateStage() {
	mTriCenter = Vec2(
		(GetCreateStage()->GetStageMenu()->GetMenuRight() + GetCreateStage()->GetStageMenu()->GetMenuLeft()) / 2.0f,
		(GetCreateStage()->GetStageMenu()->GetMenuUp() + GetCreateStage()->GetStageMenu()->GetMenuDown())*2.0f / 3.0f
	);
	mTriLength = GetCreateStage()->GetStageMenu()->GetMenuWidth() / 5.0f;
	mTriLengthFromCenter = GetCreateStage()->GetStageMenu()->GetMenuWidth() / 4.0f;

	mUpTriPos = Vec2(
		mTriCenter.x,
		mTriCenter.y + mTriLengthFromCenter
	);
	mDownTriPos = Vec2(
		mTriCenter.x,
		mTriCenter.y - mTriLengthFromCenter
	);
	mRightTriPos = Vec2(
		mTriCenter.x + mTriLengthFromCenter,
		mTriCenter.y
	);
	mLeftTriPos = Vec2(
		mTriCenter.x - mTriLengthFromCenter,
		mTriCenter.y
	);


	mUpCC = new CircleComponent(this);
	mUpCC->Initialize_CreateStage();
	mUpCC->SetCenter(mUpTriPos);
	mUpCC->SetRadius(mTriLength);
	mUpCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));

	mDownCC = new CircleComponent(this);
	mDownCC->Initialize_CreateStage();
	mDownCC->SetCenter(mDownTriPos);
	mDownCC->SetRadius(mTriLength);
	mDownCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));

	mRightCC = new CircleComponent(this);
	mRightCC->Initialize_CreateStage();
	mRightCC->SetCenter(mRightTriPos);
	mRightCC->SetRadius(mTriLength);
	mRightCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));

	mLeftCC = new CircleComponent(this);
	mLeftCC->Initialize_CreateStage();
	mLeftCC->SetCenter(mLeftTriPos);
	mLeftCC->SetRadius(mTriLength);
	mLeftCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));

	mAddCenter= Vec2(
		(GetCreateStage()->GetStageMenu()->GetMenuRight() + GetCreateStage()->GetStageMenu()->GetMenuLeft()) / 2.0f,
		(GetCreateStage()->GetStageMenu()->GetMenuUp() + GetCreateStage()->GetStageMenu()->GetMenuDown()) * 1.0f / 3.0f
	);
}

void Patrol::UpdateStageMenu_CreateStage(float deltaTime) {

}

void Patrol::DrawStageMenu_CreateStage() {

}

void Patrol::ShutdownStageMenu_CreateStage() {

}
