#include"Hand.h"
#include"CircleComponent.h"
#include"InputComponent_Keyboard.h"
#include"CreateStage.h"
#include"StageObject.h"
#include"Stage.h"
#include<Siv3D.hpp>
#include"Brock.h"
#include"Wall.h"

Hand::Hand()
	:StandardSpeed(0.3f)
	,ic(nullptr)
	,cc(nullptr)
	,mIsGrap(false)
	,mIsExpand(false)
	,mGrapping(nullptr)
{

}

Hand::~Hand()
{

}

void Hand::InitializeActor_CreateStage(CreateStage* createstage) {
	Initialize_CreateStage(createstage);
	SetPosition({ 0.0f,0.0f });

	cc = new CircleComponent(this);
	cc->Initialize_CreateStage();
	cc->SetRadius(0.003f);
	cc->SetColor({ 1.0,0.0,0.0 });

	inputUp = KeyW;
	inputDown = KeyS;
	inputRight = KeyD;
	inputLeft = KeyA;
	inputGrap = KeyEnter;
	inputBack = KeyL;
	inputClockwise = KeyRight;
	inputCounterClockwise = KeyLeft;
	inputDecision = KeySpace;

	ic = new InputComponent_Keyboard(this);
	ic->SetUpKey(inputUp);
	ic->SetDownKey(inputDown);
	ic->SetRightKey(inputRight);
	ic->SetLeftKey(inputLeft);
	ic->SetMaxXSpeed(StandardSpeed);
	ic->SetMaxYSpeed(StandardSpeed);

	dx = { -1,1,1,-1 };
	dy = { 1,1,-1,-1 };

}

void Hand::UpdateActor_CreateStage(float deltaTime) {
	Vec2 nowPos = GetPosition();
	if (nowPos.x < -0.95)nowPos.x = -0.95;
	if (nowPos.x > 0.95)nowPos.x = 0.95;
	if (nowPos.y < -0.95)nowPos.y = -0.95;
	if (nowPos.y > 0.95)nowPos.y = 0.95;
	SetPosition(nowPos);
	cc->SetCenter(nowPos);

	if (!mIsGrap&&!mIsExpand) {
		for (auto &stageObject : GetCreateStage()->GetStageObjects()) {
			if (stageObject->GetSquareComponent()->GetRect().
				contains(cc->GetCircle()) && 
			    stageObject->GetAttribute() != StageObject::Attribute::Wall) {
				//stageの中にある場合拡大可能
				if (stageObject->GetIsInStage()) {
					if (stageObject->GetAttribute() == StageObject::Attribute::Brock) {
						for (int i = 0;
							i < stageObject->GetCircleComponents().size();
							i++) {
							if (stageObject->GetCircleComponents()[i]
								->GetCircle().contains(cc->GetCircle())&&
								inputGrap.pressed()) {
								mIsExpand = true;
								//支点となるItertionをstageが保存
								GetCreateStage()->GetStage()->
									SetExpandFulcrumIter(stageObject->GetIteration());
								//支点となるObjectの属性をstageが保存
								GetCreateStage()->GetStage()->
									SetExpandAttribute(stageObject->GetAttribute());
								return;
							}
						}
					}
				}
				if (!mIsExpand) {
					if (inputGrap.pressed()) {
						stageObject->SetIsGripen(true);
						mIsGrap = true;
						mGrapping = stageObject;
						return;
					}
				}
			}
			
		}
	}
	if (mIsExpand) {
		//拡大の解除
		if (!inputGrap.pressed()) {
			GetCreateStage()->GetStage()->RemakeStageObjects();
			mIsExpand = false;
		}
	}

	if(mIsGrap){
		if (!inputGrap.pressed()) {
			mGrapping->SetIsGripen(false);
			//StageのmRectsとの当たり判定
			for (int i = 0; i < GetCreateStage()->GetStage()->GetVerticalSize(); i++) {
				for (int j = 0; j < GetCreateStage()->GetStage()->GetSideSize();j++) {
					if (GetCreateStage()->GetStage()->GetRects()[i][j]
						.contains(cc->GetCircle())&&
						GetCreateStage()->GetStage()->GetStageObjects()[i][j]==0) {
						GetCreateStage()->GetStage()->SetNewStageObject(i, j,mGrapping->GetAttribute());
					}
				}
			}
			delete mGrapping;
			mIsGrap = false;
		}
	}
}

void Hand::ActorInput(std::vector<Input> keyState) {

}

