#pragma once
#include"Parent.h"
class Title {
public:
	Title();
	~Title();

	void update(class Parent*);
	void draw();

private:
	float timer = 0.0f;
	Font titleFont{ ConvertToInt((float)0.2 * GetScreenHeight()),Typeface::Bold };
};
