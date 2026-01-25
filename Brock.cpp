#include"Brock.h"
#include"StageMenu.h"
#include"Hand.h"
#include"SpriteComponent.h"

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

void Brock::InitializeStage_CreateStage() {
	switch (GetMaterial()) {
	case Material::Wood:
		GetSpriteComponent()->SetTexture(TextureAsset(U"brock_wood"));
		break;
	case Material::Stone:
		GetSpriteComponent()->SetTexture(TextureAsset(U"brock_stone"));
		break;
	case Material::Grass:
		GetSpriteComponent()->SetTexture(TextureAsset(U"brock_grass"));
		break;
	}
}

void Brock::UpdateStageObject_CreateStage(float deltaTime) {
	switch (GetMaterial()) {
	case Material::Wood:
		GetSquareComponent()->SetColor(ColorF(102.0f / 255.0f, 51.0f / 255.0f,0));
		GetSpriteComponent()->SetTexture(TextureAsset(U"brock_wood"));
		break;
	case Material::Stone:
		GetSquareComponent()->SetColor(ColorF(128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f));
		GetSpriteComponent()->SetTexture(TextureAsset(U"brock_stone"));
		break;
	case Material::Grass:
		GetSquareComponent()->SetColor(ColorF(153.0f / 255.0f, 1, 51.0f / 255.0f));
		GetSpriteComponent()->SetTexture(TextureAsset(U"brock_grass"));
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
	StoneSC = new SquareComponent(this,200, DrawingComponent::DrawingState::UNAFFECTED);
	WoodSC = new SquareComponent(this,200, DrawingComponent::DrawingState::UNAFFECTED);
	GrassSC = new SquareComponent(this,200, DrawingComponent::DrawingState::UNAFFECTED);
	WoodSC->InitializeDrawing_CreateStage(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp() - EachHeight_StageMenu / 2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu);
	WoodSC->SetColor(ColorF(102.0f / 255.0f, 51.0f / 255.0f, 0));
	StoneSC->InitializeDrawing_CreateStage(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp() - EachHeight_StageMenu * 3.0f / 2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu);
	StoneSC->SetColor(ColorF(128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f));
	GrassSC->InitializeDrawing_CreateStage(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp() - EachHeight_StageMenu * 5.0f / 2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu);
	GrassSC->SetColor(ColorF(153.0f / 255.0f, 1, 51.0f / 255.0f));

	// SpriteComponent
	scStone = new SpriteComponent(this, 200, DrawingComponent::DrawingState::UNAFFECTED);
	scGrass = new SpriteComponent(this, 200, DrawingComponent::DrawingState::UNAFFECTED);
	scWood = new SpriteComponent(this, 200, DrawingComponent::DrawingState::UNAFFECTED);
	scStone->InitializeDrawing_CreateStage(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp() - EachHeight_StageMenu * 3.0f / 2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu);
	scGrass->InitializeDrawing_CreateStage(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp() - EachHeight_StageMenu * 5.0f / 2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu);
	scWood->InitializeDrawing_CreateStage(Vec2{
		(GetCreateStage()->GetStageMenu()->GetMenuLeft() + GetCreateStage()->GetStageMenu()->GetMenuRight()) / 2.0f,
		GetCreateStage()->GetStageMenu()->GetMenuUp() - EachHeight_StageMenu / 2.0f },
		RectWidth_StageMenu, RectHeight_StageMenu);
	scStone->SetTexture(TextureAsset(U"brock_stone"));
	scGrass->SetTexture(TextureAsset(U"brock_grass"));
	scWood->SetTexture(TextureAsset(U"brock_wood"));

	//SetMaterial(Material::Stone);
}

void Brock::UpdateStageMenu_CreateStage(float deltaTime) {
	if (GetCreateStage()->GetHand()->GetInputChoose().down()) {
		if (GetCreateStage()->GetHand()->GetCircleComponent()->GetCircle()
			.intersects(WoodSC->GetRect())) {
			SetMaterial(Material::Wood);
		}
		else if (GetCreateStage()->GetHand()->GetCircleComponent()->GetCircle()
		   .intersects(StoneSC->GetRect())) {
			SetMaterial(Material::Stone);
		}else if(GetCreateStage()->GetHand()->GetCircleComponent()->GetCircle()
			.intersects(GrassSC->GetRect())) {
			SetMaterial(Material::Grass);
		}
	}

	if (GetMaterial() == Material::Wood) {
		if (GetCreateStage()->GetHand()->GetInputD().down())
			SetMaterial(Material::Stone);
	}
	else if (GetMaterial() == Material::Stone) {
		if (GetCreateStage()->GetHand()->GetInputD().down()) {
			SetMaterial(Material::Grass);
		}
		if (GetCreateStage()->GetHand()->GetInputU().down()) {
			SetMaterial(Material::Wood);
		}
	}
	else if (GetMaterial() == Material::Grass) {
		if (GetCreateStage()->GetHand()->GetInputU().down()) {
			SetMaterial(Material::Stone);
		}
	}


}

void Brock::DrawStageMenu_CreateStage() {
	// 選択されていない場合は描かない
	switch (GetMaterial()) {
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
	delete scStone;
	delete scGrass;
	delete scWood;
}

void Brock::InitializeStageObject_Game(class Game* game) {
	InitializeActor_Game(game);
}

void Brock::UpdateStageObject_Game(float deltaTime) {

}

void Brock::InitializeStage_Game() {
	switch (GetMaterial()) {
	case Material::Wood:
		GetSpriteComponent()->SetTexture(TextureAsset(U"brock_wood"));
		break;
	case Material::Stone:
		GetSpriteComponent()->SetTexture(TextureAsset(U"brock_stone"));
		break;
	case Material::Grass:
		GetSpriteComponent()->SetTexture(TextureAsset(U"brock_grass"));
		break;
	}
}


