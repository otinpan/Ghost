# include <Siv3D.hpp> // Siv3D v0.6.15
#include"Common.h"
#include"Game.h"
#include"Parent.h"

void Main()
{
	
	Parent* mParent = 0;
	//Scene::Resize(16*60, 9*60);
	Scene::Resize(16 * 60,  9 * 60);
	Window::Resize(16 * 60, 9 * 60);
	Window::SetStyle(WindowStyle::Fixed);

	// Asset
	TextureAsset::Register(U"brock_stone", U"StageObject/brock_stone.png");
	TextureAsset::Register(U"brock_grass", U"StageObject/brock_grass.png");
	TextureAsset::Register(U"brock_wood", U"StageObject/brock_wood.png");
	TextureAsset::Register(U"candle", U"StageObject/candle.png");
	TextureAsset::Register(U"door_up", U"StageObject/door_up.png");
	TextureAsset::Register(U"door_left", U"StageObject/door_left.png");
	TextureAsset::Register(U"door_down", U"StageObject/door_down.png");
	TextureAsset::Register(U"door_right", U"StageObject/door_right.png");
	TextureAsset::Register(U"key", U"StageObject/key_yellow.png");
	TextureAsset::Register(U"treasure", U"StageObject/treasure.png");
	TextureAsset::Register(U"battery", U"StageObject/battery.png");
	TextureAsset::Register(U"keyboard", U"Keyboard.png");
	TextureAsset::Register(U"cursor_arrow", U"cursor_arrow.png");
	TextureAsset::Register(U"cursor_hand", U"cursor_hand.png");
	TextureAsset::Register(U"ghost", U"ghost.png");
	TextureAsset::Register(U"escapee1", U"escapee1.png");
	TextureAsset::Register(U"escapee2", U"escapee2.png");
	TextureAsset::Register(U"escapee3", U"escapee3.png");
	TextureAsset::Register(U"patrol", U"StageObject/patrol.png");
	TextureAsset::Register(U"escapee1_heart", U"escapee1_heart.png");
	TextureAsset::Register(U"escapee2_heart", U"escapee2_heart.png");
	TextureAsset::Register(U"escapee3_heart", U"escapee3_heart.png");
	// rule
	TextureAsset::Register(U"rule_game", U"Rule/game.png");
	TextureAsset::Register(U"rule_escapee1", U"Rule/escapee1.png");
	TextureAsset::Register(U"rule_escapee2", U"Rule/escapee2.png");
	TextureAsset::Register(U"rule_ghost1", U"Rule/ghost1.png");
	TextureAsset::Register(U"rule_object", U"Rule/object.png");
	TextureAsset::Register(U"rule_create", U"Rule/create.png");
	TextureAsset::Register(U"rule_AI_create", U"Rule/AI_create.png");
	TextureAsset::Register(U"rule_minigame", U"Rule/minigame.png");


	Scene::SetBackground({ 1,1,1 });

	while (System::Update()) {
		Cursor::RequestStyle(CursorStyle::Hidden);
		if (!mParent) {
			mParent = new Parent;
		}

		mParent->update();
	}
}

