#include"Player.h"
#include"Stage.h"

Player::Player(Vec2 pos, float speed)
	:cc(nullptr)
	, mObjectLeft(0)
	, mObjectRight(0)
	, mObjectDown(0)
	, mObjectUp(0)
	, mSpeedMagnification(speed)
{
	SetPosition(pos);
}

Player::~Player() {

}

void Player::InitializeActor_Game(class Game* game) {
	Initialize_Game(game);
	cc = new CircleComponent(this);
	cc->Initialize_Game();
	cc->SetCenter(GetPosition());
	mRadius = GetGame()->GetStage()->GetRectWidth() * 2.0f / 5.0f;
	cc->SetRadius(mRadius);
	switch (GetAttribute()) {
	case Attribute::Ghost:
		cc->SetColor(ColorF(76.0f / 255.0f, 0, 204.0f / 255.0f));
		break;
	case Attribute::GhostClone:
		cc->SetColor(ColorF(43.0f / 255.0f, 0, 110.0f / 255.0f));
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

	if (!GetAttribute() == Attribute::GhostClone) {
		for (auto& row : GetGame()->GetStage()->GetStageObjects()) {
			for (auto& stageObject : row) {
				if (stageObject == 0)continue;
				if (!IsIntersect_SC(stageObject->GetSquareComponent(), cc))continue;
				if (stageObject->GetAttribute() == StageObject::Attribute::Door) {
					mObjectLeft = stageObject->GetDoorCenter().x - stageObject->GetDoorWidth() / 2.0f;
					mObjectRight = stageObject->GetDoorCenter().x + stageObject->GetDoorWidth() / 2.0f;
					mObjectUp = stageObject->GetDoorCenter().y + stageObject->GetDoorHeight() / 2.0f;
					mObjectDown = stageObject->GetDoorCenter().y - stageObject->GetDoorHeight() / 2.0f;
				}
				else {
					mObjectLeft = stageObject->GetPosition().x - stageObject->GetWidth() / 2.0f;
					mObjectRight = stageObject->GetPosition().x + stageObject->GetWidth() / 2.0f;
					mObjectUp = stageObject->GetPosition().y + stageObject->GetHeight() / 2.0f;
					mObjectDown = stageObject->GetPosition().y - stageObject->GetHeight() / 2.0f;
				}
				LineL = { {mObjectLeft,mObjectUp},{mObjectLeft,mObjectDown} };
				LineR = { {mObjectRight,mObjectUp},{mObjectRight,mObjectDown} };
				LineU = { {mObjectRight,mObjectUp},{mObjectLeft,mObjectUp} };
				LineD = { {mObjectLeft,mObjectDown},{mObjectRight,mObjectDown} };
				//Objectとの当たり判定
				if (cc->GetCircle().intersects(LineL)) mPos.x = mObjectLeft - mRadius - 0.008; //Playerが左
				if (cc->GetCircle().intersects(LineR))mPos.x = mObjectRight + mRadius + 0.008; //Playerが右
				if (cc->GetCircle().intersects(LineD))mPos.y = mObjectDown - mRadius - 0.008; //Playerが下
				if (cc->GetCircle().intersects(LineU))mPos.y = mObjectUp + mRadius + 0.008; //Playerが上
			}

		}
	}

	//端
	if (mPos.x + mRadius > GetGame()->GetStage()->GetRight())
		mPos.x = GetGame()->GetStage()->GetRight() - mRadius - 0.008;
	if (mPos.x - mRadius < GetGame()->GetStage()->GetLeft())
		mPos.x = GetGame()->GetStage()->GetLeft() + mRadius + 0.008;
	if (mPos.y + mRadius > GetGame()->GetStage()->GetUp())
		mPos.y = GetGame()->GetStage()->GetUp() - mRadius - 0.008;
	if (mPos.y - mRadius < GetGame()->GetStage()->GetDown())
		mPos.y = GetGame()->GetStage()->GetDown() + mRadius + 0.008;

	SetPosition(mPos);
	cc->SetCenter(mPos);
}

