#pragma once
#include"pch.h"
#include"Object.h"
#include"Player.h"
#include"InstrumentationBenchmark.h"
#define BKCOLOR RGB(155, 255, 255)
#define FONTCOLOR RGB(111, 222, 147)
#define Esc 27
namespace GameFramework{
	inline void DrawObjs(Object** objs, int objsNum) {

		setfillcolor(RGB(249, 139, 24));
		//ŒÔÃÂ
		for (int i = 0; i < objsNum; ++i) {
			objs[i]->DrawSelf();
		}
	}
	inline void Draw(Player& player, Object** objs, int objsNum) {
		player.DrawRay();
		player.DrawSelf();
		DrawObjs(objs, objsNum);
	}
	class Game
	{
	private:
		int m_windowWidth,m_windowHeight;

	public:
		Game(int width = 900, int height = 800):m_windowHeight(height),m_windowWidth(width),m_player(Point2(70, 70)) ,
		objs(new Object * [objNum]),textr({ m_windowWidth - 40,m_windowHeight - 20,m_windowWidth,m_windowHeight })
		{
			Benchmark()
			initgraph(m_windowWidth, m_windowHeight, SHOWCONSOLE);
		}
		~Game() {
			Benchmark()
			closegraph();
		}
		inline static Game& GetIns() {
			static Game game;
			return game;
		}

	public:
		void OnUpdate();
		void OnStart();
		void OnAwake();
		void OnDestroy();

	private:
		// Ù–‘
		Player m_player;
		const int objNum = 8;
		Object** objs;
		const int mapWidth = 150;
		RECT textr;
		std::string_view dirStr;
		char dir[8];
		const float f = 60;
		const float deltaTimeM = 1000 / f;
		const float deltaTime = 1000 / f * 0.001f;
	};
}