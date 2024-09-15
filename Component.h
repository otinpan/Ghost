#pragma once
#include<Siv3D.hpp>
#include <cstdint>

class Component
{
public:
	// Constructor
	// (the lower the update order, the earlier the component updates)
	Component(class Actor* owner, int updateOrder = 100);
	// Destructor
	virtual ~Component();
	// Update this component by delta time
	virtual void Update(float deltaTime);
	// Process input for this component
	virtual void ProcessInput(const std::vector<Input> keyState) {}

	class Actor* GetOwner() { return mOwner; }

	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// Owning actor
	class Actor* mOwner;
	// Update order of component
	int mUpdateOrder;
};

