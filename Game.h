#pragma once
#include"Common.h"
#include"Parent.h"
#include"SquareComponent.h"

class Game {
public:
	Game();
	~Game();
	void update(class Parent*);
	void draw();

	bool Initialize();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddCircle(class CircleComponent* circle);
	void RemoveCircle(class CircleComponent* circle);

	void AddSquare(class SquareComponent* square);
	void RemoveSquare(class SquareComponent* square);

	//Hitstop
	void SetIsHitstop(bool isHitstop) { mIsHitstop = isHitstop; }
	bool GetIsHitstop() { return mIsHitstop; }
	void SetHitstop(float hitstopTime);
	void UpdateHitstop(float deltaTime);

	//class getter
	class Stage* &GetStage() { return mStage; }
	class Ghost_Game* &GetGhost() { return mGhost; }
	class Escapee_Game*& GetEscapee1() { return mEscapee1; }
	class Escapee_Game*& GetEscapee2() { return mEscapee2; }
	class Escapee_Game*& GetEscapee3() { return mEscapee3; }

	//Sequence
	void moveTo(Parent* paretn, Parent::SeqID id);
	void SetSeqID(Parent::SeqID id) { mSeqID = id; }



private:
	void ProcessInput();
    void UpdateGame();
    void LoadData();
	void UnloadData();

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;

	//All the Circle components drawn
	std::vector<class CircleComponent*> mCircles;

	//All the Square component drawn
	std::vector<class SquareComponent*> mSquares;

	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	bool mIsHitstop;  //Hitstopかどうか
	float HitstopTime;
	float mHitstopTime;

	Parent::SeqID mSeqID;

	class Stage* mStage;
	class Escapee_Game* mEscapee1;
	class Escapee_Game* mEscapee2;
	class Escapee_Game* mEscapee3;
	class Ghost_Game* mGhost;

	//RenderTexture
	RenderTexture renderTexture;
	RenderTexture renderTextureLight;
	//Shader
	VertexShader vs2D;
	PixelShader ps2DTexture;
};
