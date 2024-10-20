#include"Brock.h"
#include"StageMenu.h"

Brock::Brock(Vec2 pos,float width, float height)
	:StageObject(pos,width,height)
{
	SetAttribute(Attribute::Brock);
}

void Brock::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
	StoneSC = 0;
	WoodSC = 0;
	GrassSC = 0;
}

void Brock::UpdateStageObject_CreateStage(float deltaTime) {
}

Brock::~Brock() {
	
}

void Brock::InitializeStageMenu_CreateStage() {
	EachWidth_StageMenu = GetCreateStage()->GetStageMenu()->GetMenuWidth() / 3.0f;
	RectWidth_StageMenu = EachWidth_StageMenu / 2.0f;
	RectHeight_StageMenu = RectWidth_StageMenu;
	StoneSC = new SquareComponent(this);
	WoodSC = new SquareComponent(this);
	GrassSC = new SquareComponent(this);

	StoneSC->Initialize_CreateStage(Vec2{ GetCreateStage()->GetStageMenu()->GetMenuLeft()+EachWidth_StageMenu / 2,
		(GetCreateStage()->GetStageMenu()->GetMenuUp()
			+ GetCreateStage()->GetStageMenu()->GetMenuDown()) / 2 },
		RectWidth_StageMenu, RectHeight_StageMenu);
	WoodSC->Initialize_CreateStage(Vec2{ GetCreateStage()->GetStageMenu()->GetMenuLeft() + EachWidth_StageMenu+ EachWidth_StageMenu / 2,
		(GetCreateStage()->GetStageMenu()->GetMenuUp()
			+ GetCreateStage()->GetStageMenu()->GetMenuDown()) / 2 },
		RectWidth_StageMenu, RectHeight_StageMenu);
	GrassSC->Initialize_CreateStage(Vec2{ GetCreateStage()->GetStageMenu()->GetMenuLeft() + EachWidth_StageMenu*2 + EachWidth_StageMenu / 2,
		(GetCreateStage()->GetStageMenu()->GetMenuUp()
			+ GetCreateStage()->GetStageMenu()->GetMenuDown()) / 2 },
		RectWidth_StageMenu, RectHeight_StageMenu);
}

void Brock::UpdateStageMenu_CreateStage(float deltaTime) {

}

void Brock::DrawStageMenu_CreateStage() {

}

void Brock::ShutdownStageMenu_CreateStage() {
	delete StoneSC;
	delete WoodSC;
	delete GrassSC;
}


