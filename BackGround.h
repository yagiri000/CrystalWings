#pragma once
#include <vector>

#include "Abstract.h"
#include "Vector2.h"
#include "Collision.h"



class BackGroundParts
{
public:
	BackGroundParts();

	VERTEX2D Vert[6];
	int gHandle;
	int gradationHandle;
	Vector2 vel;
	Vector2 basePos;
	int alpha;
	int blendMode;

	void init();
	void setGraphHandle(int gh);
	void setGradationHandle(int gh);
	void setShiftVel(const Vector2 &v);
	void setAlphaBlendMode(int Alpha, int BlendMode);

	virtual void update();
	virtual void draw();
};

using BGParts = BackGroundParts;

class BackGround
{
public:
	BackGround();

	std::vector<std::shared_ptr<BGParts>> vec;

	void add(std::shared_ptr<BGParts> ptr);
	void update();
	void draw();
};
