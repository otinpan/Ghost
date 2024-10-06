#pragma once
#include"StageObject.h"

class Wall :public StageObject {
public:
	Wall(Vec2 pos, float width, float height);
	~Wall();


};
