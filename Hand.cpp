#include"Hand.h"
#include"CircleComponent.h"
#include"InputComponent_Keyboard.h"
#include"CreateStage.h"
#include"StageObject.h"
#include"Stage.h"
#include<Siv3D.hpp>
#include"Brock.h"
#include"Wall.h"
#include"Door.h"
#include"StageMenu.h"
#include"SquareComponent.h"
#include"CircleComponent.h"

Hand::Hand()
	:StandardSpeed(0.3f)
	,ic(nullptr)
	,cc(nullptr)
	,mIsGrap(false)
	,mIsExpand(false)
	,mIsChoose(false)
	,mIsDelete(false)
	,mGrapping(nullptr)
	,mChoosing(nullptr)
{

}

Hand::~Hand()
{

}

void Hand::InitializeActor_CreateStage(CreateStage* createstage) {
	Initialize_CreateStage(createstage);
	SetPosition({ 0.0f,-0.7f });

	cc = new CircleComponent(this, 300, DrawingComponent::DrawingState::UNAFFECTED);
	cc->InitializeDrawing_CreateStage();
	cc->SetRadius(0.003f);
	cc->SetColor({ 1.0,0.0,0.0 });

	
	inputGrap = KeyEnter;
	inputBack = KeyK;
	inputR = KeyRight;
	inputL = KeyLeft;
	inputU = KeyUp;
	inputD = KeyDown;
	inputChoose = KeySpace;
	inputDelete = KeyDelete;
	inputPlus = KeyPeriod;
	inputMinus = KeyComma;

	ic = new InputComponent_Keyboard(this);
	ic->Initialize();
	inputLeft = KeyA;
	inputRight = KeyD;
	inputUp = KeyW;
	inputDown = KeyS;
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

	if (!mIsGrap && !mIsExpand && !mIsDelete) {
		for (auto& stageObject : GetCreateStage()->GetStageObjects()) {
			if (stageObject->GetSquareComponent()->GetRect().
				contains(cc->GetCircle()) &&
				stageObject->GetAttribute() != StageObject::Attribute::Wall) {
				//stageの中にある場合拡大可能
				if (stageObject->GetIsInStage() && !mIsDelete) {
					//Brockは拡大可能
					if (stageObject->GetAttribute() == StageObject::Attribute::Brock) {
						for (int i = 0;
							i < stageObject->GetCircleComponents().size();
							i++) {
							if (stageObject->GetCircleComponents()[i]
								->GetCircle().contains(cc->GetCircle()) &&
								inputGrap.pressed()) {
								DeleteChoosing();//Chooseを消す
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
				//Grap
				if (!mIsExpand && !mIsDelete) {
					if (inputGrap.pressed()) {
						stageObject->SetIsGripen(true);
						mIsGrap = true;
						DeleteChoosing();
						mGrapping = stageObject;
						return;
					}
				}

				//Choose
				if (inputChoose.down() && stageObject->GetIsInStage()) {
					InitChoosing(stageObject);
					return;
				}
			}

		}

		//End CreateStage
		if (GetCreateStage()->GetStage()->GetIsSaveError()) {
			if (inputChoose.down()) {
				GetCreateStage()->GetStage()->SetIsSaveError(false);
			}
		}
		if (cc->GetViewCircle().
			intersects(GetViewRect(GetCreateStage()->GetStageMenu()->GetEndPos(),
				GetCreateStage()->GetStageMenu()->GetEndRectWidth(),
				GetCreateStage()->GetStageMenu()->GetEndRectHeight()))) {
			GetCreateStage()->GetStageMenu()->SetIsEndOver(true);
			if (inputChoose.down()) {
				GetCreateStage()->OpenTextMenu();
			}
		}
		else {
			GetCreateStage()->GetStageMenu()->SetIsEndOver(false);
		}

		// ChatGPT Menu
		if(cc->GetViewCircle().
			intersects(GetViewRect(GetCreateStage()->GetStageMenu()->GetGPTMenuPos(),
				GetCreateStage()->GetStageMenu()->GetGPTMenuWidth(),
				GetCreateStage()->GetStageMenu()->GetGPTMenuHeight()))) {
			GetCreateStage()->GetStageMenu()->SetIsGPTMenuOver(true);
			if (inputChoose.down()) {
				GetCreateStage()->OpenGPTMenu();
			}
		}
		else {
			GetCreateStage()->GetStageMenu()->SetIsGPTMenuOver(false);
		}
		
	}
	//Delete
	if (!mIsGrap && !mIsExpand && !mIsDelete) {
		if (inputDelete.pressed()) {
			mIsDelete = true;
			mIsChoose = false;
			GetCreateStage()->GetStage()->SetDeleteFulcrumPos(GetPosition());
			return;
		}
	}
	if (mIsChoose) {
		mChoosing->UpdateStageMenu_CreateStage(deltaTime);
		//stage外でChooseが押された場合mCooseが選択されていない状態にする
		if (inputChoose.down()) {
			if (!(GetCreateStage()->GetStageMenu()->GetViewStageMenuRect().
				contains(cc->GetViewCircle()))) {
				DeleteChoosing();
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

	if (mIsDelete) {
		if (!inputDelete.pressed()) {
			GetCreateStage()->GetStage()->DeleteStageObjects();
			mIsDelete = false;
		}
		DeleteChoosing();
	}


	if (mIsGrap) {
		if (!inputGrap.pressed()) {
			mGrapping->SetIsGripen(false);
			//Candle
			if (mGrapping->GetAttribute() == StageObject::Attribute::Candle) {
				if (GetCreateStage()->GetStage()->GetViewStageRect().
					contains(mGrapping->GetSquareComponent()->GetViewRect())) {
					if (mGrapping->GetIsInStage()) {
						//GetCreateStage()->GetStage()->DeleteCandle(mGrapping);
					}
					
					GetCreateStage()->GetStage()->SetNewCandle(mGrapping);
					
				}
				//もしmGrappingがObjectMenuから取り出した場合
				if (mGrapping->GetIsInObjectMenu()) {
					GetCreateStage()->GetStageMenu()->RemakeStageObject(mGrapping);
				}
				
				delete mGrapping;
				mIsGrap = false;
				return;
			}
			mIsSetOnStage = false;
			//StageのmRectsとの当たり判定
			for (int i = 0; i < GetCreateStage()->GetStage()->GetVerticalSize(); i++) {
				for (int j = 0; j < GetCreateStage()->GetStage()->GetSideSize(); j++) {
					if (GetCreateStage()->GetStage()->GetRects()[i][j]
						.contains(cc->GetCircle()) &&
						GetCreateStage()->GetStage()->GetStageObjects()[i][j] == 0) {
						GetCreateStage()->GetStage()->SetNewStageObject(i, j, mGrapping);
						mIsSetOnStage = true;
						break;
					}
				}
			}

			//もしmGrappingがObjectMenuから取り出した場合
			if (mGrapping->GetIsInObjectMenu()) {
				GetCreateStage()->GetStageMenu()->RemakeStageObject(mGrapping);
			}

			if (!mIsSetOnStage) {
				GetCreateStage()->GetStageMenu()->RemakePlayer(mGrapping);
			}
			delete mGrapping;
			mGrapping = 0;
			mIsGrap = false;
		}
	}

	if (Cursor::PosF() != Cursor::PreviousPosF()) {
		SetPosition(ConvertToWorld(Cursor::PosF()));
	}
}

void Hand::InitChoosing(class StageObject* stageObject) {
	if (mChoosing != 0) {
		mChoosing->ShutdownStageMenu_CreateStage();
	}
	mChoosing = stageObject;
	mChoosing->InitializeStageMenu_CreateStage();
	mChoosing->SetIsChosen(true);
	mIsChoose = true;
}

void Hand::DeleteChoosing() {
	if (mChoosing) {
		mChoosing->ShutdownStageMenu_CreateStage();
		mChoosing = 0;
	}
	mIsChoose = false;
}

void Hand::ActorInput(std::vector<Input> keyState) {

}

