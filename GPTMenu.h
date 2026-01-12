#pragma once
#include<Siv3D.hpp>
#include"Parent.h"
#include"CreateStage.h"

#include <curl/curl.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class GPTMenu {
public:
	GPTMenu();
	~GPTMenu();

	enum SelectedButton {
		SEND,
		CLOSE,
		NONE
	};

	void Initialize_CreateStage(class CreateStage* createStage);

	void Update(float deltaTime);
	void Draw() const;

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
	std::string BuildPrompt();
	json BuildStageSchema();
	std::vector<std::string> ExtractLayoutFromResponses(const json& resp);
	void ValidLogicalRulesOrThrow(const std::vector<std::string>& layout);
	void searchCanBeGone(int si, int sj, std::vector<std::vector<bool>>& visited, std::vector<std::string>& g);
	bool checkCanBeGone(std::vector<std::string>& g);
	std::vector<std::string> GenerateStageLayoutCppOnly(int maxRetries = 5);

	bool EndGPTMenu_CreateStage();
};


