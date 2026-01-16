#pragma once
#include<Siv3D.hpp>
#include"Parent.h"
#include"CreateStage.h"
#include <atomic>
#include <mutex>
#include <optional>
#include <thread>

struct DetailsOutput;

class GPTMenu {
public:
	GPTMenu();
	~GPTMenu();


	enum SelectedButton {
		SEND,
		CLOSE,
		NONE
	};

	using DrawFunc = std::function<void(const Vec2&, float, float,ColorF)>;


	void Initialize_CreateStage(class CreateStage* createStage);

	void Update(float deltaTime);
	void Draw() const;

	const DrawFunc& getFunc(size_t index) const;
	

private:
	class CreateStage* mCreateStage;

	// 全体
	Vec2 mBackgroundRectPos;  //背景の領域の位置
	float mBackgroundRectWidth;
	float mBackgroundRectHeight;
	ColorF mBackgroundRectColor;

	// 送信ボタン
	Vec2 mSendRectPos;
	float mSelectRectWidth;
	float mSelectRectHeight;

	// 終了
	Vec2 mCloseRectPos;

	Font selectFont;

	// 入力
	Input inputUp;
	Input inputDown;
	Input inputRight;
	Input inputLeft;
	InputGroup inputDecision;

	// selected button
	SelectedButton mSelectedButton = SelectedButton::CLOSE;

	// gpt
	int mWidth;
	int mHeight;
	// スレッド
	std::atomic<bool> mIsCreating{ false };
	std::thread mWorker;

	struct GeneratedResult {
		std::vector<std::string> layout;
		std::unique_ptr<DetailsOutput> details;
	};

	mutable std::mutex mResultMutex;
	std::optional<GeneratedResult> mPendingResult;
	std::optional<std::string> mPendingError;

	void StartCreateStageAsync();
	void PollCreateStageResult();
	void CancelOrJoinWorker();

	bool CreateStage();
	std::array<DrawFunc,3> mFuncs;
	
	int mLoadIndex = 0;

	bool EndGPTMenu_CreateStage();
};




