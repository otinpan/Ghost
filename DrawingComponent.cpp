#include"DrawingComponent.h"
#include"Game.h"
#include"CreateStage.h"
#include"Actor.h"

DrawingComponent::DrawingComponent(Actor* owner,int drawOrder,bool isBackground)
	:Component(owner)
	,mDrawOrder(drawOrder)
	,mIsBackground(isBackground)
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
