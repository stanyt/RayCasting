#include<graphics.h>
#include<string>
#include <conio.h>

#include"Player.h"

int width = 900, height = 800;
void DrawObjs(Object** objs,int objsNum) {
	
	setfillcolor(RGB(249, 139, 24));
	//物体
	for (int i = 0; i < objsNum; ++i) {
		objs[i]->DrawSelf();
	}
}
void Draw(Player& player, Object** objs, int objsNum) {
	player.DrawRay();
	player.DrawSelf();
	DrawObjs(objs, objsNum);
}
#define BKCOLOR RGB(155, 255, 255)
int main(void) {
	int t;
	RECT r = { 0,0,40,20 };
	std::string dirStr;
	Player m_player(Point2(70,70));

	int map = 150;

	initgraph(width, height);
	//墙
	Rect wall1(Point2(map, 0), Point2(map + 5, map));
	Rect wall2(Point2(0, map), Point2(map, map + 5));
	Rect wall3(Point2(0, 5), Point2(5, map));
	Rect wall4(Point2(5, 0), Point2(map, 5));
	Rect cube1(Point2(100, 110), Point2(90, 120));
	Rect cube2(Point2(10, 10), Point2(20, 20));
	Point2 points[3] = { Point2(40,30),Point2(50,60),Point2(40,60) };
	Triangle tri(points);

	Circle c(Point2(100, 100), 5);

	cleardevice();
	const int objNum = 8;
	Object** objs = new Object*[objNum];
	objs[0] = &wall1;
	objs[1] = &wall2;
	objs[2] = &cube1;
	objs[3] = &tri;
	objs[4] = &wall3;
	objs[5] = &wall4;
	objs[6] = &cube2;
	objs[7] = &c;
	float f = 60;
	float deltaTimeM = 1000 / f;
	float deltaTime = 1000 / f / 1000;

	m_player.lastMousePos.X = getmessage().x;
	m_player.lastMousePos.Y = getmessage().y;
	while (true)//游戏循环Loop
	{
		Sleep(deltaTimeM);
		cleardevice();
		m_player.Movement(dirStr, deltaTime);
		m_player.Rotation(deltaTime);
		BeginBatchDraw();//缓存画面

		m_player.CalculateRay(objs, objNum);
		m_player.RenderScene(width * 0.5f, height * 0.5f);
		setfillcolor(BKCOLOR);
		fillrectangle(0, 0, map, map);
		settextcolor(RGB(111, 222, 147));//设置字体颜色
		drawtext(dirStr.c_str(), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		Draw(m_player, objs, objNum);
		FlushBatchDraw();//释放画面
	}
	closegraph();
	return 0;
}