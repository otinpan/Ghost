#include"Player.h"
#include"Stage.h"

Player::Player(Vec2 pos, float speed)
	:cc(nullptr)
	,mObjectLeft(0)
	,mObjectRight(0)
	,mObjectDown(0)
	,mObjectUp(0)
{
	SetPosition(pos);
	SetSpeed(speed);
}

Player::~Player() {

}

void Player::InitializeActor_Game(class Game* game) {
	Initialize_Game(game);
	cc = new CircleComponent(this);
	cc->Initialize_Game();
	cc->SetCenter(GetPosition());
	mRadius = GetGame()->GetStage()->GetWidth() * 2.0f / 5.0f;
	cc->SetRadius(mRadius);
	switch (GetAttribute()) {
	case Attribute::Ghost:
		cc->SetColor(ColorF(76.0f / 255.0f, 0, 204.0f / 255.0f));
		break;
	case Attribute::Escapee1:
		cc->SetColor(ColorF(204.0f / 255.0f, 0, 204.0f / 255.0f));
		break;
	case Attribute::Escapee2:
		cc->SetColor(ColorF(102.0f / 255.0f, 178.0f / 255.0f, 1));
		break;
	case Attribute::Escapee3:
		cc->SetColor(ColorF(153.0f / 255.0f, 1.0f, 153.0f / 255.0f));
		break;
	}

	mStageObjects = GetGame()->GetStage()->GetStageObjects();
	mVerticalSize = GetGame()->GetStage()->GetVerticalSize();
	mSideSize = GetGame()->GetStage()->GetSideSize();
}

void Player::InitializePlayer_Game(class Game* game) {
	InitializeActor_Game(game);
}

void Player::UpdateActor_Game(float deltaTime) {
	UpdatePlayer_Game(deltaTime);
	
}

void Player::UpdatePlayer_Game(float deltaTime) {

}

void Player::UpdatePos_Game(float deltaTime) {
	mPos = GetPosition();
	
	for (auto &row : mStageObjects) {
		for (auto& stageObject : row) {
			if (stageObject == 0)continue;
			if (stageObject->GetAttribute() == StageObject::Attribute::Door) {
				mObjectLeft = stageObject->GetDoorCenter().x - stageObject->GetDoorWidth() / 2.0f;
				mObjectRight = stageObject->GetDoorCenter().x + stageObject->GetDoorWidth() / 2.0f;
				mObjectUp = stageObject->GetDoorCenter().y + stageObject->GetDoorHeight() / 2.0f;
				mObjectDown = stageObject->GetDoorCenter().y - stageObject->GetDoorHeight() / 2.0f;
			}
			mObjectLeft = stageObject->GetPosition().x - stageObject->GetWidth() / 2.0f;
			mObjectRight = stageObject->GetPosition().x + stageObject->GetWidth() / 2.0f;
			mObjectUp = stageObject->GetPosition().y + stageObject->GetHeight() / 2.0f;
			mObjectDown = stageObject->GetPosition().y - stageObject->GetHeight() / 2.0f;
		}
		//Objectとの当たり判定
		if (mPos.x + mRadius > mObjectLeft)mPos.x = mObjectLeft - mRadius - 0.005;
		if (mPos.x - mRadius < mObjectRight)mPos.x = mObjectRight + mRadius + 0.005;
		if (mPos.y + mRadius > mObjectDown)mPos.y = mObjectDown - mRadius - 0.005;
		if (mPos.y - mRadius < mObjectUp)mPos.y = mObjectUp + mRadius + 0.005;
	}

	//端
	if (mPos.x + mRadius > GetGame()->GetStage()->GetRight())
		mPos.x = GetGame()->GetStage()->GetRight() - mRadius - 0.005;
	if (mPos.x - mRadius < GetGame()->GetStage()->GetLeft())
		mPos.x = GetGame()->GetStage()->GetLeft() + mRadius + 0.005;
	if (mPos.y + mRadius > GetGame()->GetStage()->GetUp())
		mPos.y = GetGame()->GetStage()->GetUp() - mRadius - 0.005;
	if (mPos.y - mRadius < GetGame()->GetStage()->GetDown())
		mPos.y = GetGame()->GetStage()->GetDown() + mRadius + 0.005;
}

