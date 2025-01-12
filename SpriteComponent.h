#pragma once
#include "DrawingComponent.h"


//引数は初期値を指定したもの(drawOrder=100)を一番後ろに持ってゆく必要がある
//そうでないとエラーが出てくる
class SpriteComponent :public DrawingComponent {
public:
	SpriteComponent(class Actor* owner, int drawOrder,bool isBackground);
	~SpriteComponent();

	void InitializeDrawing_Game(float worldTexWidth,float worldTexHeight,Vec2 diff);
	void InitializeDrawing_CreateStage(float worldTexWidth, float worldTexHeight, Vec2 diff);

	void Draw() override;
    void SetTexture(Texture texture);

	int GetDrawOrder() const { return mDrawOrder; }
	float GetTexHeight() const { return mWorldTexHeight; }
	float GetTexWidth() const { return mWorldTexWidth; }

private:
	int mDrawOrder;
	Vec2 mDiff;   //Actorの中心からどれだけ離れたところにあるか

	//元の画像の大きさ
	float mTexWidth;
	float mTexHeight;

	//ワールド座標での画像の大きさ（描画したい画像の大きさ)
	float mWorldTexWidth;
	float mWorldTexHeight;

	Texture mTexture;
};
