#include "BackGround.h"
#include "Func.h"
#include "Resource.h"


BackGroundParts::BackGroundParts():
gHandle(Graph::handle("back01")),
gradationHandle(Graph::handle("gra00")),
vel(0.0, Random::FRand(0.001, 0.003)),
basePos(Random::FRand(1.0), Random::FRand(1.0)),
alpha(128),
blendMode(DX_BLENDMODE_ALPHA)
{
	init();
}

void BackGroundParts::init(){
	for (int i = 0; i < 6; i++){
		Vert[i].pos = VGet((i % 2 == 0) ? 0 : 1024.0, (i == 2 || i > 3) ? 1024.0 : 0, 0.0f);
		Vert[i].rhw = 1.0f;
		Vert[i].dif = GetColorU8(255, 255, 255, 255);
		Vert[i].u = (i % 2 == 0) ? 0.0f : 1.0f;
		Vert[i].v = (i == 2 || i>3) ? 1.0f : 0.0f;
	}
	for (int i = 0; i < 6; i++){
		Vert[i].u += basePos.x;
		Vert[i].v -= basePos.y;
	}
}

void BackGroundParts::setGraphHandle(int gh){
	gHandle = gh;
}

void BackGroundParts::setGradationHandle(int gh){
	gradationHandle = gh;
}

void BackGroundParts::setShiftVel(const Vector2 &v){
	vel = v;
}

void BackGroundParts::setAlphaBlendMode(int alpha_, int blendMode_ = DX_BLENDMODE_ALPHA){
	alpha = alpha_;
	blendMode = blendMode_;
}

//shiftu, shiftv•ªˆÚ“®
void BackGroundParts::update(){
	for (int i = 0; i < 6; i++){
		Vert[i].u += vel.x;
		Vert[i].v -= vel.y;
	}
}

void BackGroundParts::draw(){
	Draw::normal(Vector2(0, 0), gradationHandle, 255, DX_BLENDMODE_ALPHA);

	SetTextureAddressMode(DX_TEXADDRESS_WRAP);
	SetDrawBlendMode(blendMode, alpha);
	DrawPolygon2D(Vert, 2, gHandle, true);
	SetTextureAddressMode(DX_TEXADDRESS_CLAMP);
}


BackGround::BackGround(){
	add(std::make_shared<BGParts>());
}
void BackGround::add(std::shared_ptr<BGParts> ptr){
	vec.emplace_back(ptr);
}
void BackGround::update(){
	for (auto i = vec.begin(); i < vec.end(); i++){
		(**i).update();
	}
}
void BackGround::draw(){
	for (auto i = vec.begin(); i < vec.end(); i++){
		(**i).draw();
	}
}
