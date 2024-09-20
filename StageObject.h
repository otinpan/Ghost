#pragma onec
#include"CreateStage.h"
#include"StageComponent.h"

class StageObject {
public:
	enum Object
	{
		Brock,
	};

	enum State {
		EActive,
		EPaused,
		EDead,
	};

	StageObject(class CreateStage* createstage);
	virtual ~StageObject();

	void Update(float deltaTime);
	void UpdateStageComponents(float deltaTime);
	virtual void UpdateStageObject(float deltaTime);

	void ProcessInput(const std::vector<Input> keyState);
	virtual void StageObjectInput(const std::vector<Input> keyState);

	const Vec2& GePosition() const { return mPosition; }
	void SetPosition(const Vec2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	void AddStageComponent(class StageComponent* component);
	void RemoveStageComponent(class StageComponent* component);

private:
	State mState;

	Vec2 mPosition;
	float mScale;
	float mRotation;

	bool mIsDead;

	std::vector<class StageComponent*> mStageComponents;
	class CreateStage* mCreateStage;
};
