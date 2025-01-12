#pragma once
#include"Component.h"

class DrawingComponent :public Component {
public:
	DrawingComponent(class Actor* owner,int drawOrder,bool isBackground);
	~DrawingComponent();

	void Initialize_Game();
	void Initialize_CreateStage();

	virtual void Draw();

	int GetDrawOrder()const { return mDrawOrder; }
	bool GetIsBackground() const { return mIsBackground; }
	void SetIsDraw(bool isDraw) { mIsDraw = isDraw; }
	bool GetIsDraw() { return mIsDraw; }

private:
	int mDrawOrder;
	bool mIsDraw;
	bool mIsBackground;
};
