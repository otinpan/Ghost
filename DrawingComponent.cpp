#include"DrawingComponent.h"
#include"Game.h"
#include"CreateStage.h"
#include"Actor.h"

DrawingComponent::DrawingComponent(
	Actor* owner,
	int drawOrder,
	DrawingState drawState
)
	: Component(owner)
	, mDrawOrder(drawOrder)
	, mDrawingState(drawState)
	, mIsDraw(true)
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

void DrawingComponent::SetDrawingState_Game(DrawingState drawState, Game* game) {
	game->RemoveDrawing(this);
	mDrawingState = drawState;
	game->AddDrawing(this);
}

void DrawingComponent::SetDrawingState_CreateStage(DrawingState drawState, CreateStage* createStage) {
	createStage->RemoveDrawing(this);
	mDrawingState = drawState;
	createStage->AddDrawing(this);
}
