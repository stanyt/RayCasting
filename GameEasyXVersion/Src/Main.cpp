#include"pch.h"
#include"Player.h"
#include"InstrumentationBenchmark.h"
#include"Game.h"

int main(void) {
	Instrumentation::Instrumentor::GetIns().StartSession();
	Benchmark()
	GameFramework::Game::GetIns().OnAwake();
	GameFramework::Game::GetIns().OnStart();
	GameFramework::Game::GetIns().OnUpdate();
	GameFramework::Game::GetIns().OnDestroy();
	Instrumentation::Instrumentor::GetIns().EndSession();
	return 0;
}