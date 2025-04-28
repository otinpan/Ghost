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


	Scene::SetBackground({ 1,1,1 });

	while (System::Update()) {
		if (!mParent) {
			mParent = new Parent;
		}

		mParent->update();
	}
}

