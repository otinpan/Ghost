#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"


SpriteComponent::SpriteComponent(Actor* owner, float worldTexWidth,
	float worldTexHeight, Vec2 diff, int drawOrder)
	:Component(owner)
	, mTexture()
	, mDrawOrder(drawOrder)
	, WorldTexWidth(worldTexWidth)
	, WorldTexHeight(worldTexHeight)
	, Diff(diff)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw() {
	float WritingWidth = (float)WorldTexWidth / 2.0 *
		GetScreenWidth();
	float WritingHeight = (float)WorldTexHeight / 2.0 *
		GetScreenHeight();

	Vec2 WritingPos = mOwner->GetPosition() + Diff;

	mTexture.resized(WritingWidth, WritingHeight).drawAt(ConvertToView(WritingPos));
}


void SpriteComponent::SetTexture(Texture texture) {
	TexWidth = texture.width();
	TexHeight = texture.height();
	mTexture = texture;
}
