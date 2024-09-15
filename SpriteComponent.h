#pragma once
#include "Component.h"


//引数は初期値を指定したもの(drawOrder=100)を一番後ろに持ってゆく必要がある
//そうでないとエラーが出てくる
class SpriteComponent :public Component {
public:
	SpriteComponent(class Actor* owner, float worldTexWidth,
		float worldTexHeight, Vec2 diff, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw();
	virtual void SetTexture(Texture texture);

	int GetDrawOrder() const { return mDrawOrder; }
	float GetTexHeight() const { return WorldTexHeight; }
	float GetTexWidth() const { return WorldTexWidth; }

private:
	int mDrawOrder;
	Vec2 Diff;   //Actorの中心からどれだけ離れたところにあるか

	//元の画像の大きさ
	float TexWidth;
	float TexHeight;

	//ワールド座標での画像の大きさ（描画したい画像の大きさ)
	float WorldTexWidth;
	float WorldTexHeight;

	Texture mTexture;
};
