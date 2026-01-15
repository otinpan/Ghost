#include "SpriteComponent.h"
#include "Actor.h"


SpriteComponent::SpriteComponent(Actor* owner, int drawOrder, DrawingComponent::DrawingState drawState)
	:DrawingComponent(owner, drawOrder, drawState)
	, mTexture()
	, mDrawOrder(drawOrder)
	, mRotation(0.0f)
	, mScale(1.0f)
{
}

SpriteComponent::~SpriteComponent() {
}

void SpriteComponent::InitializeDrawing_Game(Vec2 pos,float width,float height) {
	Initialize_Game();
	mCenter = pos;
	mWorldTexWidth = width;
	mWorldTexHeight = height;
}

void SpriteComponent::InitializeDrawing_CreateStage(Vec2 pos,float width,float height) {
	Initialize_CreateStage();
	mCenter = pos;
	mWorldTexWidth = width;
	mWorldTexHeight = height;
}

void SpriteComponent::Draw() {
	if (!GetIsDraw())return;
	float WritingWidth = (float)mWorldTexWidth / 2.0 *
		GetScreenWidth();
	float WritingHeight = (float)mWorldTexHeight / 2.0 *
		GetScreenHeight();



	mTexture.resized(WritingWidth, WritingHeight).
		scaled(mScale).rotated(mRotation).
		drawAt(ConvertToView(mCenter));
}


void SpriteComponent::SetTexture(Texture texture) {
	mTexWidth = texture.width();
	mTexHeight = texture.height();
	mTexture = texture;
}
