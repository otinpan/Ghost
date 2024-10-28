#include"Candle.h"
#include"Stage.h"

Candle::Candle(Vec2 pos,float width,float height,float rad)
	:StageObject(pos,width,height)
	,mCenter(pos)
	,cc(0)
{
	SetAttribute(Attribute::Candle);
	SetRadius(rad);
	SetLightRad(rad *3.0);

}

Candle::~Candle() {
}

void Candle::InitializeStageObject_CreateStage(class CreateStage* createStage) {
	InitializeActor_CreateStage(createStage);
	SetMaxLightRad(GetCreateStage()->GetStage()->GetHeight() / 2);
	SetMinLightRad(0.0f);

	cc = new CircleComponent(this);
	cc->Initialize_CreateStage();
	cc->SetCenter(GetPosition());
	cc->SetRadius(GetLightRad());
	cc->SetColor(ColorF(1, 1, float(202 / 255),0.5));
}

void Candle::UpdateStageObject_CreateStage(float deltaTime) {
	cc->SetCenter(GetPosition());
	cc->SetRadius(GetLightRad());
}
