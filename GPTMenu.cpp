#include"GPTMenu.h"
#include"Parent.h"
#include"CreateStage.h"
#include"StageObject.h"
#include"Common.h"
#include"Stage.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <random>
#include <curl/curl.h>
#include <numbers>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int width = 22;
int height = 15;


GPTMenu::GPTMenu()
	:mCreateStage(nullptr)
	, mWidth(0)
	, mHeight(0)
	, mIsCreating(false)
{

}


GPTMenu::~GPTMenu() {
	CancelOrJoinWorker();
	mCreateStage = nullptr;
}


void GPTMenu::Initialize_CreateStage(class CreateStage* createStage) {
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
	inputDecision = KeySpace | KeyEnter;

	int FontSize = 0.09 * GetScreenHeight();
	selectFont = Font{ FontMethod::MSDF,FontSize / 2,Typeface::Light };

	// load
	mFuncs = {
		[](const Vec2& pos,float radius,float radian,ColorF color)
		{
			DrawCircle(pos,radius*0.5f,color);
		},
		[](const Vec2& pos,float radius,float radian,ColorF color)
		{
			DrawRotateRect(pos,radius,radius,radian,color);
		},
		[](const Vec2& pos,float radius,float radian,ColorF color)
		{
			DrawTriangle(pos,radius,radius,color);
		}

	};
}

const GPTMenu::DrawFunc& GPTMenu::getFunc(size_t index)const {
	return mFuncs.at(index);
}

void GPTMenu::Update(float deltaTime) {
	// 結果回収
	PollCreateStageResult();
	if (mIsCreating.load()) {
		if (inputDecision.down()) {
			mLoadIndex = (mLoadIndex + 1) % mFuncs.size();
		}
		return;
	}
	
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
		if (inputDecision.down()) {
			CreateStage();
		}
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
		if (EndGPTMenu_CreateStage())return;
	}

	return;
}

bool GPTMenu::EndGPTMenu_CreateStage() {
	mCreateStage->SetShouldCloseGPTMenu(true);
	return true;
}

static void DrawLoading(
	const Vec2& pos,
	float radius,
	int num,
	float speed,
	const GPTMenu::DrawFunc& func
)
{
	const float dNum = static_cast<float>(num);
	const float dif = Math::TwoPiF / dNum;

	for (int i = 0; i < num; ++i)
	{
		const float radian = i * dif;
		const Vec2 tPos = pos + Circular(radius*3.0f, radian);


		const float phase =
			static_cast<float>(Scene::Time()) * (-speed) + radian * 0.5f;

		const float t = 0.5f + 0.5f * std::sin(phase); // 0..1
		float tRadius = radius*(0.7+0.3*t);
		ColorF color = ColorF(t * 1.0f);
		func(tPos, tRadius, radian,color);
	}
}



void GPTMenu::Draw() const {
	DrawRoundRect(mBackgroundRectPos, mBackgroundRectWidth, mBackgroundRectHeight, mBackgroundRectWidth / 50.0,
		mBackgroundRectColor);

	// 作成中であることの表示
	if (mIsCreating.load()) {
		DrawLoading(
			Vec2(0.0f, -0.2f),
			0.05f,
			10,
			1.0f,
			getFunc(mLoadIndex)
		);
		return;
	}

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
	DrawRectFrame(pos[mSelectedButton], mSelectRectWidth, mSelectRectHeight, 0.005f, 0.005, ColorF(1.0f, 1.0f, 0.0f));



}


// CreateStage /////////////////////////////////////////////////////////////////////////////////////////
static const std::map<char, StageObject::Attribute> AttributeMap = {
		{'.',StageObject::Attribute::None},
		{'B',StageObject::Attribute::Brock},
		{'P',StageObject::Attribute::Patrol},
		{'D',StageObject::Attribute::Door},
		{'K',StageObject::Attribute::Key},
		{'E',StageObject::Attribute::Battery},
		{'T',StageObject::Attribute::TreasureChest},
		{'G',StageObject::Attribute::Ghost},
		{'1',StageObject::Attribute::Escapee1},
		{'2',StageObject::Attribute::Escapee2},
		{'3',StageObject::Attribute::Escapee3},
};

static const struct CellOverride {
	int x, y;
	std::optional<std::string> material;
	std::optional<int> clockwise;
	std::optional<int> patrolRange;
	std::optional<std::string> batterySize;
	std::optional<std::string> treasure;
	std::optional<float> speed;
	std::optional<bool> canBeGone;
};

static const struct StageDetails {
	StageObject::Attribute attribute;
	std::optional<std::string> material; // "Stone","Wood","Grass"
	std::optional<int> clockwise; // 0,1,2,3
	std::optional<int> patrolRange; // 0-30
	std::optional<std::string> batterySize; // Small Medium Large
	std::optional<std::string> treasure; // Empty, Battery, Key
	std::optional<float> speed; // 0.0 -100.0
	std::optional<bool> canBeGone; // bool
};

static const char* AttributeToString(StageObject::Attribute a) {
	switch (a) {
	case StageObject::Attribute::None: return "None";
	case StageObject::Attribute::Wall: return "Wall";
	case StageObject::Attribute::Brock: return "Brock";
	case StageObject::Attribute::Door: return "Door";
	case StageObject::Attribute::Patrol: return "Patrol";
	case StageObject::Attribute::Battery: return "Battery";
	case StageObject::Attribute::Key: return "Key";
	case StageObject::Attribute::TreasureChest: return "TreasureChest";
	case StageObject::Attribute::Candle: return "Candle";
	case StageObject::Attribute::Ghost: return "Ghost";
	case StageObject::Attribute::Escapee1: return "Escapee1";
	case StageObject::Attribute::Escapee2: return "Escapee2";
	case StageObject::Attribute::Escapee3: return "Escapee3";
	default: return "Unknown";
	}
}

static const struct CandleOut {
	int x, y;
	float radius;
};
static const struct StageDetailsOut {
	std::vector<CellOverride> cell_override;
	std::vector<CandleOut> candles;
};

static const struct DetailsOutput {

	std::map<std::pair<int, int>, StageDetails> cell_details; // <<x,y>,StageDetails>
	std::map<std::pair<float, float>, float> candles;
};

static json AnyOfIntOrNull(int mn, int mx) {
	return json{
		{"anyOf", json::array({
			json{{"type","integer"},{"minimum",mn},{"maximum",mx}},
			json{{"type","null"}}
		})}
	};
}

static json AnyOfNumberOrNull(double mn, double mx) {
	return json{
		{"anyOf", json::array({
			json{{"type","number"},{"minimum",mn},{"maximum",mx}},
			json{{"type","null"}}
		})}
	};
}

static json AnyOfBoolOrNull() {
	return json{
		{"anyOf", json::array({
			json{{"type","boolean"}},
			json{{"type","null"}}
		})}
	};
}

// null なら optional を empty にするヘルパ
template <class T>
static void assign_optional(const json& j, const char* key, std::optional<T>& outOpt) {
	auto it = j.find(key);
	if (it == j.end() || it->is_null()) {
		outOpt.reset();
		return;
	}
	outOpt = it->get<T>();
}

static void from_json(const json& j, CandleOut& c) {
	c.x = j.at("x").get<int>();
	c.y = j.at("y").get<int>();
	c.radius = j.at("radius").get<float>();
}

static void from_json(const json& j, CellOverride& o) {
	o.x = j.at("x").get<int>();
	o.y = j.at("y").get<int>();

	assign_optional<std::string>(j, "material", o.material);
	assign_optional<int>(j, "clockwise", o.clockwise);
	assign_optional<int>(j, "patrolRange", o.patrolRange);
	assign_optional<std::string>(j, "batterySize", o.batterySize);
	assign_optional<std::string>(j, "treasure", o.treasure);
	assign_optional<float>(j, "speed", o.speed);
	assign_optional<bool>(j, "canBeGone", o.canBeGone);
}

std::string readApiKey() {
	std::ifstream file("OpenAI_Key.txt");

	if (!file) throw std::runtime_error("Unable to open OpenAI_Key.txt");

	std::string key;
	std::getline(file, key);

	return key;
}

// ---- libcurl helpers ----
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	size_t total = size * nmemb;
	std::string* s = static_cast<std::string*>(userp);
	s->append(static_cast<const char*>(contents), total);
	return total;
}

static std::string HttpPostJson(const std::string& url, const std::string& bearerKey, const std::string& bodyJson) {
	CURL* curl = curl_easy_init();
	if (!curl) throw std::runtime_error("curl_easy_init failed");

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
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, ""); // 自動でgzip/deflate/br等を解凍

	// (任意) タイムアウト
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 180L);

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

void searchCanBeGone(int si, int sj, std::vector<std::vector<bool>>& visited, std::vector<std::string>& g) {
	std::queue<std::pair<int, int>> q;
	std::vector<int> di = { -1,1,0,0 };
	std::vector<int> dj = { 0,0,-1,1 };
	visited[si][sj] = true;
	q.push({ si,sj });
	while (!q.empty()) {
		int ni = q.front().first;
		int nj = q.front().second;
		q.pop();
		for (int k = 0; k < 4; k++) {
			int nxi = ni + di[k];
			int nxj = nj + dj[k];
			if (nxi < 0 || nxi >= height || nxj < 0 || nxj >= width)continue;
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
bool checkCanBeGone(std::vector<std::string>& g) {
	std::pair<int, int> ghostPos, escapee1Pos, escapee2Pos, escapee3Pos;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (g[i][j] == 'G')ghostPos = { i,j };
			if (g[i][j] == '1')escapee1Pos = { i,j };
			if (g[i][j] == '2')escapee2Pos = { i,j };
			if (g[i][j] == '3')escapee3Pos = { i,j };
		}
	}
	std::vector<std::vector<bool>> ghost(height, std::vector<bool>(width, false));
	std::vector<std::vector<bool>> escapee1(height, std::vector<bool>(width, false));
	std::vector<std::vector<bool>> escapee2(height, std::vector<bool>(width, false));
	std::vector<std::vector<bool>> escapee3(height, std::vector<bool>(width, false));

	searchCanBeGone(ghostPos.first, ghostPos.second, ghost, g);
	searchCanBeGone(escapee1Pos.first, escapee1Pos.second, escapee1, g);
	searchCanBeGone(escapee2Pos.first, escapee2Pos.second, escapee2, g);
	searchCanBeGone(escapee3Pos.first, escapee3Pos.second, escapee3, g);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (ghost[i][j] && escapee1[i][j] && escapee2[i][j] && escapee3[i][j]) {
				return true;
			}
		}
	}
	return false;

}


// JSON Schema (Structured Outputs). 22 chars per row, allowed charset only.
static json BuildStageSchema() {
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

// ---- stage prompt/schema ----






static std::string BuildPrompt(int w, int h) {
	std::ostringstream p;
	p <<
		R"(You MUST follow the rules. If any rule is violated, the output is rejected.

[ABSOLUTE REQUIREMENTS]
1) The grid is exactly 15 rows.
2) Each row is exactly 22 characters.
3) Allowed characters only: . B P D K E T G 1 2 3
4) Counts must be EXACT:
   - G appears exactly 1 time.
   - '1' appears exactly 1 time.
   - '2' appears exactly 1 time.
   - '3' appears exactly 1 time.

[LEGEND / MEANINGS]
- '.' = Floor (walkable)
- 'B' = Block (not walkable)
- 'P' = Patrol (walkable)
- 'D' = Door (NOT walkable unless the player has a Key)
- 'K' = Key (walkable)
- 'E' = Battery (walkable)
- 'T' = TreasureChest (walkable)
- 'G' = Ghost start (walkable)
- '1','2','3' = Escapee start positions (walkable)

[GAME RULES (for level design intent)]
- There is exactly 1 Ghost (G) and 3 Escapees (1,2,3).
- Ghost wins if it captures all Escapees.
- Each Escapee has a flashlight.
- Escapees win if they shine flashlights on the Ghost and reduce the Ghost’s health to zero.
Design the map to support both chase and confrontation, not only hiding.

[ADDITIONAL RULES]
A) Spawn separation:
- G,1,2,3 must not be adjacent in 4-neighborhood (up/down/left/right).

B) Connectivity / not fully blocked:
- Consider '.' 'P' 'D' 'K' 'E' 'T' 'G' '1' '2' '3' as walkable.
- From each of G,1,2,3 there must exist a walkable path to every other spawn.
- The walkable area should contain at least 2 distinct simple paths between G and each Escapee
  (i.e., avoid a single one-tile-wide corridor that acts as a strict bottleneck everywhere).

C) Maze-like but not too dense:
- The stage should look like a maze with corridors and rooms, but avoid excessive walls.
- Include at least one open area: a contiguous walkable rectangle of size at least 4x4
  (all cells in that rectangle are walkable).

[OUTPUT FORMAT]
Return ONLY JSON: { "layout": ["<22 chars>", ... 15 rows ...] }
Do not include explanations, comments, or extra keys.
)";
	return p.str();
}



static json AnyOfEnumOrNull(const json& enumVals) {
	return json{
		{"anyOf", json::array({
			json{{"type","string"}, {"enum", enumVals}},
			json{{"type","null"}}
		})}
	};
}

static json BuildDetailsSchema() {
	return json{
		{"name","stage_details"},
		{"strict",true},
		{"schema",{
			{"type","object"},
			{"additionalProperties",false},
			{"required", json::array({"cell_overrides","candles"})},
			{"properties",{
				{"cell_overrides",{
					{"type","array"},
					{"maxItems",120},
					{"items",{
						{"type","object"},
						{"additionalProperties",false},

						// strict=true 対応：properties の全キーを required に入れる
						{"required", json::array({
							"x","y",
							"material","clockwise","patrolRange","batterySize","treasure","speed","canBeGone"
						})},

						{"properties",{
							{"x", {{"type","integer"},{"minimum",0},{"maximum",21}}},
							{"y", {{"type","integer"},{"minimum",0},{"maximum",14}}},

							{"material", AnyOfEnumOrNull(json::array({"Stone","Wood","Grass"}))},
							{"clockwise", AnyOfIntOrNull(0,3)},
							{"patrolRange", AnyOfIntOrNull(0,22)},
							{"batterySize", AnyOfEnumOrNull(json::array({"Small","Medium","Large"}))},
							{"treasure", AnyOfEnumOrNull(json::array({"Empty","Battery","Key"}))},
							{"speed", AnyOfNumberOrNull(0.0,100.0)},
							{"canBeGone", AnyOfBoolOrNull()}
						}}
					}}
				}},
				{"candles",{
					{"type","array"},
					{"maxItems",12},
					{"items",{
						{"type","object"},
						{"additionalProperties",false},
						{"required", json::array({"x","y","radius"})},
						{"properties",{
							{"x", {{"type","integer"},{"minimum",0},{"maximum",21}}},
							{"y", {{"type","integer"},{"minimum",0},{"maximum",14}}},
							{"radius", {{"type","number"},{"minimum",10.0},{"maximum",600.0}}}
						}}
					}}
				}}
			}}
		}}
	};
}

// layoutから'.'でないセルを列挙する
static std::vector<std::tuple<int, int, char>> CollectNonDotCells(const std:: vector<std::string>& layout) {
	std::vector<std::tuple<int, int, char>> out;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			char c = layout[y][x];
			if (c == '.') continue;
			out.emplace_back(x, y, c);
		}
	}
	return out;
}

static std::string BuildDetaislPrompt(const std::vector<std::string>& layout) {
	auto nonDots = CollectNonDotCells(layout);

	std::ostringstream p;
	p <<
		R"(You will enrich a 2D stage with extra parameters and candle placements.
Return ONLY JSON following the provided schema.

[ABSOLUTE REQUIREMENTS]
1) cell_overrides MUST include exactly one entry for EVERY non-dot cell (layout[y][x] != '.').
   - For each (x,y) with a non-dot tile, there must be exactly one object in cell_overrides with that same x,y.
   - Do NOT include any entry for '.' cells.
2) Do NOT add, remove, or move tiles/objects. You only output parameters for existing non-dot tiles.
3) IMPORTANT (schema strict): In each cell_overrides object, you MUST include ALL fields:
   x, y, material, clockwise, patrolRange, batterySize, treasure, speed, canBeGone
   If a field is not applicable, set it to null (do NOT omit keys).

4) IMPORTANT (enumeration rule to avoid missing cells):
   - The list NON_DOT_CELLS below enumerates ALL non-dot cells in the layout.
   - cell_overrides MUST have EXACTLY COUNT entries.
   - For each index i:
	   cell_overrides[i].x MUST equal NON_DOT_CELLS[i].x
	   cell_overrides[i].y MUST equal NON_DOT_CELLS[i].y
	 Do NOT change the order. Do NOT skip any index.
   - Do NOT output any (x,y) that is not listed in NON_DOT_CELLS.

[NON_DOT_CELLS]
COUNT=)";

	p << nonDots.size() << "\n";
	// i: x y tile
	for (size_t i = 0; i < nonDots.size(); i++) {
		auto [x, y, t] = nonDots[i];
		p << i << ": " << x << " " << y << " " << t << "\n";
	}

	p <<
		R"(

[MINIMAL-PARAMETER POLICY (avoid over-design)]
- Keep parameters minimal: for MOST cells, all optional fields should be null.
- Only set a field when it clearly adds gameplay value and matches the tile type.
- Hard limit: Across ALL cell_overrides, keep the TOTAL number of non-null fields (excluding x,y) small.
  Target: <= 15 non-null fields total.

[FIELD GUIDELINES BY TILE]
- B (Brock): material may be set (often "Stone"), others null.
- D (Door): material may be set, canBeGone may be set, others null.
- P (Patrol): patrolRange and speed may be set; clockwise may be set; others null.
- T (TreasureChest): treasure and batterySize may be set; others null.
- K (Key): typically all null.
- E (Battery): batterySize may be set; others null.
- G/1/2/3: speed may be set; others null.

[CANDLES]
- Place 3 to 6 candles (avoid too many).
- Put candles only on passable tiles: '.' 'K' 'E' 'G' '1' '2' '3'
- Do NOT place candles on: B,P,D,T
- Avoid placing within Manhattan distance <=2 from G,1,2,3.
- radius: 80 to 200 typically.

[COORDINATES]
- x is column index (0..21), y is row index (0..14).
- The tile at (x,y) is layout[y][x].

[GAME RULES (for level design intent)]
- There is exactly 1 Ghost (G) and 3 Escapees (1,2,3).
- Ghost wins if it captures all Escapees.
- Each Escapee has a flashlight.
- Escapees win if they shine flashlights on the Ghost and reduce the Ghost’s health to zero.
Design the map to support both chase and confrontation, not only hiding.

[LAYOUT]
)";
	for (auto& row : layout) p << row << "\n";

	p <<
		R"(
[OUTPUT RULES]
- Return ONLY JSON that matches the schema.
- Use null for non-applicable fields. Never omit required keys.
)";
	return p.str();
}


// LAYOUT //////////////////////////////////////////////////////////////////////////////////////////////

// Responses API の出力から "layout" を取り出す（Structured Outputs前提）
static std::vector<std::string> ExtractLayoutFromResponses(const json& resp) {

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

// ---- optional: extra validation you likely want ----
static void ValidateLogicalRulesOrThrow(const std::vector<std::string>& layout) {
	const int H = (int)layout.size();
	const int W = (H ? (int)layout[0].size() : 0);
	if (H != height || W != width) throw std::runtime_error("layout size mismatch");


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

static bool IsBlocked(char c) {
	return (c == 'B' || c == 'P' || c == 'D' || c == 'T');
}

static bool InBounds(int y, int x) {
	return 0 <= y && y < height && 0 <= x && x < width;
}

static bool Adjacent4(int y1, int x1, int y2, int x2) {
	return (abs(y1 - y2) + abs(x1 - x2)) == 1;
}

static std::vector<std::pair<int, int>> FindAll(const std::vector<std::string>& g, char ch) {
	std::vector<std::pair<int, int>> pos;
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			if (g[y][x] == ch) pos.push_back({ y,x });
	return pos;
}

static std::vector<std::pair<int, int>> CollectPassableDots(std::vector<std::string>& g) {
	std::vector<std::pair<int, int>> cells;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (g[y][x] == '.') cells.push_back({ y,x });
		}
	}
	return cells;
}

// G/1/2/3 が互いに4近傍で隣接しないか
static bool CheckNotAdjacent4(const std::vector<std::pair<int, int>>& ps) {
	for (int i = 0; i < (int)ps.size(); i++) {
		for (int j = i + 1; j < (int)ps.size(); j++) {
			if (Adjacent4(ps[i].first, ps[i].second, ps[j].first, ps[j].second)) return false;
		}
	}
	return true;
}

static bool TryFixPlayers(std::vector<std::string>& g, int tries) {
	// まず既存の G/1/2/3 を全部消す（壊れてても良いので一旦正規化）
	for (char ch : {'G', '1', '2', '3'}) {
		auto ps = FindAll(g, ch);
		for (auto [y, x] : ps) g[y][x] = '.'; // 一旦空に戻す
	}

	// 置ける候補（'.'）を集める
	auto cells = CollectPassableDots(g);
	if ((int)cells.size() < 4) return false;

	// 適当にシャッフルして4点選ぶのを繰り返す
	std::mt19937 rng((unsigned)std::random_device{}());

	for (int t = 0; t < tries; t++) {
		std::shuffle(cells.begin(), cells.end(), rng);
		std::vector<std::pair<int, int>> pick = { cells[0],cells[1],cells[2],cells[3] };

		if (!CheckNotAdjacent4(pick)) continue;

		// 置いてみる
		auto backup = g;
		g[pick[0].first][pick[0].second] = 'G';
		g[pick[1].first][pick[1].second] = '1';
		g[pick[2].first][pick[2].second] = '2';
		g[pick[3].first][pick[3].second] = '3';

		if (checkCanBeGone(g)) {
			return true; // 成功
		}
		g = backup; // ダメなら戻す
	}
	return false;
}




std::vector<std::string> GenerateStageLayout(int maxRetries = 5) {
	std::string apiKey = readApiKey();

	if (apiKey == "error") {
		throw std::runtime_error("OPENAI_API_KEY is not set");
	}

	const std::string url = "https://api.openai.com/v1/responses";
	const std::string model = "gpt-4o-mini"; // 例：軽量。必要なら gpt-4o / 最新スナップショットに。

	json req;
	req["model"] = model;
	req["instructions"] = "You are a professional game level designer. Output JSON only.";
	req["input"] = NormalizePromptToSafeAscii(BuildPrompt(width,height)); // UTF8に変換
	 
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


			// ランダムに配置
			if (attempt == maxRetries) {
				TryFixPlayers(layout,100);
			}
			ValidateLogicalRulesOrThrow(layout);
			return layout; // OK
		}
		catch (const std::exception& e) {
			std::cerr << "[Validate layout error][attempt " << attempt << "] "
				<< e.what() << std::endl;

			// 失敗したら、次の試行で「直せ」と追記して再生成させる
			std::ostringstream fb;
			fb << "\n\nThe previous layout was invalid: " << e.what()
				<< "\nRegenerate a new layout satisfying all rules strictly.";
			req["input"] = NormalizePromptToSafeAscii(BuildPrompt(width,height) + fb.str());
		}
	}

	throw std::runtime_error("Failed to generate a valid layout within retry limit");
}


static StageDetailsOut ExtractDetailsFromResponse(const json& resp) {
	if (!resp.contains("output") || !resp["output"].is_array()) {
		throw std::runtime_error("Response JSON has no 'output' array");
	}

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

	if (text.empty()) {
		throw std::runtime_error("Could not find output_text in response: " + resp.dump(2));
	}

	json out = json::parse(text);

	if (!out.contains("candles") || !out["candles"].is_array()) {
		throw std::runtime_error("Parsed output has no 'candles' array: " + out.dump(2));
	}
	if (!out.contains("cell_overrides") || !out["cell_overrides"].is_array()) {
		throw std::runtime_error("Parsed output has no 'cell_overrides' array: " + out.dump(2));
	}

	StageDetailsOut result;
	result.candles = out["candles"].get<std::vector<CandleOut>>();
	result.cell_override = out["cell_overrides"].get<std::vector<CellOverride>>();
	return result;
}


// 初期化
static std::map<std::pair<int, int>, StageDetails> CreateDefaultStageDetails(const std::vector<std::string>& layout) {
	std::map<std::pair<int, int>, StageDetails> res;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			char c = layout[y][x];
			if (c == '.')continue;

			StageDetails sd;
			sd.attribute = AttributeMap.at(c);
			sd.material.reset();
			sd.clockwise.reset();
			sd.patrolRange.reset();
			sd.batterySize.reset();
			sd.treasure.reset();
			sd.speed.reset();
			sd.canBeGone.reset();

			res[{x, y}] = sd;
		}
	}

	return res;
}

// detailsから<位置、詳細情報> のmapを作成
std::map<std::pair<int, int>, StageDetails> CreateStagePosAndStageDetails(
	std::vector<std::string>& layout,
	std::vector<CellOverride>& details)
{
	std::map<std::pair<int, int>, StageDetails> res;
	for (const auto& d : details) {
		int i = d.y, j = d.x;
		if (i < 0 || i >= height || j < 0 || j >= width) {
			throw std::runtime_error("Pos from details is out of stage");
		}

		StageDetails sd;

		// attribute
		char c = layout[i][j];

		sd.attribute =  AttributeMap.at(c);

		// 詳細情報
		sd.material = d.material;
		sd.clockwise = d.clockwise;
		sd.patrolRange = d.patrolRange;
		sd.batterySize = d.batterySize;
		sd.treasure = d.treasure;
		sd.speed = d.speed;
		sd.canBeGone = d.canBeGone;

		res[std::make_pair(j, i)] = sd;
	}

	return res;
}

void MergeCreatedStage(
	std::map<std::pair<int, int>, StageDetails>& init, // layoutの'.'でセルを初期化したもの
	std::map<std::pair<int, int>, StageDetails>& created // llmにlayoutを渡して作成してもらったもの
)
{
	// layoutでは作成されているがdetailsでは詳細情報が書かれていない個数のカウント
	int cnt_all = 0; // initで作成された
	int cnt_created_details = 0; // detailsで作成された
	int cnt_false_created_details = 0; // layoutで作成れた && detailsで作成されていない
	int cnt_true_created_details = 0; // layoutで作成された && detailsで作成された
	for (const auto& i : init) {
		auto p = i.first;
		cnt_all++;

		if (created.count(p)) {
			cnt_true_created_details++; // ちゃんと作成できている
		}
		else {
			cnt_false_created_details++; // 作成できていない
		}
	}

	for (const auto& c : created) {
		auto p = c.first;
		auto sd = c.second;
		cnt_created_details++;
		init[p] = sd;
	}


	return;
}

void JustifyStageDetails(std::map<std::pair<int, int>, StageDetails>& details) {
	std::mt19937 rng{ std::random_device{}() };


	for (auto& d : details) {
		const auto pos = d.first;
		auto& sd = d.second; // 参照で更新

		switch (sd.attribute) {
		case StageObject::Attribute::None:
			break;

		case StageObject::Attribute::Wall:
		case StageObject::Attribute::Brock:
			if (!sd.material.has_value()) sd.material = "Stone";
			break;

		case StageObject::Attribute::Patrol: {
			if (!sd.clockwise.has_value()) {
				std::uniform_int_distribution<int> dist(0, 3); // 0..3
				sd.clockwise = dist(rng);
			}

			if (!sd.patrolRange.has_value()) {
				int maxPatrolRange = 0;
				switch (*sd.clockwise) {
				case 0: maxPatrolRange = pos.second; break;              // ←要整合
				case 1: maxPatrolRange = width - 1 - pos.first; break;   // ←要整合
				case 2: maxPatrolRange = height - 1 - pos.second; break; // ←要整合
				case 3: maxPatrolRange = pos.first; break;
				}
				if (maxPatrolRange < 0) maxPatrolRange = 0;

				std::uniform_int_distribution<int> dist(0, maxPatrolRange);
				sd.patrolRange = dist(rng);
			}

			if (!sd.speed.has_value()) {
				std::uniform_real_distribution<float> dist(0.0f, 100.0f);
				sd.speed = dist(rng);
			}
			break;
		}

		case StageObject::Attribute::Door:
			if (!sd.clockwise.has_value()) {
				std::uniform_int_distribution<int> dist(0, 3);
				sd.clockwise = dist(rng);
			}
			break;

		case StageObject::Attribute::Battery:
			if (!sd.batterySize.has_value()) {
				std::uniform_int_distribution<int> dist(0, 2);
				switch (dist(rng)) {
				case 0: sd.batterySize = "Small"; break;
				case 1: sd.batterySize = "Middle"; break;
				case 2: sd.batterySize = "Large"; break;
				}
			}
			break;

		case StageObject::Attribute::TreasureChest:
			if (!sd.batterySize.has_value()) {
				std::uniform_int_distribution<int> dist(0, 2);
				switch (dist(rng)) {
				case 0: sd.batterySize = "Small"; break;
				case 1: sd.batterySize = "Middle"; break;
				case 2: sd.batterySize = "Large"; break;
				}
			}
			if (!sd.treasure.has_value()) {
				std::uniform_int_distribution<int> dist(0, 2);
				switch (dist(rng)) {
				case 0: sd.treasure = "Empty"; break;
				case 1: sd.treasure = "Battery"; break;
				case 2: sd.treasure = "Key"; break;
				}
			}
			break;

		case StageObject::Attribute::Ghost:
			if (!sd.speed.has_value()) {
				std::uniform_real_distribution<float> dist(0.0f, 100.0f);
				sd.speed = dist(rng);
			}
			break;

		case StageObject::Attribute::Escapee1:
		case StageObject::Attribute::Escapee2:
		case StageObject::Attribute::Escapee3:
			if (!sd.speed.has_value()) {
				std::uniform_real_distribution<float> dist(0.0f, 100.0f);
				sd.speed = dist(rng);
			}
			break;

		default:
			break;
		}
	}
}


// candleから<位置、半径> のmapを作成
std::map<std::pair<float, float>, float> CreateStagePosAndCandles(std::vector<CandleOut>& candle) {
	std::map<std::pair<float, float>, float> res;
	for (const auto& c : candle) {
		float cx = (float)c.x, cy = (float)c.y;
		res[std::make_pair(cx, cy)] = c.radius;
	}

	return res;
}


DetailsOutput GenerateStageDetailsAndCandles(
	std::vector < std:: string > & layout,
	int maxRetries = 5) {
	std::string apiKey = readApiKey();

	if (apiKey == "error") {
		throw std::runtime_error("OPEN_API_KEY is not set");
	}

	const std::string url = "https://api.openai.com/v1/responses";
	const std::string model = "gpt-4o-mini"; // 例：軽量。必要なら gpt-4o / 最新スナップショットに。

	json req;
	req["model"] = model;
	req["max_output_tokens"] = 6000; // 足りない場合がある
	req["temperature"] = 0.0;
	req["instructions"] = "You are a professional game level designer. Output JSON only.";
	req["input"] = NormalizePromptToSafeAscii(BuildDetaislPrompt(layout));


	req["text"] = {
		{"format",{
			{"type","json_schema"},
			{"name","stage_details"},
			{"strict",true},
			{"schema",BuildDetailsSchema()["schema"]}
		}}
	};

	for (int attempt = 1; attempt <= maxRetries; attempt++) {
		std::string respStr = HttpPostJson(url, apiKey, req.dump());
		json resp = json::parse(respStr);

		std::ofstream ofs("log_d.txt", std::ios::app);
		ofs << "attempt" << ": " << attempt << "\n";
		ofs << resp.dump(2) << "\n";
		try {
			StageDetailsOut details = ExtractDetailsFromResponse(resp);
			// 初期化
			auto stage_details = CreateDefaultStageDetails(layout);



			auto created_stage_details = CreateStagePosAndStageDetails(layout, details.cell_override);
			// 合体 すべてのセルに詳細情報
			MergeCreatedStage(stage_details, created_stage_details);
			// layoutが'.'でない場合はdetailsがあることを保障
			JustifyStageDetails(stage_details);

			// candle
			auto stage_candles = CreateStagePosAndCandles(details.candles);
			DetailsOutput res = { stage_details,stage_candles };
			//PrintDetailsOutput(res);
			return res;

		}
		catch (const std::exception& e) {
			std::cerr << "[Validate details error][attempt " << attempt << "] "
				<< e.what() << std::endl;
			// 失敗したら、次の試行で「直せ」と追記して再生成させる
			std::ostringstream fb;
			fb << "\n\nThe previous details was invalid: " << e.what()
				<< "\nRegenerate a new details satisfying all rules strictly.";
			req["input"] = NormalizePromptToSafeAscii(BuildDetaislPrompt(layout) + fb.str());
		}

	}

	throw std::runtime_error("Failed to generate a valid details within retry limit");

}

bool GPTMenu::CreateStage() {
	StartCreateStageAsync();
	return true;
}

void GPTMenu::StartCreateStageAsync() {
	if (mIsCreating.load())return;

	CancelOrJoinWorker();

	{
		std::lock_guard<std::mutex> lock(mResultMutex);
		mPendingResult.reset();
		mPendingError.reset();
	}

	mIsCreating.store(true);

	mWorker = std::thread([this]() {
		try {
			curl_global_init(CURL_GLOBAL_DEFAULT);

			auto layout = GenerateStageLayout(5);
			auto details = GenerateStageDetailsAndCandles(layout, 2);

			auto out = std::make_unique<DetailsOutput>(std::move(details));

			curl_global_cleanup();
			{
				std::lock_guard < std::mutex> lock(mResultMutex);
				mPendingResult = GeneratedResult{ std::move(layout),std::move(out) };
			}
		}
		catch (const std::exception& e) {
			{
				std::lock_guard<std::mutex> lock(mResultMutex);
				mPendingError = std::string(e.what());
			}

			curl_global_cleanup();
		}
		mIsCreating.store(false);

	});

}

void GPTMenu::PollCreateStageResult() {
	// スレッド資源を削除
	if (!mIsCreating.load()) {
		if (mWorker.joinable())mWorker.join();
	}

	std::optional<GeneratedResult> result;
	std::optional<std::string> err;

	{
		std::lock_guard<std::mutex> lock(mResultMutex);
		result = std::move(mPendingResult);
		err = std::move(mPendingError);
		mPendingResult.reset();
		mPendingError.reset();
	}

	if (err) {
		Print << U"Error: " << Unicode::FromUTF8(*err);
		return;
	}

	if (result) {
		Print << U"Success CreateStage";
		return;
	}


}

void GPTMenu::CancelOrJoinWorker() {
	// すでに走っているスレッドがいるならそのスレッドが終わるまで待つ
	if (mWorker.joinable()) {
		mWorker.join();
	}
}


