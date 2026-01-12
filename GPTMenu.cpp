#include"GPTMenu.h"
#include"Parent.h"
#include"CreateStage.h"
#include"Stage.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using json = nlohmann::json;



GPTMenu::GPTMenu()
	:mCreateStage(nullptr)
	,mWidth(0)
	,mHeight(0)
{

}


GPTMenu::~GPTMenu() {
	mCreateStage = nullptr;
}


void GPTMenu::Initialize_CreateStage(CreateStage* createStage) {
	mCreateStage = createStage;
	if (mCreateStage->GetStage()) {
		mWidth = mCreateStage->GetStage()->GetSideSize();
		mHeight = mCreateStage->GetStage()->GetVerticalSize();
	}
	


	// 全体設定
	mBackgroundRectPos = Vec2(0, 0);
	mBackgroundRectWidth = (float)1.7;
	mBackgroundRectHeight = (float)1.8;
	mBackgroundRectColor = ColorF(0);

	// ボタン設定
	mSendRectPos = Vec2(0.4f, -0.7f);
	mSelectRectHeight = 0.18f;
	mSelectRectWidth = 0.5f;

	mCloseRectPos = Vec2(-0.4f, -0.7f);

	// 入力
	inputUp = KeyW;
	inputDown = KeyS;
	inputRight = KeyD;
	inputLeft = KeyA;
	inputDecision = KeySpace|KeyEnter;

	int FontSize = 0.09 * GetScreenHeight();
	selectFont = Font{ FontMethod::MSDF,FontSize / 2,Typeface::Light };
}

void GPTMenu::Update(float deltaTime) {
	RectF sendRect = RectF(Arg::center(ConvertToView(mSendRectPos)),
		mSelectRectWidth * GetScreenWidth() / 2.0f,
		mSelectRectHeight * GetScreenHeight() / 2.0f);

	RectF closeRect = RectF(Arg::center(ConvertToView(mCloseRectPos)),
		mSelectRectWidth * GetScreenWidth() / 2.0f,
		mSelectRectHeight * GetScreenHeight() / 2.0f);

	switch (mSelectedButton) {
	case SelectedButton::NONE:
		if (inputLeft.down()) {
			mSelectedButton = SelectedButton::CLOSE;
		}
		if (inputRight.down()) {
			mSelectedButton = SelectedButton::SEND;
		}
		break;
	case SelectedButton::SEND:
		if (inputLeft.down()) {
			mSelectedButton = SelectedButton::CLOSE;
		}
		break;
	case SelectedButton::CLOSE:
		if (inputDecision.down()) {
			EndGPTMenu_CreateStage();
			return;
		}
		if (inputRight.down()) {
			mSelectedButton = SelectedButton::SEND;
		}
		break;
	}
	

	if (sendRect.leftClicked()) {
		// to do: GPTへ送信
	}
	if (closeRect.leftClicked()) {
		if(EndGPTMenu_CreateStage())return;
	}
}

bool GPTMenu::EndGPTMenu_CreateStage() {
	mCreateStage->SetShouldCloseGPTMenu(true);
	return true;
}


void GPTMenu::Draw() const {
	DrawRoundRect(mBackgroundRectPos, mBackgroundRectWidth, mBackgroundRectHeight, mBackgroundRectWidth / 50.0,
		mBackgroundRectColor);

	std::map < SelectedButton, Vec2> pos;
	std::map<SelectedButton, String> text;
	pos[SEND] = mSendRectPos;
	pos[CLOSE] = mCloseRectPos;
	text[SEND] = U"Send";
	text[CLOSE] = U"Close";

	// 描画
	for (auto [mode, p] : pos) {
		DrawRect(p, mSelectRectWidth, mSelectRectHeight, ColorF(1.0f));
		selectFont(text[mode]).drawAt(ConvertToView(p), ColorF(0.0f));
	}
	DrawRectFrame(pos[mSelectedButton], mSelectRectWidth, mSelectRectHeight, 0.005f, 0.005 , ColorF(1.0f,1.0f,0.0f));


}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	size_t total = size * nmemb;
	std::string* s = static_cast<std::string*>(userp);
	s->append(static_cast<const char*>(contents), total);
	return total;
}

static std::string HttpPostJson(const std::string& url, const std::string& bearerKey, const std::string& bodyJson) {
	CURL* curl = curl_easy_init();
	if (!curl)throw std::runtime_error("curl_easy_init failed");

	std::string response;
	struct curl_slist* headers = nullptr;
	std::string auth = "Authorization: Bearer " + bearerKey;

	headers = curl_slist_append(headers, auth.c_str());
	headers = curl_slist_append(headers, "Content-Type: application/json");

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, bodyJson.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)bodyJson.size());
	// WriteCallbackをlibcurlに渡す → レスポンスを受信するたびに
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	// (任意) タイムアウト
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);

	CURLcode res = curl_easy_perform(curl);

	long http_code = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

	curl_slist_free_all(headers);
	curl_easy_cleanup(curl);

	if (res != CURLE_OK) {
		throw std::runtime_error(std::string("curl_easy_perform failed: ") + curl_easy_strerror(res));
	}
	if (http_code < 200 || http_code >= 300) {
		std::ostringstream oss;
		oss << "HTTP " << http_code << " response: " << response;
		throw std::runtime_error(oss.str());
	}

	return response;
}

std::string readApiKey() {
	std::ifstream file("OpenAI_Key.txt");
	if (!file) throw std::runtime_error("Unable to open OpenAI_Key.txt");

	std::string key;
	std::getline(file, key);
	return key;
}

std::string GPTMenu::BuildPrompt() {
	int w = mWidth, h = mHeight;
	std::ostringstream p;
	p <<
		R"(Generate a playable 2D grid stage.

[GRID]
- width=)" << w << R"(, height=)" << h << R"(
- Exactly 15 rows, each row exactly 22 characters
- Use only these characters: . B P D K E T G 1 2 3

[LEGEND]
. empty
B brock (impassable)
P patrol (impassable)
D door
K key
E battery
T treasure chest (impassable)
G ghost (exactly one)
1 escapee1 (exactly one)
2 escapee2 (exactly one)
3 escapee3 (exactly one)

[CONSTRAINTS]
- Place exactly one of G,1,2,3
- Keep G,1,2,3 not adjacent (4-neighborhood) initially
- Do not create a fully blocked map; ensure multiple paths exist
- Maze-like but not too dense; include at least one open area

Return ONLY the JSON that matches the provided schema.)";
	return p.str();

}


json GPTMenu::BuildStageSchema() {
	return json{
		{"name", "stage_layout"},
		{"strict", true},
		{"schema",
			{
				{"type", "object"},
				{"additionalProperties", false},
				{"required", json::array({"layout"})},
				{"properties",
					{
						{"layout",
							{
								{"type", "array"},
								{"minItems", 15},
								{"maxItems", 15},
								{"items",
									{
										{"type", "string"},
										{"pattern", "^[.BPDKETG123]{22}$"}
									}
								}
							}
						}
					}
				}
			}
		}
	};
}


std::vector<std::string> GPTMenu::ExtractLayoutFromResponses(const json& resp) {
	if (!resp.contains("output") || !resp["output"].is_array()) {
		throw std::runtime_error("Response JSON has no 'output' array");
	}

	// output 内の message.content の text を連結
	std::string text;
	for (const auto& item : resp["output"]) {
		if (item.value("type", "") != "message") continue;
		if (!item.contains("content") || !item["content"].is_array()) continue;
		for (const auto& c : item["content"]) {
			if (c.value("type", "") == "output_text") {
				text += c.value("text", "");
			}
		}
	}

	// text が空なら、そのまま全体をダンプして原因追跡できるようにする
	if (text.empty()) {
		throw std::runtime_error("Could not find output_text in response: " + resp.dump(2));
	}

	// Structured Outputs なので text は JSON のはず
	json out = json::parse(text);
	if (!out.contains("layout") || !out["layout"].is_array()) {
		throw std::runtime_error("Parsed output has no 'layout' array: " + out.dump(2));
	}
	// stringの配列として返す
	return out["layout"].get<std::vector<std::string>>();
}


void GPTMenu::ValidLogicalRulesOrThrow(const std::vector<std::string>& layout) {
	const int H = (int)layout.size();
	const int W = (H ? (int)layout[0].size() : 0);
	if (H != mHeight || W != mWidth) throw std::runtime_error("layout size mismatch");


	auto countChar = [&](char ch) {
		int c = 0;
		for (auto& row : layout) for (char r : row) if (r == ch) c++;
		return c;
		};

	if (countChar('G') != 1) throw std::runtime_error("G must appear exactly once");
	if (countChar('1') != 1) throw std::runtime_error("1 must appear exactly once");
	if (countChar('2') != 1) throw std::runtime_error("2 must appear exactly once");
	if (countChar('3') != 1) throw std::runtime_error("3 must appear exactly once");
}


void GPTMenu::searchCanBeGone(int si, int sj, std::vector<std::vector<bool>>& visited, std::vector<std::string>& g) {
	std::queue<std::pair<int, int>> q;
	std::vector<int> di = { -1,1,0,0 };
	std::vector<int> dj = { 0,0,-1,1 };
	q.push({ si,sj });
	while (!q.empty()) {
		int ni = q.front().first;
		int nj = q.front().second;
		q.pop();
		for (int k = 0; k < 4; k++) {
			int nxi = ni + di[k];
			int nxj = nj + dj[k];
			if (nxi < 0 || nxi >= mHeight || nxj < 0 || nxj >= mWidth)continue;
			if (g[nxi][nxj] == 'B'
				|| g[nxi][nxj] == 'P'
				|| g[nxi][nxj] == 'D'
				|| g[nxi][nxj] == 'T')continue;
			if (!visited[nxi][nxj]) {
				visited[nxi][nxj] = true;
				q.push({ nxi,nxj });
			}
		}
	}
}

// すべてのplayerから到達できる場所が1つでもあるか
bool GPTMenu::checkCanBeGone(std::vector<std::string>& g) {
	std::pair<int, int> ghostPos, escapee1Pos, escapee2Pos, escapee3Pos;
	for (int i = 0; i < mHeight; i++) {
		for (int j = 0; j < mWidth; j++) {
			if (g[i][j] == 'G')ghostPos = { i,j };
			if (g[i][j] == '1')escapee1Pos = { i,j };
			if (g[i][j] == '2')escapee2Pos = { i,j };
			if (g[i][j] == '3')escapee3Pos = { i,j };
		}
	}
	std::vector<std::vector<bool>> ghost(mHeight, std::vector<bool>(mWidth, false));
	std::vector<std::vector<bool>> escapee1(mHeight, std::vector<bool>(mWidth, false));
	std::vector<std::vector<bool>> escapee2(mHeight, std::vector<bool>(mWidth, false));
	std::vector<std::vector<bool>> escapee3(mHeight, std::vector<bool>(mWidth, false));

	searchCanBeGone(ghostPos.first, ghostPos.second, ghost, g);
	searchCanBeGone(escapee1Pos.first, escapee1Pos.second, escapee1, g);
	searchCanBeGone(escapee2Pos.first, escapee2Pos.second, escapee2, g);
	searchCanBeGone(escapee3Pos.first, escapee3Pos.second, escapee3, g);
	for (int i = 0; i < mHeight; i++) {
		for (int j = 0; j < mWidth; j++) {
			if (ghost[i][j] && escapee1[i][j] && escapee2[i][j] && escapee3[i][j]) {
				return true;
			}
		}
	}
	return false;

}

std::vector<std::string> GPTMenu::GenerateStageLayoutCppOnly(int maxRetries = 5) {
	std::string apiKey = readApiKey();
	if (apiKey == "error") {
		throw std::runtime_error("OPENAI_API_KEY is not set");
	}

	const std::string url = "https://api.openai.com/v1/responses";
	const std::string model = "gpt-4o-mini"; // 例：軽量。必要なら gpt-4o / 最新スナップショットに。

	json req;
	req["model"] = model;
	req["instructions"] = "You are a professional game level designer. Output JSON only.";
	req["input"] = BuildPrompt();

	// Structured Outputs: text.format (json_schema)
	// docs: text: { format: { type: "json_schema", strict: true, schema: ... } } :contentReference[oaicite:2]{index=2}
	req["text"] = {
		{"format", {
			{"type", "json_schema"},
			{"name", "stage_layout"},
			{"strict", true},
			{"schema", BuildStageSchema()["schema"]}
		}}
	};

	for (int attempt = 1; attempt <= maxRetries; attempt++) {
		std::string respStr = HttpPostJson(url, apiKey, req.dump());
		json resp = json::parse(respStr);

		std::ofstream ofs("log.txt", std::ios::app);
		ofs << "attempt" << ": " << attempt << "\n";
		ofs << resp.dump(2) << "\n"; // デバッグ用にレスポンス全体を表示

		try {
			auto layout = ExtractLayoutFromResponses(resp);
			for (auto x : layout)std::cout << x << std::endl;
			if (!checkCanBeGone(layout)) {
				throw std::runtime_error("There is no place all players can go.");
			}
			return layout; // OK
		}
		catch (const std::exception& e) {
			// 失敗したら、次の試行で「直せ」と追記して再生成させる
			std::ostringstream fb;
			fb << "\n\nThe previous layout was invalid: " << e.what()
				<< "\nRegenerate a new layout satisfying all rules strictly.";
			req["input"] = BuildPrompt() + fb.str();
		}
	}

	throw std::runtime_error("Failed to generate a valid layout within retry limit");
}
