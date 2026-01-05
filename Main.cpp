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
	TextureAsset::Register(U"brock_stone", Resource(U"StageObject/brock_stone.png"));
	TextureAsset::Register(U"brock_grass", Resource(U"StageObject/brock_grass.png"));
	TextureAsset::Register(U"brock_wood", Resource(U"StageObject/brock_wood.png"));
	TextureAsset::Register(U"candle", Resource(U"StageObject/candle.png"));
	TextureAsset::Register(U"door_front", Resource(U"StageObject/door_front.png"));
	TextureAsset::Register(U"door_side", Resource(U"StageObject/door_side.png"));
	TextureAsset::Register(U"key", Resource(U"StageObject/key.png"));
	TextureAsset::Register(U"treasure", Resource(U"StageObject/treasure.png"));
	TextureAsset::Register(U"battery", Resource(U"StageObject/battery.png"));


	Scene::SetBackground({ 1,1,1 });

	while (System::Update()) {
		if (!mParent) {
			mParent = new Parent;
		}

		mParent->update();
	}
}

