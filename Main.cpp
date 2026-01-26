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


	Scene::SetBackground({ 1,1,1 });

	while (System::Update()) {
		Cursor::RequestStyle(CursorStyle::Hidden);
		if (!mParent) {
			mParent = new Parent;
		}

		mParent->update();
	}
}

