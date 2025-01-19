#include"Door.h"
#include"CreateStage.h"
#include"StageMenu.h"
#include"Hand.h"

Door::Door(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
{
	SetAttribute(Attribute::Door);
}

Door::~Door() {

}


void Door::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
	DoorWidth = { GetWidth(),GetWidth() / 4,GetWidth(),GetWidth() / 4 };
	DoorHeight = { GetHeight() / 4,GetHeight(),GetHeight() / 4,GetHeight() };
	DoorRel_dx = { 0,GetWidth() * 3 / 8,0,-GetWidth() * 3 / 8 };
	DoorRel_dy = { GetHeight() * 3 / 8,0,-GetHeight() * 3 / 8,0 };
    SetDoorCenter( Vec2{ GetPosition().x + DoorRel_dx[0],GetPosition().y + DoorRel_dy[0] });
	GetSquareComponent()->InitializeDrawing_CreateStage(GetDoorCenter(), DoorWidth[0], DoorHeight[0]);
}

void Door::UpdateStageObject_CreateStage(float deltaTime) {
	SetDoorCenter(Vec2{GetPosition().x + DoorRel_dx[GetClockwise()],GetPosition().y + DoorRel_dy[GetClockwise()]});
	SetDoorHeight ( DoorHeight[GetClockwise()]);
	SetDoorWidth  (DoorWidth[GetClockwise()]);
	GetSquareComponent()->SetCenter(GetDoorCenter());
	GetSquareComponent()->SetWidth(GetDoorWidth());
	GetSquareComponent()->SetHeight(GetDoorHeight());
	GetSquareComponent()->SetColor(ColorF(0, 1, 1));
}

void Door::InitializeStageMenu_CreateStage() {
	mTriCenter = Vec2(
		(GetCreateStage()->GetStageMenu()->GetMenuRight() + GetCreateStage()->GetStageMenu()->GetMenuLeft()) / 2.0f,
		(GetCreateStage()->GetStageMenu()->GetMenuUp() + GetCreateStage()->GetStageMenu()->GetMenuDown()) / 2.0f
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
		mTriCenter.x+mTriLengthFromCenter,
		mTriCenter.y 
	);
	mLeftTriPos = Vec2(
		mTriCenter.x - mTriLengthFromCenter,
		mTriCenter.y
	);
	

	mUpCC = new CircleComponent(this,10,true);
	mUpCC->InitializeDrawing_CreateStage();
	mUpCC->SetCenter(mUpTriPos);
	mUpCC->SetRadius(mTriLength);
	mUpCC ->SetColor(ColorF(1.0, 1.0, 0.0, 0));
	mUpCC->SetIsDraw(false);

	mDownCC = new CircleComponent(this,10,true);
	mDownCC->InitializeDrawing_CreateStage();
	mDownCC->SetCenter(mDownTriPos);
	mDownCC->SetRadius(mTriLength);
	mDownCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));
	mDownCC->SetIsDraw(false);

	mRightCC = new CircleComponent(this,10,true);
	mRightCC->InitializeDrawing_CreateStage();
	mRightCC->SetCenter(mRightTriPos);
	mRightCC->SetRadius(mTriLength);
	mRightCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));
	mRightCC->SetIsDraw(false);

	mLeftCC = new CircleComponent(this,10,true);
	mLeftCC->InitializeDrawing_CreateStage();
	mLeftCC->SetCenter(mLeftTriPos);
	mLeftCC->SetRadius(mTriLength);
	mLeftCC->SetColor(ColorF(1.0, 1.0, 0.0, 0));
	mLeftCC->SetIsDraw(false);
	return;
}

void Door::UpdateStageMenu_CreateStage(float deltaTime) {
	if(GetCreateStage()->GetHand()->GetInputU().down()){
		SetClockwise(0);
	}
	if (GetCreateStage()->GetHand()->GetInputR().down()) {
		SetClockwise(1);
	}
	if (GetCreateStage()->GetHand()->GetInputD().down()) {
		SetClockwise(2);
	}
	if (GetCreateStage()->GetHand()->GetInputL().down()) {
		SetClockwise(3);
	}

	if (GetCreateStage()->GetHand()->GetInputChoose().down()) {
		if (IsIntersect_CC(GetCreateStage()->GetHand()->GetCircleComponent(), mUpCC)) {
			SetClockwise(0);
		}
		if (IsIntersect_CC(GetCreateStage()->GetHand()->GetCircleComponent(), mRightCC)) {
			SetClockwise(1);
		}
		if (IsIntersect_CC(GetCreateStage()->GetHand()->GetCircleComponent(), mDownCC)) {
			SetClockwise(2);
		}
		if (IsIntersect_CC(GetCreateStage()->GetHand()->GetCircleComponent(), mLeftCC)) {
			SetClockwise(3);
		}
	}
}

void Door::DrawStageMenu_CreateStage() {
	if (GetClockwise() != 0) {
		DrawTriangle(mUpTriPos, mTriLength, 0, ColorF(0, 0, 0));
	}
	else {
		DrawTriangle(mUpTriPos, mTriLength, 0, ColorF(1, 1, (float)102 / 255));
	}
	if (GetClockwise() != 1) {
		DrawTriangle(mRightTriPos, mTriLength, 90_deg, ColorF(0, 0, 0));
	}
	else {
		DrawTriangle(mRightTriPos, mTriLength, 90_deg, ColorF(1, 1, (float)102 / 255));
	}
	if (GetClockwise() != 2) {
		DrawTriangle(mDownTriPos, mTriLength, 180_deg, ColorF(0, 0, 0));
	}
	else {
		DrawTriangle(mDownTriPos, mTriLength, 180_deg, ColorF(1, 1, (float)102 / 255));
	}
	if (GetClockwise() != 3) {
		DrawTriangle(mLeftTriPos, mTriLength, 270_deg, ColorF(0, 0, 0));
	}
	else {
		DrawTriangle(mLeftTriPos, mTriLength, 270_deg, ColorF(1, 1, (float)102 / 255));
	}
}

void Door::ShutdownStageMenu_CreateStage() {
	delete mUpCC;
	delete mDownCC;
	delete mRightCC;
	delete mLeftCC;
	return;
}

void Door::InitializeStageObject_Game(class Game* game) {
	InitializeActor_Game(game);
	DoorWidth = { GetWidth(),GetWidth() / 4,GetWidth(),GetWidth() / 4 };
	DoorHeight = { GetHeight() / 4,GetHeight(),GetHeight() / 4,GetHeight() };
	DoorRel_dx = { 0,GetWidth() * 3 / 8,0,-GetWidth() * 3 / 8 };
	DoorRel_dy = { GetHeight() * 3 / 8,0,-GetHeight() * 3 / 8,0 };
	GetSquareComponent()->InitializeDrawing_Game(GetDoorCenter(), DoorWidth[GetClockwise()], DoorHeight[GetClockwise()]);
	
}

void Door::InitializeStage_Game() {
	SetDoorCenter(Vec2{ GetPosition().x + DoorRel_dx[GetClockwise()],GetPosition().y + DoorRel_dy[GetClockwise()] });
	SetDoorHeight(DoorHeight[GetClockwise()]);
	SetDoorWidth(DoorWidth[GetClockwise()]);
	GetSquareComponent()->SetCenter(GetDoorCenter());
	GetSquareComponent()->SetWidth(GetDoorWidth());
	GetSquareComponent()->SetHeight(GetDoorHeight());
	GetSquareComponent()->SetColor(ColorF(0, 1, 1));


	SetObjectLeft(GetDoorCenter().x - GetDoorWidth() / 2.0f);
	SetObjectRight(GetDoorCenter().x + GetDoorWidth() / 2.0f);
	SetObjectUp(GetDoorCenter().y + GetDoorHeight() / 2.0f);
	SetObjectDown(GetDoorCenter().y - GetDoorHeight() / 2.0f);
	SetLineL({ {GetObjectLeft(),GetObjectUp()},{GetObjectLeft(),GetObjectDown()} });
	SetLineR({ {GetObjectRight(),GetObjectUp()},{GetObjectRight(),GetObjectDown()} });
	SetLineU({ {GetObjectLeft(),GetObjectUp()},{GetObjectRight(),GetObjectUp()} });
	SetLineD({ {GetObjectLeft(),GetObjectDown()},{GetObjectRight(),GetObjectDown()} });
}

void Door::UpdateStageObject_Game(float deltaTime) {
	
}
