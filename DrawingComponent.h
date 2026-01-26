#pragma once
#include"Component.h"

class DrawingComponent :public Component {
public:
	enum DrawingState {
		BACK,
		FRONT,
		UNAFFECTED,
	};

	DrawingComponent(class Actor* owner,int drawOrder,DrawingState drawState);
	~DrawingComponent();


	void Initialize_Game();
	void Initialize_CreateStage();

	virtual void Draw();

	int GetDrawOrder()const { return mDrawOrder; }
	void SetDrawingState_Game(DrawingState drawState,class Game* game);
	void SetDrawingState_CreateStage(DrawingState drawState,class CreateStage* createStage);
	DrawingState GetDrawingState() const{ return mDrawingState; }
	void SetIsDraw(bool isDraw) { mIsDraw = isDraw; }
	bool GetIsDraw() const{ return mIsDraw; }
	void SetRotation(float rot) { mRotation = rot; }
	float GetRotation() { return mRotation; }

private:
	int mDrawOrder;
	bool mIsDraw;
	DrawingState mDrawingState;

	float mRotation = 0.0;
};
