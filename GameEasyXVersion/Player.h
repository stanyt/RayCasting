#ifndef _PLAYER_H_
#define _PLAYER_H_
#include<string>
#include"Math.h"
#include"Object.h"
#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1:0)
class Player
{
public:
	Player(Point2 pos, Vector2 forward = Vector2(0, -1));
	~Player();

private:
	const float fieldAngle = 60;
	const float rayMaxDepth = 300;
	static const int sampleNum = 200;
	float rayDepths[Player::sampleNum + 1];
	Ray rays[Player::sampleNum + 1];
	Object* hitInfo[Player::sampleNum + 1];
	float m_speed, m_radius,m_rotateSpeed;
	float m_sampleAngle;
	Point2 m_pos;
	Vector2 m_forward;
	float closeDepth = 20;
public:
	Point2 lastMousePos;
public:
	void Movement(std::string& dir, float deltaTime);
	void Rotation(float deltaTime);
	void DrawSelf();
	void DrawRay();
	void CalculateRay(Object** objs, int objsNum);
	void RenderScene(float width , float height);
};


#endif // !_PLAYER_H_

#pragma once
