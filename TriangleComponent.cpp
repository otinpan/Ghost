#include"TriangleComponent.h"
#include"CircleComponent.h"
#include"SquareComponent.h"
#include"Actor.h"

TriangleComponent::TriangleComponent(class Actor* owner, int drawOrder, DrawingState drawState)
	:DrawingComponent(owner,drawOrder,drawState)
	, mPos0(Vec2(0, 0))
	, mPos1(Vec2(0, 0))
	, mPos2(Vec2(0, 0))
	, mColor0(0)
	, mColor1(0)
	,mColor2(0)
{

}

TriangleComponent::~TriangleComponent() {
	if (mOwner->GetCreateStage()) {
		mOwner->GetCreateStage()->RemoveTriangle(this);
	}
	if (mOwner->GetGame()) {
		mOwner->GetGame()->RemoveTriangle(this);
	}
}


void TriangleComponent::InitializeDrawing_Game(Vec2 pos0,Vec2 pos1,Vec2 pos2) {
	Initialize_Game();
	mOwner->GetGame()->AddTriangle(this);
	mPos0 = pos0;
	mPos1 = pos1;
	mPos2 = pos2;
}

void TriangleComponent::InitializeDrawing_CreateStage(Vec2 pos0, Vec2 pos1, Vec2 pos2) {
	Initialize_CreateStage();
	mOwner->GetCreateStage()->AddTriangle(this);
	mPos0 = pos0;
	mPos1 = pos1;
	mPos2 = pos2;
}

void TriangleComponent::Draw() {
	if (!GetIsDraw())return;
	DrawTriangle_pos(mPos0, mPos1, mPos2, mColor0, mColor1, mColor2);
}

bool IsIntersect_TT(class TriangleComponent* t1, class TriangleComponent* t2) {
	Triangle Tri1 = Triangle{ t1->GetPos0(),t1->GetPos1(),t1->GetPos2() };
	Triangle Tri2 = Triangle{ t2->GetPos0(),t2->GetPos1(),t2->GetPos2() };
	if (Tri1.intersects(Tri2))return true;
	else return false;
}

bool IsIntersect_TC(class TriangleComponent* t, class CircleComponent* c) {
	Triangle Tri = Triangle(t->GetPos0(), t->GetPos1(), t->GetPos2());
	Circle C = Circle(c->GetCenter(), c->GetRadius());
	if (Tri.intersects(C))return true;
	else return false;
}

bool IsIntersect_TS(class TriangleComponent* t, class SquareComponent* s) {
	Triangle Tri = Triangle(t->GetPos0(), t->GetPos1(), t->GetPos2());
	RectF S = RectF(Arg::center(s->GetCenter()), s->GetWidth(), s->GetHeight());
	if (Tri.intersects(S)) return true;
	else return false;
}
