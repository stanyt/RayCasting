#include"pch.h"
#include"Object.h"
void Object::Intersection(const Ray& r, float& outCurrentDepth, Object*& outColliderObj) {
	//œ‡Ωª
	float deltaX, deltaY, t;
	Point2 p;
	for (int i = 0; i < edgeNum; ++i) {
		deltaX = edge[i].endPos.X - edge[i].startPos.X;
		deltaY = edge[i].endPos.Y - edge[i].startPos.Y;
		t = (deltaY * (r.startPos.X - edge[i].startPos.X) - deltaX * (r.startPos.Y - edge[i].startPos.Y)) /
			(r.direction.Y * deltaX - r.direction.X * deltaY);
		if (t < 0) continue;
		if (t >= outCurrentDepth) continue;
		p.X = r.startPos.X + r.direction.X * t;
		p.Y = r.startPos.Y + r.direction.Y * t;
		if (((p.X <= edge[i].startPos.X && p.X <= edge[i].endPos.X) || (p.X > edge[i].startPos.X && p.X > edge[i].endPos.X))
			&& ((p.Y <= edge[i].startPos.Y && p.Y <= edge[i].endPos.Y) || (p.Y > edge[i].startPos.Y && p.Y > edge[i].endPos.Y))) {
			continue;
		}
		outCurrentDepth = t;
		outColliderObj = this;
	}
}

void Circle::Intersection(const Ray& r, float& outCurrentDepth, Object*& outColliderObj) {
	float a = r.direction.X * r.direction.X + r.direction.Y * r.direction.Y;
	float b = 2 * (r.startPos.X * r.direction.X + r.startPos.Y * r.direction.Y - center.X * r.direction.X - center.Y * r.direction.Y);
	float c = r.startPos.X * r.startPos.X + r.startPos.Y * r.startPos.Y +
		center.X * center.X + center.Y * center.Y - radius * radius - 2 * (center.X * r.startPos.X + center.Y * r.startPos.Y);
	float delta = b * b - 4 * a * c;
	if (delta < 0) return;
	delta = sqrt(delta);
	float t1 = (-b - delta) / 2 * a;
	float t2 = (-b + delta) / 2 * a;
	if (t1 < 0 && t2 < 0 || t1 >= outCurrentDepth && t2 >= outCurrentDepth) {
		return;
	}
	if (t1 <= t2) {
		outCurrentDepth = t1;
	}
	else outCurrentDepth = t2;
	outColliderObj = this;
}