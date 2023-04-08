#include"Player.h"
#include<graphics.h>
Player::Player(Point2 pos, Vector2 forward) :m_forward(forward),m_pos(pos)
{
	m_speed = 60, m_radius = 5, m_rotateSpeed=30;
	m_sampleAngle = fieldAngle / sampleNum;
}
Player::~Player()
{
}
void Player::Movement(std::string& dir,float deltaTime)
{
	if (KEY_DOWN('W')) {
		m_pos += m_forward * m_speed* deltaTime; dir = "up";
	}
	if (KEY_DOWN('S')) {
		m_pos -= m_forward * m_speed* deltaTime; dir = "down";
	}
	if (KEY_DOWN('A')) {
		m_pos -= m_forward.Rotate(90) * m_speed* deltaTime; dir = "left";
	}
	if (KEY_DOWN('D')) {
		m_pos += m_forward.Rotate(90) * m_speed* deltaTime; dir = "right";
	}
}
void Player::CalculateRay(Object** objs, int objsNum)
{
	float sina = sin(m_sampleAngle * PI / 180), cosa = cos(m_sampleAngle * PI / 180);
	//方向采样
	rayDepths[0] = rayMaxDepth;
	rays[0].direction.X = m_forward.X * cos(-fieldAngle * 0.5f * PI / 180) - m_forward.Y * sin(-fieldAngle * 0.5f * PI / 180);
	rays[0].direction.Y = m_forward.X * sin(-fieldAngle * 0.5f * PI / 180) + m_forward.Y * cos(-fieldAngle * 0.5f * PI / 180);
	for (int i = 1; i < sampleNum + 1; ++i) {
		rayDepths[i] = rayMaxDepth;
		rays[i].direction.X = rays[i - 1].direction.X * cosa - rays[i - 1].direction.Y * sina;
		rays[i].direction.Y = rays[i - 1].direction.X * sina + rays[i - 1].direction.Y * cosa;
	}
	for (size_t i = 0; i < sampleNum+1; ++i)
	{
		rays[i].startPos = m_pos;
		for (size_t j = 0; j < objsNum; ++j) {
			objs[j]->Intersection(rays[i], rayDepths[i], hitInfo[i]);
		}
		if (rayDepths[i] >= rayMaxDepth) {
			hitInfo[i] = nullptr;
			continue;
		}
	}
}

void Player::Rotation(float deltaTime)
{
	POINT curPoint;
	GetCursorPos(&curPoint);
	float rotate = manugite(Vector2(curPoint.x - lastMousePos.X, curPoint.y - lastMousePos.Y));
	if (curPoint.x < lastMousePos.X) {
		m_forward = m_forward.Rotate(-rotate* deltaTime* m_rotateSpeed);
	}
	else if (curPoint.x > lastMousePos.X)
	{
		m_forward = m_forward.Rotate(rotate* deltaTime* m_rotateSpeed);
	}
	lastMousePos.X = curPoint.x;
	lastMousePos.Y = curPoint.y;
}

void Player::RenderScene(float centerX,float centerY)
{
	float dx = centerX * 2 / sampleNum;
	float h0 = centerY * 2 * closeDepth / rayDepths[0];
	float h1;
	POINT points[4];
	float lightRange=150;
	float gray,dc=255/ lightRange;

	for (int i = 1; i < sampleNum + 1; ++i) {
		gray = dc * (lightRange - rayDepths[i]);
		h1 = centerY * 2 * closeDepth / rayDepths[i];
		if (h0 == 0||h1==0) {
			h0 = h1;
			continue;
		}
		if (hitInfo[i] != hitInfo[i - 1]) {
			h0 = h1;
		}
		if (gray > 255) gray = 255;
		if (gray < 0) gray = 0;
		setcolor(RGB(gray, gray, gray));
		setfillcolor(RGB(gray, gray, gray));
		points[0].x = (i - 1) * dx;
		points[0].y = centerY - h0 * 0.5f;
		points[1].x = i * dx;
		points[1].y = centerY - h1 * 0.5f;
		points[2].x = i * dx;
		points[2].y = centerY + h1 * 0.5f;
		points[3].x = (i - 1) * dx;
		points[3].y = centerY + h0 * 0.5f;

		fillpolygon(points, 4);
		h0 = h1;
	}
}

void Player::DrawSelf() {
	setfillcolor(RED);
	//主角
	fillcircle(m_pos.X, m_pos.Y, m_radius);
	circle(m_pos.X, m_pos.Y, closeDepth);
}

void Player::DrawRay() {
	POINT points[3];
	points[0] = m_pos.GETPOINT();
	line(m_pos.X, m_pos.Y, m_pos.X + rays[0].direction.X * rayDepths[0],
			m_pos.Y + rays[0].direction.Y * rayDepths[0]);
	line(m_pos.X, m_pos.Y, m_pos.X + rays[sampleNum].direction.X * rayDepths[sampleNum],
				m_pos.Y + rays[sampleNum].direction.Y * rayDepths[sampleNum]);
	for (size_t i = 1; i < sampleNum + 1; ++i)
	{
		line(m_pos.X + rays[i - 1].direction.X * rayDepths[i - 1],
			m_pos.Y + rays[i - 1].direction.Y * rayDepths[i - 1],
			m_pos.X + rays[i].direction.X * rayDepths[i],
			m_pos.Y + rays[i].direction.Y * rayDepths[i]);
		setfillcolor(RGB(237, 175, 173));
		setcolor(RGB(237, 175, 173));
		points[1] = (m_pos + rays[i - 1].direction * rayDepths[i - 1]).GETPOINT();
		points[2] = (m_pos + rays[i].direction * rayDepths[i]).GETPOINT();
		fillpolygon(points, 3);
	}
}
