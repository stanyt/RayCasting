#include"pch.h"
#include"Game.h"
namespace GameFramework{
	void Game::OnUpdate()
	{
		Benchmark()
	
		while (true)//游戏循环Loop
		{
			if (KEY_DOWN(Esc)) {
				break;
			}
			Sleep(deltaTimeM);
			cleardevice();
			m_player.Movement(dirStr, deltaTime);
			m_player.Rotation(deltaTime);

			BeginBatchDraw();//缓存画面

			m_player.CalculateRay(objs, objNum);
			m_player.RenderScene(m_windowWidth * 0.5f, m_windowHeight * 0.5f);
			setfillcolor(BKCOLOR);
			fillrectangle(0, 0, mapWidth, mapWidth);
			settextcolor(FONTCOLOR);//设置字体颜色
			sprintf_s(dir, "%.*s", dirStr.size(), dirStr.data());
			drawtext(dir, &textr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			Draw(m_player, objs, objNum);
			FlushBatchDraw();//释放画面
		}
	}

	void Game::OnStart()
	{
		Benchmark()
		Rect *wall1=new Rect(Point2(mapWidth, 0), Point2(mapWidth + 5, mapWidth));
		Rect *wall2=new Rect(Point2(0, mapWidth), Point2(mapWidth, mapWidth + 5));
		Rect *wall3=new Rect(Point2(0, 5), Point2(5, mapWidth));
		Rect *wall4=new Rect(Point2(5, 0), Point2(mapWidth, 5));
		Rect *cube1=new Rect(Point2(100, 110), Point2(90, 120));
		Rect *cube2=new Rect(Point2(10, 10), Point2(20, 20));
		Point2 points[3] = { Point2(40,30),Point2(50,60),Point2(40,60) };
		Triangle* tri=new Triangle(points);
		Circle *c =new Circle(Point2(100, 100), 5);

		objs[0] = wall1;
		objs[1] = wall2;
		objs[2] = cube1;
		objs[3] = tri;
		objs[4] = wall3;
		objs[5] = wall4;
		objs[6] = cube2;
		objs[7] = c;
		m_player.lastMousePos.X = getmessage().x;
		m_player.lastMousePos.Y = getmessage().y;
	}

	void Game::OnAwake()
	{
		Benchmark()
		cleardevice();
	}

	void Game::OnDestroy()
	{
		Benchmark()
		delete[]objs;
	}
}