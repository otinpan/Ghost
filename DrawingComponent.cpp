#include"DrawingComponent.h"
#include"Game.h"
#include"CreateStage.h"
#include"Actor.h"

DrawingComponent::DrawingComponent(Actor* owner,int drawOrder,DrawState drawState)
	:Component(owner)
	,mDrawOrder(drawOrder)
	,mDrawState(drawState)
	,mIsDraw(true)
{

}

DrawingComponent::~DrawingComponent() {
	if(mOwner->GetGame())mOwner->GetGame()->RemoveDrawing(this);
	if (mOwner->GetCreateStage())mOwner->GetCreateStage()->RemoveDrawing(this);

}


void DrawingComponent::Initialize_Game() {
	mOwner->GetGame()->AddDrawing(this);
}


void DrawingComponent::Initialize_CreateStage() {
	mOwner->GetCreateStage()->AddDrawing(this);
}



void DrawingComponent::Draw() {

}

void DrawingComponent::SetDrawState_Game(DrawState drawState, Game* game) {
	game->RemoveDrawing(this);
	mDrawState = drawState;
	game->AddDrawing(this);
}

void DrawingComponent::SetDrawState_CreateStage(DrawState drawState, CreateStage* createStage) {
	createStage->RemoveDrawing(this);
	mDrawState = drawState;
	createStage->AddDrawing(this);
}
