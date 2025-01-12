#include "SpriteComponent.h"
#include "Actor.h"


SpriteComponent::SpriteComponent(Actor* owner, int drawOrder,bool isBackground)
	:DrawingComponent(owner,drawOrder,isBackground)
	, mTexture()
	, mDrawOrder(drawOrder)
{

}

SpriteComponent::~SpriteComponent() {
}

void SpriteComponent::InitializeDrawing_Game(float worldTexWidth, float worldTexHeight, Vec2 diff) {
	Initialize_Game();
	mWorldTexWidth = worldTexWidth;
	mWorldTexHeight = worldTexHeight;
	mDiff = diff;
}

void SpriteComponent::InitializeDrawing_CreateStage(float worldTexWidth, float worldTexHeight, Vec2 diff) {
	Initialize_CreateStage();
}

void SpriteComponent::Draw() {
	if (!GetIsDraw())return;
	float WritingWidth = (float)mWorldTexWidth / 2.0 *
		GetScreenWidth();
	float WritingHeight = (float)mWorldTexHeight / 2.0 *
		GetScreenHeight();

	Vec2 WritingPos = mOwner->GetPosition() + mDiff;

	mTexture.resized(WritingWidth, WritingHeight).drawAt(ConvertToView(WritingPos));
}


void SpriteComponent::SetTexture(Texture texture) {
	mTexWidth = texture.width();
	mTexHeight = texture.height();
	mTexture = texture;
}
