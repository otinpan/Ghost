#include"Door.h"

Door::Door(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
{
	SetAttribute(Attribute::Door);
}

Door::~Door() {

}


void Door::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
	sc = new SquareComponent(this);
	DoorWidth = { GetWidth(),GetWidth() / 4,GetWidth(),GetWidth() / 4 };
	DoorHeight = { GetHeight() / 4,GetHeight(),GetHeight() / 4,GetHeight() };
	DoorRel_dx = { 0,GetWidth() * 3 / 8,0,-GetWidth() * 3 / 8 };
	DoorRel_dy = { GetHeight() * 3 / 8,0,-GetHeight() * 3 / 8,0 };
	mDoorCenter = Vec2{ GetPosition().x + DoorRel_dx[0],GetPosition().y + DoorRel_dy[0] };
	sc->Initialize_CreateStage(mDoorCenter, DoorWidth[0], DoorHeight[0]);
}

void Door::UpdateStageObject_CreateStage(float deltaTime) {
	mDoorCenter = Vec2{GetPosition().x + DoorRel_dx[GetClockwise()],GetPosition().y + DoorRel_dy[GetClockwise()]};
	mDoorHeight = DoorHeight[GetClockwise()];
	mDoorWidth = DoorWidth[GetClockwise()];
	sc->SetCenter(mDoorCenter);
	sc->SetWidth(mDoorWidth);
	sc->SetHeight(mDoorHeight);
	sc->SetColor(ColorF(0, 1, 1));
}

