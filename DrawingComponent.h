#pragma once
#include"Component.h"

class DrawingComponent :public Component {
public:
	enum DrawState {
		BACK,
		FRONT,
		UNAFFECTED,
	};

	DrawingComponent(class Actor* owner,int drawOrder,DrawState drawState);
	~DrawingComponent();


	void Initialize_Game();
	void Initialize_CreateStage();

	virtual void Draw();

	int GetDrawOrder()const { return mDrawOrder; }
	DrawState GetDrawState() const{ return mDrawState; }
	void SetIsDraw(bool isDraw) { mIsDraw = isDraw; }
	bool GetIsDraw() const{ return mIsDraw; }

private:
	int mDrawOrder;
	bool mIsDraw;
	DrawState mDrawState;
};
