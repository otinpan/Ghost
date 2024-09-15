# include <Siv3D.hpp> // Siv3D v0.6.15
#include"Common.h"
#include"Game.h"
#include"Parent.h"

void Main()
{
	Window::SetStyle(WindowStyle::Sizable);
	Parent* mParent = 0;

	Scene::SetBackground({ 1,1,1 });

	while (System::Update()) {
		if (!mParent) {
			mParent = new Parent;
		}

		mParent->update();
	}
}

