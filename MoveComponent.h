#pragma once
#include"Component.h"

class MoveComponent :public Component {
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime)override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed()const { return mForwardSpeed; }
	float GetYSpeed() const { return mYSpeed; }
	float GetXSpeed()const { return mXSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetYSpeed(float speed) { mYSpeed = speed; }
	void SetXSpeed(float speed) { mXSpeed = speed; }

private:
	float mAngularSpeed;
	float mForwardSpeed;
	float mYSpeed;
	float mXSpeed;
};
