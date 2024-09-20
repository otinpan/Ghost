#include"StageComponent.h"

StageComponent::StageComponent(StageObject* owner, int updateOrder)
	:mOwner(owner)
	, mUpdateOrder(updateOrder)
{
	mOwner->AddStageComponent(this);
}


StageComponent::~StageComponent() {
	mOwner->RemoveStageComponent(this);
}

void StageComponent::Update(float deltaTime) {

}
