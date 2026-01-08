#include"RegisterController.h"

RegisterController::RegisterController()
	:mSeqID(Parent::SEQ_NONE)
	, mIsRunning(true)
	, mIsAccepted(false)
{
	Initialize();
}


RegisterController::~RegisterController() {

}


void RegisterController::Initialize() {
	Scene::SetBackground(ColorF(0.7f));


	mControllersPos.resize(4);
	eachWidth = 1.8f / 4;
	for (int i = 0; i < 4; i++) {
		mControllersPos[i] = Vec2(-0.9+eachWidth*(i+0.5f), -0.5f);
	}

	drawSize = eachWidth *0.95;

	TextureAsset::Load(U"keyboard");

	mControllers.emplace_back(Controller::ControllerType::JOYCON_L2);
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

	// 接続が切れたコントローラーを削除
	DeleteCanceledController();

	// コントローラー登録
	if (mControllers.size() < 3 ) {
		if (KeyEnter.down()&& !IsExistController(Controller::ControllerType::KEYBOARD)) {
			mControllers.emplace_back(Controller::ControllerType::KEYBOARD);
		}
	}
	if (mControllers.size() < 3) {
		if (auto joy = JoyConL(0)) {
			if (joy.buttonSR.pressed() && joy.buttonSL.pressed() && !IsExistController(Controller::ControllerType::JOYCON_L0)) {
				mControllers.emplace_back(Controller::ControllerType::JOYCON_L0);
			}
		}
	}
	if (mControllers.size() < 3) {
		if (auto joy = JoyConL(1)) {
			if (joy.buttonSR.pressed() && joy.buttonSL.pressed() && !IsExistController(Controller::ControllerType::JOYCON_L1)) {
				mControllers.emplace_back(Controller::ControllerType::JOYCON_L1);
			}
		}
	}
	if (mControllers.size() < 3) {
		if (auto joy = JoyConL(2)) {
			if (joy.buttonSR.pressed() && joy.buttonSL.pressed() && !IsExistController(Controller::ControllerType::JOYCON_L2)) {
				mControllers.emplace_back(Controller::ControllerType::JOYCON_L2);
			}
		}
	}
	if (mControllers.size() < 3) {
		if (auto joy = JoyConL(3)) {
			if (joy.buttonSR.pressed() && joy.buttonSL.pressed() && !IsExistController(Controller::ControllerType::JOYCON_L3)) {
				mControllers.emplace_back(Controller::ControllerType::JOYCON_L3);
			}
		}
	}
	if (mControllers.size() < 3) {
		if (auto joy = JoyConR(0)) {
			if (joy.buttonSR.pressed() && joy.buttonSL.pressed() && !IsExistController(Controller::ControllerType::JOYCON_R0)) {
				mControllers.emplace_back(Controller::ControllerType::JOYCON_R0);
			}
		}
	}
	if (mControllers.size() < 3) {
		if (auto joy = JoyConR(1)) {
			if (joy.buttonSR.pressed() && joy.buttonSL.pressed() && !IsExistController(Controller::ControllerType::JOYCON_R1)) {
				mControllers.emplace_back(Controller::ControllerType::JOYCON_R1);
			}
		}
	}
	if (mControllers.size() < 3) {
		if (auto joy = JoyConR(2)) {
			if (joy.buttonSR.pressed() && joy.buttonSL.pressed() && !IsExistController(Controller::ControllerType::JOYCON_R2)) {
				mControllers.emplace_back(Controller::ControllerType::JOYCON_R2);
			}
		}
	}
	if (mControllers.size() < 3) {
		if (auto joy = JoyConR(3)) {
			if (joy.buttonSR.pressed() && joy.buttonSL.pressed() && !IsExistController(Controller::ControllerType::JOYCON_R3)) {
				mControllers.emplace_back(Controller::ControllerType::JOYCON_R3);
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
		if (joy.buttonPlus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_R0);
		}
	}
	if (auto joy = JoyConR(1)) {
		if (joy.buttonPlus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_R1);
		}
	}
	if (auto joy = JoyConR(2)) {
		if (joy.buttonPlus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_R2);
		}
	}
	if (auto joy = JoyConR(3)) {
		if (joy.buttonPlus.down()) {
			DeleteController(Controller::ControllerType::JOYCON_R3);
		}
	}


	// 人数チェック
	if (mControllers.size() >= 2 && mControllers.size() <= 4) {
		mIsAccepted = true;
	}
	else {
		mIsAccepted = false;
	}

	// シーン変更
	if (mIsAccepted && (KeySpace.down() || KeyRight.down())) {
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
	auto iter = std::find(mControllers.begin(), mControllers.end(), type);
	if (iter == mControllers.end()) {
		return false;
	}

	return true;
}

// typeがmControllersに存在するなら削除
bool RegisterController::DeleteController(Controller::ControllerType type) {
	auto iter = std::find(mControllers.begin(), mControllers.end(), type);
	if (iter == mControllers.end()) {
		return false;
	}

	mControllers.erase(iter);
	return true;
}

void RegisterController::DeleteCanceledController()
{
	Array<Controller::ControllerType> toDelete;

	for (const auto controller : mControllers)
	{
		if (controller == Controller::ControllerType::KEYBOARD)
		{
			continue;
		}


		switch (controller)
		{
		case Controller::ControllerType::JOYCON_L0:
			if (const auto joy = JoyConL(0)) {
				break;
			}
			else {
				DeleteController(Controller::ControllerType::JOYCON_L0);
			}
			break;
		case Controller::ControllerType::JOYCON_L1:
			if (const auto joy = JoyConL(1)) {
				break;
			}
			else {
				DeleteController(Controller::ControllerType::JOYCON_L1);
			}
			break;
		case Controller::ControllerType::JOYCON_L2:
			if (const auto joy = JoyConL(2)) {
				break;
			}
			else {
				DeleteController(Controller::ControllerType::JOYCON_L2);
			}
			break;
		case Controller::ControllerType::JOYCON_L3:
			if (const auto joy = JoyConL(3)) {
				break;
			}
			else {
				DeleteController(Controller::ControllerType::JOYCON_L3);
			}
			break;
		case Controller::ControllerType::JOYCON_R0:
			if (const auto joy = JoyConR(0)) {
				break;
			}
			else {
				DeleteController(Controller::ControllerType::JOYCON_R0);
			}
			break;
		case Controller::ControllerType::JOYCON_R1:
			if (const auto joy = JoyConR(1)) {
				break;
			}
			else {
				DeleteController(Controller::ControllerType::JOYCON_R1);
			}
			break;
		case Controller::ControllerType::JOYCON_R2:
			if (const auto joy = JoyConR(2)) {
				break;
			}
			else {
				DeleteController(Controller::ControllerType::JOYCON_R2);
			}
			break;
		case Controller::ControllerType::JOYCON_R3:
			if (const auto joy = JoyConR(3)) {
				break;
			}
			else {
				DeleteController(Controller::ControllerType::JOYCON_R3);
			}
			break;
		default:
			continue; // returnしない
		}
	}


}




void RegisterController::draw() {
	if (mIsAccepted) {
		Print << U"Press Space to Start";
	}
	Print << mControllers.size();
	for (auto x : mControllers) {
		Print << x;
	}

	if (mIsAccepted) {
		// todo
		// 登録完了OK表示
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

	effect.update();

}

void RegisterController::DrawKeyboard(Vec2 pos) {

	//keyoboard描画
	float WritingWidth = (float)eachWidth / 2.0 *
		GetScreenWidth();
	float WritingHeight = (float)0.7 / 2.0 *
		GetScreenHeight();
	Texture(TextureAsset(U"keyboard")).resized(WritingWidth, WritingHeight).
		scaled(1.0f).rotated(0.0f).
		drawAt(ConvertToView(pos));


	const Array<Input>& inputs = s3d::Keyboard::GetAllInputs();
	for (const auto& input: inputs) {
		if (input.down()) {
			// effectの追加
			effect.add([center = pos](double t) {
				float size = 0.01 + 0.1 * t;
				size *= GetScreenWidth() / 2.0f;
				float frameSize = 0.005 * GetScreenWidth() / 2.0f;
				Circle(ConvertToView(center), size).drawFrame(frameSize, 0, ColorF(1.0, (1.0 - t)));
				return t < 1.0f;
			});
		}
	}
}

void RegisterController::DrawJoyCon(Controller::ControllerType type, Vec2 pos) {
	float angle = 0_deg;
	bool covered = true;

	Vec2 stickPos = Vec2(pos.x ,pos.y);
	
	Optional<JoyCon> joy;
	bool isLeft=false;
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

	bool isStick=false;

	if (joy.has_value()) {
		if (isLeft) {
			joy->drawAt(ConvertToView(pos), drawSize * GetScreenWidth() / 2.0f, -90_deg - angle, covered);
		}
		else {
			joy->drawAt(ConvertToView(pos), drawSize * GetScreenWidth() / 2.0f, 90_deg + angle, covered);
		}

		if (auto d = joy->povD8()) {
			isStick = true;
			stickPos += Circular{ 0.2f,180_deg-(*d * 45_deg) }; //半径、角度
		}

		if (joy->button0.down()||joy->button1.down()||joy->button2.down()||joy->button3.down()) {
			Vec2 effPos;
			if (isStick)effPos = stickPos;
			else effPos = pos;
	
			effect.add([center = effPos](double t) {
				float size = 0.01 + 0.1 * t;
				size *= GetScreenWidth() / 2.0f;
				float frameSize = 0.005 * GetScreenWidth() / 2.0f;
				Circle(ConvertToView(center), size).drawFrame(frameSize, 0, ColorF(1.0, (1.0 - t)));
				return t < 1.0f;
			});
			
		}
	}
	if (isStick) {
		DrawCircle(stickPos, 0.02, ColorF(1.0f));
	}
	effect.update();
}


void RegisterController::Shutdown() {

}

void RegisterController::moveTo(Parent* parent, Parent::SeqID id) {
	if (id == Parent::SEQ_MAINMENU)parent->moveTo(Parent::SEQ_MAINMENU, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_STAGESELECT) {
		parent->setControllers(mControllers);
		parent->setStageSelectGame(true);
		parent->moveTo(Parent::SEQ_STAGESELECT, Parent::SEQ_REGISTERCONTROLLER);
	}
	if (id == Parent::SEQ_GAME)parent->moveTo(Parent::SEQ_GAME, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_CREATESTAGE)parent->moveTo(Parent::SEQ_CREATESTAGE, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_GAMERESULT)parent->moveTo(Parent::SEQ_GAMERESULT, Parent::SEQ_REGISTERCONTROLLER);
	if (id == Parent::SEQ_CHANGEWINDOWSIZE)parent->moveTo(Parent::SEQ_CHANGEWINDOWSIZE, Parent::SEQ_REGISTERCONTROLLER);
}
