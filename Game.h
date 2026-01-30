#pragma once
#include"Common.h"
#include"Parent.h"
#include"SquareComponent.h"

class Game {
public:
	Game(String selectedStageName, std::vector<Controller::ControllerType> controllers);
	~Game();
	void update(class Parent*);
	void draw();

	bool Initialize();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddDrawing(class DrawingComponent* drawing);
	void RemoveDrawing(class DrawingComponent* drawing);

	void AddCircle(class CircleComponent* circle);
	void RemoveCircle(class CircleComponent* circle);

	void AddSquare(class SquareComponent* square);
	void RemoveSquare(class SquareComponent* square);

	void AddTriangle(class TriangleComponent* tri);
	void RemoveTriangle(class TriangleComponent* tri);

	void AddPlayer(class Player* player);
	void RemovePlayer(class Player* player);

	//Hitstop
	void SetIsHitstop(bool isHitstop) { mIsHitstop = isHitstop; }
	bool GetIsHitstop() { return mIsHitstop; }
	void SetHitstop(float hitstopTime);
	void UpdateHitstop(float deltaTime);

	//class getter
	class Stage*& GetStage() { return mStage; }
	class Ghost_Game*& GetGhost() { return mGhost; }
	class Escapee_Game*& GetEscapee1() { return mEscapee1; }
	class Escapee_Game*& GetEscapee2() { return mEscapee2; }
	class Escapee_Game*& GetEscapee3() { return mEscapee3; }
	std::vector<class Player*>& GetPlayers() { return mPlayers; }

	//Sequence
	void moveTo(Parent* paretn, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }

	// Pause用入力
	void SetInputUp(InputGroup input) { inputUp = input; }
	void SetInputDown(InputGroup input) { inputDown = input; }
	void SetInputBack(InputGroup input) { inputBack = input; }
	void SetInputPause(InputGroup input) { inputPause = input; }
	void SetInputDecision(InputGroup input) { inputDecision = input; }

	// Pause
	bool GetIsPaused() { return mIsPaused; }
	void SetIsPaused(bool isPaused) { mIsPaused = isPaused; }



private:
	void ProcessInput();
	void UpdateGame();
	void LoadData();
	void UnloadData();

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	//All the Drwaing
	std::vector<class DrawingComponent*> mDrawings_Back;
	std::vector<class DrawingComponent*> mDrawings_Front;
	std::vector<class DrawingComponent*> mDrawings_Unaffected;

	//All the player
	std::vector<class Player*> mPlayers;

	//All the Circle components drawn
	std::vector<class CircleComponent*> mCircles;

	//All the Square components drawn
	std::vector<class SquareComponent*> mSquares;

	//All the Triangle components drawn
	std::vector<class TriangleComponent*> mTriangles;


	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	bool mIsHitstop;  //Hitstopかどうか
	float HitstopTime;
	float mHitstopTime;

	Parent::SeqID mSeqID;

	class Stage* mStage;
	String mSelectedStageName; // 選択されたステージの名前
	class Escapee_Game* mEscapee1;
	class Escapee_Game* mEscapee2;
	class Escapee_Game* mEscapee3;
	class Ghost_Game* mGhost;

	// controller
	std::vector<Controller::ControllerType> mControllers;

	//RenderTexture
	RenderTexture renderTexture;
	RenderTexture renderTextureLight;
	//Shader
	VertexShader vs2D;
	PixelShader ps2DTexture;

	// timer
	float mGameTime;
	int mGameSec;
	int mGameMin;
	bool mIsTimeUp;
	const Font mTimerFont{ ConvertToInt((float)0.05 * GetScreenHeight()),Typeface::Bold };
	void UpdateTimer(float deltaTime);

	// pause manu
	bool mIsPaused;
	enum PauseSelectedMode {
		CONTINUE,
		MAIN_MENU,
		STAGE_SELECT,
		RULE,
	};
	class Player* mPauseOwner;
	PauseSelectedMode mPauseMode;
	void UpdatePause(float deltaTime);
	void DrawPause();
	Font pauseFont;

	// rule
	bool mIsRule = false;
	void UpdateRule();
	void DrawRule();
	std::vector<TextureAsset> mRuleTextures;
	int mRuleIteration=0;
	int mRuleSize;

	// 終了判定
	void CheckIsGameEnd();
	bool mIsGameEnd = false;
	Parent::GameJudgement mJudgement;

	// ghost hp font
	Font mHpFont{ ConvertToInt((float)0.04 * GetScreenHeight()),Typeface::Black,FontStyle::Bitmap };
	Font mSmallHpFont{ ConvertToInt((float)0.03 * GetScreenHeight()),Typeface::Black,FontStyle::Bitmap };

	// escapee help font
	Font mEscapeeHelpFont{ ConvertToInt((float)0.03 * GetScreenHeight()),Typeface::Black,FontStyle::Bitmap };

	// game help font
	Font mGameHelpFont{ ConvertToInt((float)0.03 * GetScreenHeight()),Typeface::Black,FontStyle::Bitmap };


	InputGroup inputUp;
	InputGroup inputDown;
	InputGroup inputPause;
	InputGroup inputBack;
	InputGroup inputDecision;

};
