#ifndef _OBJECT_H_
#define _OBJECT_H_
#include"Math.h"
#include<graphics.h>
class Object
{
public:
	int edgeNum;
	Line* edge;
	Object(int edgenum) :edgeNum(edgenum) {
		edge = new Line[edgeNum]();
	}
	~Object() {
		delete[]edge;
	}
	void virtual DrawSelf()=0;
	void virtual Intersection(Ray&r,float& currentDepth, Object*& colliderObj) {
		//œ‡Ωª
		float deltaX, deltaY, t;
		Point2 p;
		for (int i = 0; i < edgeNum; ++i) {
			deltaX = edge[i].endPos.X - edge[i].startPos.X;
			deltaY = edge[i].endPos.Y - edge[i].startPos.Y;
			t = (deltaY * (r.startPos.X - edge[i].startPos.X) - deltaX * (r.startPos.Y - edge[i].startPos.Y)) /
				(r.direction.Y * deltaX - r.direction.X * deltaY);
			if (t < 0) continue;
			if (t >= currentDepth) continue;
			p.X = r.startPos.X + r.direction.X * t;
			p.Y = r.startPos.Y + r.direction.Y * t;
			if (((p.X <= edge[i].startPos.X && p.X <= edge[i].endPos.X) || (p.X > edge[i].startPos.X && p.X > edge[i].endPos.X))
				&& ((p.Y <= edge[i].startPos.Y && p.Y <= edge[i].endPos.Y) || (p.Y > edge[i].startPos.Y && p.Y > edge[i].endPos.Y))) {
				continue;
			}
			currentDepth = t;
			colliderObj = this;
		}
	}
};

class Rect:public Object
{
private:
	Point2 leftUp, rightDown;
public:
	Rect(Point2 lu, Point2 rd) :leftUp(lu), rightDown(rd),Object(4){
		edge[0].startPos = lu;
		lu.X = rd.X;
		edge[0].endPos = lu;
		edge[1].startPos = lu;
		edge[1].endPos = rd;
		edge[2].startPos = rd;
		rd.X = leftUp.X;
		edge[2].endPos = rd;
		edge[3].startPos = rd;
		lu.X = leftUp.X;
		edge[3].endPos = lu;
	}
	virtual void DrawSelf() {
		fillrectangle(leftUp.X, leftUp.Y, rightDown.X, rightDown.Y);
	}
};

class Triangle:public Object
{
private:
	POINT v[3];
public:
	Triangle(Point2 points[]):Object(3) {
		edge[0].startPos = points[0];
		edge[0].endPos = points[1];
		edge[1].startPos = points[1];
		edge[1].endPos = points[2];
		edge[2].startPos = points[2];
		edge[2].endPos = points[0];
		v[0].x = points[0].X;
		v[0].y = points[0].Y;
		v[1].x = points[1].X;
		v[1].y = points[1].Y;
		v[2].x = points[2].X;
		v[2].y = points[2].Y;
	}
	virtual void DrawSelf() {
		fillpolygon(v, 3);
	}
};

class Circle :public Object {
	Point2 center;
	float radius;
public:
	Circle(Point2 c,float r):radius(r),center(c),Object(1){}
	void virtual Intersection(Ray& r, float& currentDepth, Object*& colliderObj) {
		float a = r.direction.X* r.direction.X + r.direction.Y* r.direction.Y;
		float b = 2 * (r.startPos.X * r.direction.X + r.startPos.Y * r.direction.Y - center.X * r.direction.X - center.Y * r.direction.Y);
		float c = r.startPos.X * r.startPos.X + r.startPos.Y * r.startPos.Y +
			center.X * center.X + center.Y * center.Y - radius * radius - 2 * (center.X * r.startPos.X + center.Y * r.startPos.Y);
		float delta =  b * b - 4 * a * c ;
		if (delta < 0) return;
		delta = sqrt(delta);
		float t1 = (-b - delta) / 2 * a;
		float t2 = (-b + delta) / 2 * a;
		if (t1 < 0 && t2 < 0||t1>=currentDepth&&t2>=currentDepth) {
			return;
		}
		if (t1 <= t2) {
			currentDepth = t1;
		}
		else currentDepth = t2;
		colliderObj = this;
	}
	virtual void DrawSelf() {
		fillcircle(center.X,center.Y,radius);
	}
};

#endif //!_OBJECT_H_
#pragma once
