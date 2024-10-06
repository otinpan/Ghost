#include"Brock.h"

Brock::Brock(Vec2 pos,float width, float height)
	:StageObject(pos,width,height)
{
	SetAttribute(Attribute::Brock);
}

Brock::~Brock() {
	
}


