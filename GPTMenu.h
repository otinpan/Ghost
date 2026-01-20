#pragma once
#include<Siv3D.hpp>
#include"Parent.h"
#include"CreateStage.h"
#include <atomic>
#include <mutex>
#include <optional>
#include <thread>

struct DetailsOutput;

struct CharPos {
	size_t index;   // mText内の文字index
	Vec2 pos;       // その文字の描画基準位置（penPos）
	int line;       // 行番号
};

struct LayoutResult {
	Array<CharPos> chars;
	Array<size_t> lineBegin; // 各行の先頭index（mTextのindex）
	Array<size_t> lineEnd;   // 各行の末尾の次（[begin,end)）
	Vec2 cursorPos;          // カーソル描画位置
};

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
	void Draw() ;

	const DrawFunc& getFunc(size_t index) const;

	bool editing() const { return TextInput::GetEditingText() || mTimerNotEditing.sF() < 0.5f; }
	

private:
	class CreateStage* mCreateStage;

	// 全体
	Vec2 mBackgroundRectPos;  //背景の領域の位置
	float mBackgroundRectWidth;
	float mBackgroundRectHeight;

	// 送信ボタン
	Vec2 mSendRectPos;
	float mSelectRectWidth;
	float mSelectRectHeight;

	// 終了
	Vec2 mCloseRectPos;

	Font selectFont;

	// 入力
	bool mIsTextMode;
	Input inputUp;
	Input inputDown;
	Input inputRight;
	Input inputLeft;
	InputGroup inputDecision;

	// text入力領域
	Vec2 mTextRectPos;
	float mTextRectWidth;
	float mTextRectHeight;
	// text入力色
	ColorF mTextRectColor;
	ColorF mTextColor;
	ColorF mCursorColor;
	ColorF EditingTextColor;
	ColorF EditingTextBgColor;
	// カーソル
	float mCursorWidth;
	size_t mCursorPos;
	size_t MaxTextSize;
	bool mIsTextDecide;
	String mText;
	std::set<char> ValidInput;
	Stopwatch mTimerNotEditing;
	// スクロール
	float mScrollY = 0.0f; //スクロール量
	bool mWasComposed = false;
	bool mSwallowEnterOnce = false;
	void EnsureCursorVisible(const LayoutResult& layout, const Vec2& start, float boxHeight, float lineHeight);

	FontAsset textboxFont()const {
		return FontAsset(U"text");
	}
	int fontSize;

	void UpdateTextCursor();
	void DrawTextMenu();
	


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
	LayoutResult BuildLayoutForText(
		const String& text,
		size_t cursorPos,
		const Vec2& startPos,
		float boxWidth,
		float boxHeight,
		float lineHeight) const;
	size_t FindNearestIndexInLine(const LayoutResult& L, int line, float targetX) const;

	void StartCreateStageAsync(std::string userPromptUtf8);
	void PollCreateStageResult();
	void CancelOrJoinWorker();
	bool CreateStage(const String& userPrompt);

	void ApplyToStage(const GeneratedResult& result);


	// ロード中のミニゲーム
	void InitializeMiniGame();
	void UpdateMiniGame(float deltaTime);
	void DrawMiniGame();
	// ball
	float mBallRadius; //半径
	float mBallSpeed;
	float mBallPos;
	std::array<DrawFunc, 3> mFuncs;
	Font mLoadingFont{ ConvertToInt((float)0.07f * GetScreenHeight()),Typeface::Black };
	Font mExplainFont{ ConvertToInt((float)0.04f * GetScreenHeight()),Typeface::Black };
	String LoadText;
	String ExplainText;
	// load
	Array<Vec2> mLoadBrickPos;
	SizeF mLoadBrickSize;
	Array<String> mLoadTexts;
	Array<int> mLoadCounter;
	// explain
	Array<Vec2> mExplainBrickPos;
	Array<String> mExplainTexts;
	Array<int> mExplainCounter;
	SizeF mExplainBrickSize;


	
	int mLoadIndex = 0;

	bool EndGPTMenu_CreateStage();
};




