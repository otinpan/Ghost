#include"Wall.h"

Wall::Wall(Vec2 pos, float width, float height)
	:StageObject(pos, width, height)
{
	SetAttribute(Attribute::Wall);
}

Wall::~Wall() {

}
