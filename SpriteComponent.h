#pragma once
#include "DrawingComponent.h"


//引数は初期値を指定したもの(drawOrder=100)を一番後ろに持ってゆく必要がある
//そうでないとエラーが出てくる
class SpriteComponent :public DrawingComponent {
public:
	SpriteComponent(class Actor* owner, int drawOrder,DrawState drawState);
	~SpriteComponent();

	void InitializeDrawing_Game(Vec2 pos,float width, float height);
	void InitializeDrawing_CreateStage(Vec2 pos,float width,float height);

	void Draw() override;
    void SetTexture(Texture texture);

	int GetDrawOrder() const { return mDrawOrder; }
	float GetTexHeight() const { return mWorldTexHeight; }
	float GetTexWidth() const { return mWorldTexWidth; }
	Vec2 GetCenter() const { return mCenter; }
	void SetCenter(Vec2 pos) { mCenter = pos; }

private:
	int mDrawOrder;
	Vec2 mDiff;   //Actorの中心からどれだけ離れたところにあるか

	//元の画像の大きさ
	float mTexWidth;
	float mTexHeight;

	//ワールド座標での画像の大きさ（描画したい画像の大きさ)
	float mWorldTexWidth;
	float mWorldTexHeight;
	Vec2 mCenter;

	Texture mTexture;


};
