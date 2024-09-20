#pragma once
#include"CreateStage.h"
#include"StageObject.h"
#include<Siv3D.hpp>

class StageComponent
{
public:
	StageComponent(class StageObject* owner, int updateOrder = 100);

	virtual ~StageComponent();

	virtual void Update(float deltaTime);
	// Process input for this component
	virtual void ProcessInput(const std::vector<Input> keyState) {}

	class StageObject* GetOwner() { return mOwner; }

	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// Owning actor
	class StageObject* mOwner;
	// Update order of component
	int mUpdateOrder;
};


Vec2 ViewPos(Vec2 pos, float w, float h);

