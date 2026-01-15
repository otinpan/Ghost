#include"StageObject.h"
#include"SquareComponent.h"
#include"CircleComponent.h"
#include"CreateStage.h"
#include"Hand.h"
#include"Stage.h"
#include"math.h"
#include"DrawingComponent.h"
StageObject::StageObject(Vec2 pos, float width, float height)
	:sqc(nullptr)
	, mIsGripen(false)
	, mCenter(pos)
	, mMaterial(Material::Stone)
	, mWidth(width)
	, mHeight(height)
	, mIteration({ -1,-1 })
	, mAttribute(Attribute::None)
	, mClockwise(0)
	, mPatrolRange(1)
	, mIsInObjectMenu(false)
	, mBatterySize(BatterySize::Zero)
	, mTreasure(Treasure::Empty)
	, StandardSpeed(0.2f)
	, mIsTurn(false)
{
	SetPosition(pos);
}

StageObject::~StageObject() {
	if (GetCreateStage()) {
		GetCreateStage()->RemoveStageObject(this);
		if (mIsInStage) {
			if (mAttribute != Attribute::Candle) {
				GetCreateStage()->GetStage()->SetStageObject(GetIteration().first, GetIteration().second, 0);
			}
			else {

			}
		}
	}

	DeleteComponents();
}

void StageObject::InitializeActor_CreateStage(class CreateStage* createstage){
	Initialize_CreateStage(createstage);
	GetCreateStage()->AddStageObject(this);

	sqc = new SquareComponent(this,50,DrawingComponent::DrawingState::UNAFFECTED);
	sqc->InitializeDrawing_CreateStage(mCenter,mWidth,mHeight);

	sc = new SpriteComponent(this, 70, DrawingComponent::DrawingState::UNAFFECTED);
	sc->InitializeDrawing_CreateStage(mCenter, mWidth, mHeight);

	switch (mAttribute) {
	case Attribute::Wall:
		sqc->SetColor(ColorF(0.5f));
		sc->SetTexture(TextureAsset(U"brock_stone"));
		break;
	case Attribute::Brock:
		sqc->SetColor(ColorF(1, 1, 1));
		sqc->SetIsDraw(false);
		sc->SetTexture(TextureAsset(U"brock_stone"));
		break;
	case Attribute::Door:
		sqc->SetColor(ColorF(0, 0, 0));
		sqc->SetIsDraw(false);
		sc->SetTexture(TextureAsset(U"door_front"));
		break;
	case Attribute::Patrol:
		sqc->SetColor(ColorF(0, (float)102 / 255, 0));
		sc -> SetIsDraw(false);
		break;
	case Attribute::Key:
		sqc->SetColor(ColorF((float)76 / 255, (float)0, (float)153 / 255));
		sqc->SetIsDraw(false);
		sc->SetTexture(TextureAsset(U"key"));
		break;
	case Attribute::Battery:
		sqc->SetColor(ColorF(0, 1, 128.0f / 255.0f));
		sqc->SetIsDraw(false);
		sc->SetTexture(TextureAsset(U"battery"));
		break;
	case Attribute::TreasureChest:
		sqc->SetColor(ColorF(1, 1, 0));
		sqc->SetIsDraw(false);
		sc->SetTexture(TextureAsset(U"treasure"));
		break;
	case Attribute::Candle:
		sqc->SetColor(ColorF(1, 1, 1));
		sqc->SetIsDraw(false);
		sc->SetTexture(TextureAsset(U"candle"));
		break;
	case Attribute::Ghost:
		sqc->SetColor(ColorF(76.0f / 255.0f, 0, 204.0f / 255.0f));
		sc->SetIsDraw(false);
		break;
	case Attribute::Escapee1:
		sqc->SetColor(ColorF(204.0f / 255.0f, 0, 204.0f/255.0f));
		sc->SetIsDraw(false);
		break;
	case Attribute::Escapee2:
		sqc->SetColor(ColorF(102.0f / 255.0f, 178.0f/255.0f, 1));
		sc->SetIsDraw(false);
		break;
	case Attribute::Escapee3:
		sqc->SetColor(ColorF(153.0f / 255.0f, 1.0f,153.0f / 255.0f));
		break;
	}

	cc.resize(4);
	for (int i = 0; i < 4; i++) {
		cc[i] = new CircleComponent(this,70,DrawingComponent::DrawingState::UNAFFECTED);
		cc[i]->InitializeDrawing_CreateStage();
		cc[i]->SetRadius((float)mWidth / 7.0f);
		cc[i]->SetColor(ColorF(0, 0, 1));
	}

	float dw = (float)mWidth / 2.0f - cc[0]->GetRadius();
	float dh = (float)mHeight / 2.0f - cc[0]->GetRadius() * mHeight / mWidth;
	dx = { -dw,dw,dw,-dw };
	dy = { dh,dh,-dh,-dh };
}

void StageObject::InitializeStageObject_CreateStage(class CreateStage* createstage) {
	InitializeActor_CreateStage(createstage);
}

void StageObject::InitializeStage_CreateStage() {

}

void StageObject::UpdateActor_CreateStage(float deltaTime) {
	if (GetIsGripen()) {
		SetPosition(GetCreateStage()->GetHand()->GetPosition());
	}

	UpdateStageObject_CreateStage(deltaTime);


	// 描画の位置変更
	sqc->SetCenter(GetPosition());
	sc->SetCenter(GetPosition());

	for (int i = 0; i < 4; i++) {
		cc[i]->
			SetCenter(Vec2
			(GetPosition().x + dx[i],
				GetPosition().y + dy[i]));
	}
}

void StageObject::UpdateStageObject_CreateStage(float deltaTime) {

}


void StageObject::ActorInput(std::vector<Input> keyState) {

}


void StageObject::RotateClockwise(bool isClockwise) {
	if (isClockwise) {
		mClockwise++;
	}
	else {
		mClockwise--;
	}

	if (mClockwise < 0)mClockwise += 4;
	mClockwise %= 4;
	AdjustPatrolRange();
}

void StageObject::SpreadLightRad(bool isPlus) {
	if (isPlus)mLightRad += GetCreateStage()->GetStage()->GetHeight() / 700.0f;
	else mLightRad -= GetCreateStage()->GetStage()->GetHeight() / 700.0f;
	mLightRad = std::min(mLightRad, mMaxLightRad);
	mLightRad = std::max(mLightRad, mMinLightRad);
}

void StageObject::AddPatrolRange(bool isPlus) {
	if (isPlus)mPatrolRange++;
	else mPatrolRange--;
	mPatrolRange = std::max(1, mPatrolRange);
	AdjustPatrolRange();
}

void StageObject::AdjustPatrolRange() {
	switch (mClockwise) {
	case 0:
		mPatrolRange = std::min(mPatrolRange,mIteration.first+1);
		break;
	case 1:
		mPatrolRange = std::min(mPatrolRange,
			GetCreateStage()->GetStage()->GetSideSize()- mIteration.second);
		break;
	case 2:
		mPatrolRange = std::min(mPatrolRange,
			GetCreateStage()->GetStage()->GetVerticalSize() - mIteration.first);
		break;
	case 3:
		mPatrolRange = std::min(mPatrolRange, mIteration.second+1);
		break;
	}
}



Vec2 StageObject::GetLeftTop() {
	return Vec2({ GetPosition().x - mWidth / 2.0f - 0.001f,GetPosition().y + mHeight / 2.0f + 0.001f });
}

Vec2 StageObject::GetRightTop() {
	return Vec2({ GetPosition().x + mWidth / 2.0f + 0.001f,GetPosition().y + mHeight / 2.0f + 0.001f });
}

Vec2 StageObject::GetRightBottom() {
	return Vec2({ GetPosition().x + mWidth / 2.0f + 0.001f,GetPosition().y - mHeight / 2.0f - 0.001f });
}

Vec2 StageObject::GetLeftBottom() {
	return Vec2({ GetPosition().x - mWidth / 2.0f - 0.001f,GetPosition().y - mHeight / 2.0f - 0.001f });
}

Vec2 StageObject::GetExpandFulcrum(int i) {
	if (i == 0)return GetRightBottom();
	else if (i == 1)return GetLeftBottom();
	else if (i == 2)return GetLeftTop();
	else return GetRightTop();
}

void StageObject::UpdateStageMenu_CreateStage(float deltaTime) {

}

void StageObject::DrawStageMenu_CreateStage() {
	
}

void StageObject::InitializeStageMenu_CreateStage() {

}

void StageObject::ShutdownStageMenu_CreateStage() {

}




float ConvertToSpeed(float barMin, float barWidth, float pos) {
	return (pos - barMin) / barWidth * 100.0f;
}


//Game///////////////////////////////////////////////////////////////
void StageObject::InitializeActor_Game(class Game* game) {
	Initialize_Game(game);
	sqc = new SquareComponent(this,50,DrawingComponent::DrawingState::UNAFFECTED); 
	sqc->InitializeDrawing_Game(mCenter, mWidth, mHeight);

	sc = new SpriteComponent(this, 70, DrawingComponent::DrawingState::UNAFFECTED);
	sc->InitializeDrawing_Game(mCenter, mWidth, mHeight);

	switch (mAttribute) {
	case Attribute::Wall:
		sqc->SetColor(ColorF(0.5f));
		sc->SetTexture(TextureAsset(U"brock_stone"));
		break;
	case Attribute::Brock:
		sqc->SetColor(ColorF(1, 1, 1));
		switch (mMaterial) {
		case Material::Stone:
			sc->SetTexture(TextureAsset(U"brock_stone"));
			break;
		case Material::Grass:
			sc->SetTexture(TextureAsset(U"brock_grass"));
			break;
		case Material::Wood:
			sc->SetTexture(TextureAsset(U"brock_wood"));
			break;
		}
		sc->SetTexture(TextureAsset(U"brock_stone"));
		break;
	case Attribute::Door:
		sqc->SetColor(ColorF(0, 0, 0));
		sc->SetTexture(TextureAsset(U"Door_front"));
		break;
	case Attribute::Patrol:
		sqc->SetColor(ColorF(0, (float)102 / 255, 0));
		sc->SetIsDraw(false);
		break;
	case Attribute::Key:
		sqc->SetColor(ColorF((float)76 / 255, (float)0, (float)153 / 255));
		sc->SetTexture(TextureAsset(U"key"));
		break;
	case Attribute::Battery:
		sqc->SetColor(ColorF(0, 1, 128.0f / 255.0f));
		sc->SetTexture(TextureAsset(U"battery"));
		break;
	case Attribute::TreasureChest:
		sqc->SetColor(ColorF(1, 1, 0));
		sc->SetTexture(TextureAsset(U"treasure"));
		break;
	case Attribute::Candle:
		sqc->SetColor(ColorF(1, 1, 1));
		sc->SetTexture(TextureAsset(U"candle"));
		break;
	case Attribute::Ghost:
		sqc->SetColor(ColorF(76.0f / 255.0f, 0, 204.0f / 255.0f));
		break;
	case Attribute::Escapee1:
		sqc->SetColor(ColorF(204.0f / 255.0f, 0, 204.0f / 255.0f));
		break;
	case Attribute::Escapee2:
		sqc->SetColor(ColorF(102.0f / 255.0f, 178.0f / 255.0f, 1));
		break;
	case Attribute::Escapee3:
		sqc->SetColor(ColorF(153.0f / 255.0f, 1.0f, 153.0f / 255.0f));
		break;
	}

	if (mAttribute == Attribute::Door) {
		mObjectLeft = GetDoorCenter().x - GetDoorWidth() / 2.0f;
		mObjectRight = GetDoorCenter().x + GetDoorWidth() / 2.0f;
		mObjectUp = GetDoorCenter().y + GetDoorHeight() / 2.0f;
		mObjectDown = GetDoorCenter().y - GetDoorHeight() / 2.0f;
	}
	else {
		mObjectLeft = GetPosition().x - GetWidth() / 2.0f;
		mObjectRight = GetPosition().x + GetWidth() / 2.0f;
		mObjectUp = GetPosition().y + GetHeight() / 2.0f;
		mObjectDown = GetPosition().y - GetHeight() / 2.0f;
	}

	LineL = { {mObjectLeft,mObjectUp},{mObjectLeft,mObjectDown} };
	LineR = { {mObjectRight,mObjectUp},{mObjectRight,mObjectDown} };
	LineU = { {mObjectRight,mObjectUp},{mObjectLeft,mObjectUp} };
	LineD = { {mObjectLeft,mObjectDown},{mObjectRight,mObjectDown} };

}

void StageObject::InitializeStageObject_Game(class Game* game) {
	InitializeActor_Game(game);
}

void StageObject::InitializeStage_Game() {

}

void StageObject::UpdateActor_Game(float deltaTime) {
	UpdateStageObject_Game(deltaTime);
}

void StageObject::UpdateStageObject_Game(float deltaTime) {

}
