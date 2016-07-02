//--------------------------------------
//Develop Code Name "Natasha"
//by yagiri
//--------------------------------------

#include "Collision.h"

ICollision::ICollision(col_kind i_kind) :
kind(i_kind)
{
}

ColPoint::ColPoint() : ICollision(point)
{
}
ColPoint::ColPoint(Vector2 pos_) :
ICollision(point), pos(pos_)
{
}
Vector2 ColPoint::getPos(){
	return pos;
}

ColLine::ColLine() : 
ICollision(line)
{
}
ColLine::ColLine(Vector2 start_, Vector2 end_) :
ICollision(line), start(start_), end(end_)
{
}
Vector2 ColLine::getPos(){
	return (start + end) * 0.5;
}

ColCircle::ColCircle() : 
ICollision(circle)
{
}
ColCircle::ColCircle(Vector2 pos_, double radius_) :
ICollision(circle), pos(pos_), radius(radius_)
{
}
Vector2 ColCircle::getPos(){
	return pos;
}


ColBox::ColBox() : 
ICollision(box)
{
}
ColBox::ColBox(Vector2 pos_, Vector2 size_) :
ICollision(box), pos(pos_), size(size_)
{
}
Vector2 ColBox::getPos(){
	return pos;
}



bool Collsion::IsCrash(std::shared_ptr<ICollision> col1, std::shared_ptr<ICollision> col2){
	if (col1->kind > col2->kind){
		std::swap(col1, col2);
	}

	if (col1->kind == ICollision::point && col2->kind == ICollision::circle){
		auto a = std::static_pointer_cast<ColPoint>(col1);
		auto b = std::static_pointer_cast<ColCircle>(col2);
		return pow(b->pos.x - a->pos.x, 2) + pow(b->pos.y - a->pos.y, 2) < pow(b->radius, 2);
	}


	else if (col1->kind == ICollision::point && col2->kind == ICollision::box){
		auto a = std::static_pointer_cast<ColPoint>(col1);
		auto b = std::static_pointer_cast<ColBox>(col2);
		return 2 * abs(a->pos.x - b->pos.x) < b->size.x && 2 * abs(a->pos.y - b->pos.y) < b->size.y;
	}

	else if (col1->kind == ICollision::line && col2->kind == ICollision::box){
		auto a = std::static_pointer_cast<ColLine>(col1);
		auto b = std::static_pointer_cast<ColBox>(col2);
		auto check = [](double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4){
			double S, T, D;	//	一時変数を宣言

			//	分母を先に計算。計算量を減らすため、分子は後で行う。
			D = (x3 - x1) * (y4 - y1) - (y3 - y1) * (x4 - x1);

			//	D の符号に応じて分岐
			if (D < 0){
				S = (y4 - y1)*(x2 - x1) - (x4 - x1)*(y2 - y1);
				T = (x3 - x1)*(y2 - y1) - (y3 - y1)*(x2 - x1);

				return S <= 0 && T <= 0 && (S + T) / D >= 1;
			}
			else if (D > 0){
				S = (y4 - y1)*(x2 - x1) - (x4 - x1)*(y2 - y1);
				T = (x3 - x1)*(y2 - y1) - (y3 - y1)*(x2 - x1);

				return S >= 0 && T >= 0 && (S + T) / D >= 1;
			}

			//	D = 0 の時には、点が線分の上かどうかを判定する。
			return (x3 - x1)*(x4 - x1) + (y3 - y1)*(y4 - y1) <= 0
				|| (x3 - x2)*(x4 - x2) + (y3 - y2)*(y4 - y2) <= 0
				|| (x1 - x3)*(x2 - x3) + (y1 - y3)*(y2 - y3) <= 0;
		};

		Vector2 pos[4];
		pos[0].x = b->pos.x - b->size.x * 0.5;
		pos[0].y = b->pos.y - b->size.y * 0.5;
		pos[1].x = b->pos.x + b->size.x * 0.5;
		pos[1].y = b->pos.y - b->size.y * 0.5;
		pos[2].x = b->pos.x + b->size.x * 0.5;
		pos[2].y = b->pos.y + b->size.y * 0.5;
		pos[3].x = b->pos.x - b->size.x * 0.5;
		pos[3].y = b->pos.y + b->size.y * 0.5;

		return false
			|| check(a->start.x, a->start.y, a->end.x, a->end.y, pos[0].x, pos[0].y, pos[1].x, pos[1].y)
			|| check(a->start.x, a->start.y, a->end.x, a->end.y, pos[1].x, pos[1].y, pos[2].x, pos[2].y)
			|| check(a->start.x, a->start.y, a->end.x, a->end.y, pos[2].x, pos[2].y, pos[3].x, pos[3].y)
			|| check(a->start.x, a->start.y, a->end.x, a->end.y, pos[3].x, pos[3].y, pos[0].x, pos[0].y);
	}


	else if (col1->kind == ICollision::line && col2->kind == ICollision::line){
		auto a = std::static_pointer_cast<ColLine>(col1);
		auto b = std::static_pointer_cast<ColLine>(col2);

		double x1 = a->start.x;
		double y1 = a->start.y;
		double x2 = a->end.x;
		double y2 = a->end.y;
		double x3 = b->start.x;
		double y3 = b->start.y;
		double x4 = b->end.x;
		double y4 = b->end.y;
		double S, T, D;	//	一時変数を宣言

		//	分母を先に計算。計算量を減らすため、分子は後で行う。
		D = (x3 - x1) * (y4 - y1) - (y3 - y1) * (x4 - x1);

		//	D の符号に応じて分岐
		if (D < 0){
			S = (y4 - y1)*(x2 - x1) - (x4 - x1)*(y2 - y1);
			T = (x3 - x1)*(y2 - y1) - (y3 - y1)*(x2 - x1);

			return S <= 0 && T <= 0 && (S + T) / D >= 1;
		}
		else if (D > 0){
			S = (y4 - y1)*(x2 - x1) - (x4 - x1)*(y2 - y1);
			T = (x3 - x1)*(y2 - y1) - (y3 - y1)*(x2 - x1);

			return S >= 0 && T >= 0 && (S + T) / D >= 1;
		}

		//	D = 0 の時には、点が線分の上かどうかを判定する。
		return (x3 - x1)*(x4 - x1) + (y3 - y1)*(y4 - y1) <= 0
			|| (x3 - x2)*(x4 - x2) + (y3 - y2)*(y4 - y2) <= 0
			|| (x1 - x3)*(x2 - x3) + (y1 - y3)*(y2 - y3) <= 0;
	}


	else if (col1->kind == ICollision::line && col2->kind == ICollision::circle){
		auto a = std::static_pointer_cast<ColLine>(col1);
		auto b = std::static_pointer_cast<ColCircle>(col2);


		if (Func::distSqr(a->start.x, a->start.y, b->pos.x, b->pos.y) < b->radius*b->radius
			|| Func::distSqr(a->end.x, a->end.y, b->pos.x, b->pos.y) < b->radius*b->radius){
			return true;
		}
		else {
			double k = a->end.y - a->start.y;
			double l = a->end.x - a->start.x;
			if (!((k*b->pos.x - l*b->pos.y - k*a->start.x + l*a->start.y)*(k*b->pos.x - l*b->pos.y - k*a->start.x + l*a->start.y) < b->radius * b->radius * (k*k + l*l))){
				return false;
			}
			if (((a->start.x - b->pos.x)*(a->end.x - b->pos.x) + (a->start.y - b->pos.y)*(a->end.y - b->pos.y)) < 0){
				return true;
			}
		}
		return false;

		return Func::CircleAndLine(b->pos.x, b->pos.y, b->radius,
			a->start.x, a->start.y,
			a->end.x, a->end.y);
	}


	else if (col1->kind == ICollision::circle && col2->kind == ICollision::circle){
		auto a = std::static_pointer_cast<ColCircle>(col1);
		auto b = std::static_pointer_cast<ColCircle>(col2);
		return pow(b->pos.x - a->pos.x, 2) + pow(b->pos.y - a->pos.y, 2) < pow(a->radius + b->radius, 2);
	}

	else if (col1->kind == ICollision::circle && col2->kind == ICollision::box){
		auto a = std::static_pointer_cast<ColCircle>(col1);
		auto b = std::static_pointer_cast<ColBox>(col2);

		double xc = a->pos.x;
		double yc = a->pos.y;
		double r = a->radius;
		double x1 = b->pos.x - b->size.x * 0.5;
		double y1 = b->pos.y - b->size.y * 0.5;
		double x2 = b->pos.x + b->size.x * 0.5;
		double y2 = b->pos.y + b->size.y * 0.5;

		if ((xc > x1) && (xc < x2) && (yc > y1 - r) && (yc < y2 + r)){
			return true;
		}
		else if ((xc > x1 - r) && (xc < x2 + r) && (yc > y1) && (yc < y2)){
			return true;
		}
		else if (pow(x1 - xc, 2) + pow(y1 - yc, 2) < pow(r, 2)){
			return true;
		}
		else if (pow(x2 - xc, 2) + pow(y1 - yc, 2) < pow(r, 2)){
			return true;
		}
		else if (pow(x1 - xc, 2) + pow(y2 - yc, 2) < pow(r, 2)){
			return true;
		}
		else if (pow(x2 - xc, 2) + pow(y2 - yc, 2) < pow(r, 2)){
			return true;
		}
		return false;
	}

	else if (col1->kind == ICollision::box && col2->kind == ICollision::box){
		auto a = std::static_pointer_cast<ColBox>(col1);
		auto b = std::static_pointer_cast<ColBox>(col2);
		return 2 * abs(a->pos.x - b->pos.x) < (a->size.x + b->size.x)
			&& 2 * abs(a->pos.y - b->pos.y) < (a->size.y + b->size.y);
	}

	return false;
}


void Collsion::draw(std::shared_ptr<ICollision> col, int color){

	int alpha = 128;

	if (false){
	}
	else if (col->kind == ICollision::point){
		auto ptr = std::static_pointer_cast<ColPoint>(col);
		Draw::circle(ptr->pos, 4, color, alpha);
	}
	else if (col->kind == ICollision::line){
		auto ptr = std::static_pointer_cast<ColLine>(col);
		Draw::line(ptr->start, ptr->end, color, alpha);
	}
	else if (col->kind == ICollision::circle){
		auto ptr = std::static_pointer_cast<ColCircle>(col);
		Draw::circle(ptr->pos, ptr->radius, color, alpha);
	}
	else if (col->kind == ICollision::box){
		auto ptr = std::static_pointer_cast<ColBox>(col);
		Draw::centerbox(ptr->pos, ptr->size, color, alpha);
	}
}



std::shared_ptr<ICollision> Collsion::testCol(){
	return std::make_shared<ColLine>(Input::mousePos(), Input::mousePos() + Vector2::GetPolar(50, Input::eframe()*0.01));
	//return std::make_shared<ColCircle>(Input::mousePos(), 12);

}

void Collsion::testColDraw(){
	draw(testCol(), 0x888888);
}





