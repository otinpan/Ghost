#pragma once
#include"Parent.h"
#include"Actor.h"
using namespace std;

class StageSelect {
public:
	StageSelect();
	~StageSelect();

	void update(class Parent*);
	void draw_Game();
	void draw_CreateStage();

	void Initialize();
	void Shutdown();

	void moveTo(Parent* parent, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }

private:
	void ProcessInput();
	void UpdateStageSelect_Game();
	void UpdateStageSelect_CreateStage();
	bool InitializeStages();   //Initialize mStageNames
	void RemakeStageVector(); //mStageNamesを再構築する

	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputLeft;
	InputGroup inputRight;
	InputGroup inputDecision;
	InputGroup inputBack;

	bool mIsinputUp;
	bool mIsinputDown;
	bool mIsinputRight;
	bool mIsinputLeft;
	float minputUpTime;
	float minputDownTime;
	float minputRightTime;
	float minputLeftTime;


	vector<vector<Texture>> mStageTextures; //Stageのテクスチャ
	vector<vector<String>> mStageNames; //Stageの名前
	vector<vector<bool>> mIsInStage;  //Stageが入っているか
	vector<vector<Vec2>> mStagePoses; //Stageの位置(中心座標)
	int mVerticalSize;
	int mSideSize;
	int mDisplayVerticalSize;
	int mDisplaySideSize;
	float mStageWidth; //表示範囲
	float mStageHeight;
	float mStageRectWidth; //表示するStageの幅
	float mStageRectHeight;
	float mStageEachWidth; //それぞれのRectが所有する範囲
	float mStageEachHeight;
	float mStageLeft; //表示範囲の左端
	float mStageRight;
	float mStageUp;
	float mStageDown;

	float mTopPos; //一番上の移動量
	float MaxTopPos;
	float MaxDownPos;

	Vec2 mSideBarPos;
	float SideBarUp;
	float SideBarDown;
	float mSideBarUp;
	float mSideBarDown;
	float mSideBarWidth;
	float mSideBarHeight;


	pair<int, int> mIteration; //いま選択しているstageのIteration
	int mUpLine; //完全位映りきっている一番上の行
	int mDownLine; //完全に映りきっている一番下の行

	void UpdateRectPos(int plus); //plusの方向に平行移動する
	void UpdateinputCooltime(bool &mIsinput, float &minputTime,float deltaTime);


	bool mIsRunning;

	Parent::SeqID mSeqID;
	
};
