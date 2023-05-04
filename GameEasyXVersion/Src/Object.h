#include"Math.h"
#include"pch.h"
class Object
{
public:
	int edgeNum;
	Line* edge;
	Object(int edgenum) :edgeNum(edgenum) {
		edge = new Line[edgeNum]();
	}
	virtual ~Object() {
		delete[]edge;
	}
	void virtual DrawSelf()=0;
	void virtual Intersection(const Ray& r, float& outCurrentDepth, Object*& outColliderObj);
};

class Rect:public Object
{
private:
	Point2 leftUp, rightDown;
public:
	Rect(Point2 lu, Point2 rd) :Object(4),leftUp(lu), rightDown(rd){
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
	inline void DrawSelf() override {
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
	void DrawSelf() override {
		fillpolygon(v, 3);
	}
};

class Circle :public Object {
	Point2 center;
	float radius;
public:
	Circle(Point2 c,float r):radius(r),center(c),Object(1){}
	void Intersection(const Ray& r, float& outCurrentDepth, Object*& outColliderObj) override;
	inline void DrawSelf() override {
		fillcircle(center.X,center.Y,radius);
	}
};

#pragma once
