#ifndef _MATH_H_
#define _MATH_H_
#include"pch.h"
const float PI = 3.1415926535;
struct Vector2 {
	float X; float Y;
	Vector2(float x=1,float y=0):X(x),Y(y){}
	Vector2 Rotate(float angle) {
		Vector2 res;
		res.X = X * cos(angle * PI / 180) - Y * sin(angle * PI / 180);
		res.Y = X * sin(angle * PI / 180) + Y * cos(angle * PI / 180);
		return res;
	}
	Vector2 operator*(float x) {
		return Vector2(X * x, Y * x);
	}
	Vector2 operator/(float x) {
		return Vector2(X / x, Y / x);
	}
	static float Dot(Vector2 a, Vector2 b);
	static float CosAngle(Vector2 a, Vector2 b);
};
struct Point2 {
	float X; float Y;
	Point2(float x=0, float y=0) :X(x), Y(y) {}
	Point2 operator*(float x) {
		return Point2(X*x,Y*x);
	}
	void operator+=(const Vector2& v) {
		X += v.X;
		Y += v.Y;
	}
	void operator-=(const Vector2& v) {
		X -= v.X;
		Y -= v.Y;
	}
	Vector2 operator-(Point2 p) const {
		return Vector2(X - p.X, Y - p.Y);
	}
	Point2 operator+(Vector2 d) const {
		return Point2(X + d.X, Y + d.Y);
	}
	POINT GETPOINT() {
		POINT p;
		p.x = X;
		p.y = Y;
		return p;
	}
};
struct Ray
{
	Point2 startPos;
	Vector2 direction;
	Ray(Point2& pos, Vector2& dir) :startPos(pos), direction(dir) {}
	Ray() :startPos(), direction() {}
};
struct Line {
	Point2 startPos;
	Point2 endPos;
	Line(Point2& start, Point2& end) :startPos(start), endPos(end) {}
	Line() :startPos(), endPos() {}
};
float manugite(Point2 p);
float manugite(Vector2 v);
Point2 Normalize(Point2& p);
#endif // !_MATH_H_

#pragma once
