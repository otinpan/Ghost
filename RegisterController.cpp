#include"RegisterController.h"

RegisterController::RegisterController()
	:mSeqID(Parent::SEQ_NONE)
	, mIsRunning(true)
{
	Initialize();
}


RegisterController::~RegisterController() {

}


void RegisterController::Initialize() {
	Scene::SetBackground(ColorF(0.7f));

	mControllerIteration = 0;

	mControllersPos.resize(4);
	float eachWidth = 1.8f / 4;
	for (int i = 0; i < 4; i++) {
		mControllersPos[i] = Vec2(0.5, -0.9f+eachWidth * (i + 0.5f));
	}

	drawSize = eachWidth * 0.75;
}

void RegisterController::update(Parent* parent) {
	if (mIsRunning) {
		if (mSeqID != Parent::SEQ_NONE) {
			moveTo(parent, mSeqID);
		}
	}

	ClearPrint();
	ProcessInput();
	UpdateRegisterController();
	draw();
}

void RegisterController::ProcessInput() {

}


void RegisterController::UpdateRegisterController() {
	float deltaTime = Scene::DeltaTime();

	// コントローラー登録
	if (mControllerIteration < 3 ) {
		if (KeyEnter.down()&& !IsExistController(Controller::ControllerType::KEYBOARD)) {
			mControllers[mControllerIteration] = Controller::ControllerType::KEYBOARD;
			mControllerIteration++;
		}
	}
	if (mControllerIteration < 3) {
		if (auto joy = JoyConL(0)) {
			if (joy.buttonSR.down() && joy.buttonSL.down() && !IsExistController(Controller::ControllerType::JOYCON_L0)) {
				mControllers[mControllerIteration]=Controller::ControllerType::JOYCON_L0;
				mControllerIteration++;
			}
		}
	}
	if (mControllerIteration < 3) {
		if (auto joy = JoyConL(1)) {
			if (joy.buttonSR.down() && joy.buttonSL.down() && !IsExistController(Controller::ControllerType::JOYCON_L1)) {
				mControllers[mControllerIteration] = Controller::ControllerType::JOYCON_L1;
				mControllerIteration++;
			}
		}
	}
	if (mControllerIteration < 3) {
		if (auto joy = JoyConL(2)) {
			if (joy.buttonSR.down() && joy.buttonSL.down() && !IsExistController(Controller::ControllerType::JOYCON_L2)) {
				mControllers[mControllerIteration] = Controller::ControllerType::JOYCON_L2;
				mControllerIteration++;
			}
		}
	}
	if (mControllerIteration < 3) {
		if (auto joy = JoyConL(3)) {
			if (joy.buttonSR.down() && joy.buttonSL.down() && !IsExistController(Controller::ControllerType::JOYCON_L3)) {
				mControllers[mControllerIteration] = Controller::ControllerType::JOYCON_L3;
				mControllerIteration++;
			}
		}
	}
	if (mControllerIteration < 3) {
		if (auto joy = JoyConR(0)) {
			if (joy.buttonSR.down() && joy.buttonSL.down() && !IsExistController(Controller::ControllerType::JOYCON_R0)) {
				mControllers[mControllerIteration] = Controller::ControllerType::JOYCON_R0;
				mControllerIteration++;
			}
		}
	}
	if (mControllerIteration < 3) {
		if (auto joy = JoyConR(1)) {
			if (joy.buttonSR.down() && joy.buttonSL.down() && !IsExistController(Controller::ControllerType::JOYCON_R1)) {
				mControllers[mControllerIteration] = Controller::ControllerType::JOYCON_R1;
				mControllerIteration++;
			}
		}
	}
	if (mControllerIteration < 3) {
		if (auto joy = JoyConR(2)) {
			if (joy.buttonSR.down() && joy.buttonSL.down() && !IsExistController(Controller::ControllerType::JOYCON_R2)) {
				mControllers[mControllerIteration] = Controller::ControllerType::JOYCON_R2;
				mControllerIteration++;
			}
		}
	}
	if (mControllerIteration < 3) {
		if (auto joy = JoyConR(3)) {
			if (joy.buttonSR.down() && joy.buttonSL.down() && !IsExistController(Controller::ControllerType::JOYCON_R3)) {
				mControllers[mControllerIteration] = Controller::ControllerType::JOYCON_R3;
				mControllerIteration++;
			}
		}
	}

	// コントローラー削除
	if (KeyDelete.down()) {
		DeleteController(Controller::ControllerType::KEYBOARD);
	}
	if (auto joy = JoyConL(0)) {
		if (joy.buttonMinus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_L0);
		}
	}
	if (auto joy = JoyConL(1)) {
		if (joy.buttonMinus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_L1);
		}
	}
	if (auto joy = JoyConL(2)) {
		if (joy.buttonMinus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_L2);
		}
	}
	if (auto joy = JoyConL(3)) {
		if (joy.buttonMinus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_L3);
		}
	}
	if (auto joy = JoyConR(0)) {
		if (joy.buttonMinus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_R0);
		}
	}
	if (auto joy = JoyConR(1)) {
		if (joy.buttonMinus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_R1);
		}
	}
	if (auto joy = JoyConR(2)) {
		if (joy.buttonMinus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_R2);
		}
	}
	if (auto joy = JoyConR(3)) {
		if (joy.buttonMinus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_R3);
		}
	}

	// シーン変更
	if (mControllers.size()>=2&& (KeySpace.down()||KeyRight.down())) {
		mSeqID = Parent::SEQ_STAGESELECT;
		return;
	}


	if (KeyBackspace.down() || KeyLeft.down()) {
		mSeqID = Parent::SEQ_MAINMENU;
		return;
	}

	if (const auto joy = JoyConL(0)) {
		auto d = joy.povD8();
	}

}

bool RegisterController::IsExistController(Controller::ControllerType type) {
	for (auto controller : mControllers) {
		if (controller == type) {
			return true;
		}
	}
	return false;
}

bool RegisterController::DeleteController(Controller::ControllerType type) {
	auto iter = std::find(mControllers.begin(), mControllers.end(), type);
	if (iter == mControllers.end()) {
		return false;
	}

	mControllers.erase(iter);
	mControllerIteration--;
	return true;
}



void RegisterController::draw() {
	ClearPrint();
	Print << mControllers.size();
	for (auto c : mControllers) {
		Print << c;
	}

	for (int i = 0; i < mControllers.size(); i++) {
		if (mControllers[i] == Controller::ControllerType::NONE) {
			assert(U"controller is none!!!");
		}
		if (mControllers[i] == Controller::ControllerType::KEYBOARD) {
			DrawKeyboard(mControllersPos[i]);
		}
		else {
			DrawJoyCon(mControllers[i], mControllersPos[i]);
		}
		
	}

}

void RegisterController::DrawKeyboard(Vec2 pos) {

}

void RegisterController::DrawJoyCon(Controller::ControllerType type, Vec2 pos) {
	Effect effect;
	float angle = 0_deg;
	bool covered = true;

	Vec2 stickPos = Vec2(pos.x - 0.05, pos.y);
	
	Optional<JoyCon> joy;
	bool isLeft;
	switch (type) {
	case Controller::ControllerType::JOYCON_L0:
		joy = JoyConL(0);
		isLeft = true;
		break;
	case Controller::ControllerType::JOYCON_L1:
		joy = JoyConL(1);
		isLeft = true;
		break;
	case Controller::ControllerType::JOYCON_L2:
		joy = JoyConL(2);
		isLeft = true;
		break;
	case Controller::ControllerType::JOYCON_L3:
		isLeft = true;
		joy = JoyConL(3);
		break;
	case Controller::ControllerType::JOYCON_R0:
		joy = JoyConR(0);
		break;
	case Controller::ControllerType::JOYCON_R1:
		joy = JoyConR(1);
		break;
	case Controller::ControllerType::JOYCON_R2:
		joy = JoyConR(2);
		break;
	case Controller::ControllerType::JOYCON_R3:
		joy = JoyConR(3);
		break;
	default:
		joy = none;
		return;
	}



	if (joy.has_value()) {
		if (isLeft) {
			joy->drawAt(ConvertToView(pos), drawSize * GetScreenWidth() / 2.0f, -90_deg - angle, covered);
		}
		else {
			joy->drawAt(ConvertToView(pos), drawSize * GetScreenWidth() / 2.0f, 90_deg + angle, covered);
		}

		if (auto d = joy->povD8()) {
			stickPos += Circular{ 0.04f,*d * 45_deg };
		}

		if (joy->button2.down()) {
			effect.add([center = stickPos](double t) {
				float size = 0.01 + 0.1 * t;
				size *= GetScreenWidth() / 2.0f;
				float frameSize = 0.005 * GetScreenWidth() / 2.0f;
				Circle(ConvertToView(center), size).drawFrame(frameSize, 0, ColorF(1.0, (1.0 - t)));
				return t < 1.0f;
			});
		}
	}
	DrawCircle(stickPos, 0.02, ColorF(1.0f));
	effect.update();
}


void RegisterController::Shutdown() {

}

void RegisterController::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_STAGESELECT) {
		parent->setStageSelectGame(true);
		parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_REGISTERCONTROLLER);
	}
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_REGISTERCONTROLLER);
}
