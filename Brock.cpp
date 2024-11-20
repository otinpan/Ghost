#include"Brock.h"
#include"StageMenu.h"
#include"Hand.h"

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
	switch (mMaterial) {
	case Material::Wood:
		GetSquareComponent()->SetColor(ColorF(102.0f / 255.0f, 51.0f / 255.0f,0));
		break;
	case Material::Stone:
		GetSquareComponent()->SetColor(ColorF(128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f));
		break;
	case Material::Grass:
		GetSquareComponent()->SetColor(ColorF(153.0f / 255.0f, 1, 51.0f / 255.0f));
		break;
	}

}

Brock::~Brock() {
	
}

void Brock::InitializeStageMenu_CreateStage() {
	EachWidth_StageMenu = GetCreateStage()->GetStageMenu()->GetMenuWidth() / 3.0f;
	EachHeight_StageMenu = GetCreateStage()->GetStageMenu()->GetMenuHeight() / 3;
	RectHeight_StageMenu = EachHeight_StageMenu / 2.0f;
	RectWidth_StageMenu = RectHeight_StageMenu*GetScreenHeight()/GetScreenWidth();
	StoneSC = new SquareComponent(this);
	WoodSC = new SquareComponent(this);
	GrassSC = new SquareComponent(this);

	WoodSC->Initialize_CreateStage(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft()+GetCreateStage()->GetStageMenu()->GetMenuRight())/2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp()-EachHeight_StageMenu/2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu);
	WoodSC->SetColor(ColorF(102.0f / 255.0f, 51.0f / 255.0f,0));
	StoneSC->Initialize_CreateStage(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp() - EachHeight_StageMenu*3.0f / 2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu);
	StoneSC->SetColor(ColorF(128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f));
	GrassSC->Initialize_CreateStage(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp() - EachHeight_StageMenu *5.0f/ 2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu);
	GrassSC->SetColor(ColorF(153.0f/255.0f, 1, 51.0f / 255.0f));

	mMaterial = Material::Stone;
}

void Brock::UpdateStageMenu_CreateStage(float deltaTime) {
	if (GetCreateStage()->GetHand()->GetInputChoose().down()) {
		if (GetCreateStage()->GetHand()->GetCircleComponent()->GetCircle()
			.intersects(WoodSC->GetRect())) {
			mMaterial = Material::Wood;
		}
		else if (GetCreateStage()->GetHand()->GetCircleComponent()->GetCircle()
		   .intersects(StoneSC->GetRect())) {
			mMaterial = Material::Stone;
		}else if(GetCreateStage()->GetHand()->GetCircleComponent()->GetCircle()
			.intersects(GrassSC->GetRect())) {
			mMaterial=Material::Grass;
		}
	}

	if (mMaterial == Material::Wood) {
		if (GetCreateStage()->GetHand()->GetInputD().down())
			mMaterial = Material::Stone;
	}
	else if (mMaterial == Material::Stone) {
		if (GetCreateStage()->GetHand()->GetInputD().down()) {
			mMaterial = Material::Grass;
		}
		if (GetCreateStage()->GetHand()->GetInputU().down()) {
			mMaterial = Material::Wood;
		}
	}
	else if (mMaterial == Material::Grass) {
		if (GetCreateStage()->GetHand()->GetInputU().down()) {
			mMaterial = Material::Stone;
		}
	}


}

void Brock::DrawStageMenu_CreateStage() {
	switch (mMaterial) {
	case Material::Wood:
		DrawRectFrame(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp() - EachHeight_StageMenu / 2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu,0,0.002f,ColorF(1,1,0));
		break;
	case Material::Stone:
		DrawRectFrame(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp() - EachHeight_StageMenu * 3.0f / 2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu, 0,0.002f, ColorF(1, 1, 0));
		break;
	case Material::Grass:
		DrawRectFrame(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp() - EachHeight_StageMenu * 5.0f / 2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu, 0,0.002f, ColorF(1, 1, 0));
		break;
	}
}

void Brock::ShutdownStageMenu_CreateStage() {
	delete StoneSC;
	delete WoodSC;
	delete GrassSC;
}

void Brock::InitializeStageObject_Game(class Game* game) {
	InitializeActor_Game(game);
}

void Brock::UpdateStageObject_Game(float deltaTime) {

}


