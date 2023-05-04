#include"pch.h"
#include"Math.h"
float manugite(Point2 p) {
	return sqrt(p.X * p.X + p.Y * p.Y);
}
float manugite(Vector2 v) {
	return sqrt(v.X * v.X + v.Y * v.Y);
}
Point2 Normalize(Point2& p) {
	return Point2(p.X / manugite(p), p.Y / manugite(p));
}

float Vector2::Dot(Vector2 a, Vector2 b) {
	return a.X * b.X + a.Y * b.Y;
}
float Vector2::CosAngle(Vector2 a, Vector2 b) {
	return Dot(a, b) / (manugite(a) * manugite(b));
}