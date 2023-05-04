#pragma once
#include"pch.h"

#define Benchmark 1
#define BenchmarkLogConsole 0
#define BenchmarkVisualization 1

#if Benchmark
#if BenchmarkVisualization
#define Benchmark() Instrumentation::InstrumentationTimer timer##__LINE__(__FUNCSIG__);
#else
#define Benchmark() 
#endif
namespace Instrumentation {
	struct Profile {
		const char* name;
		long long start;
		long long duration;
	};
	class Instrumentor {
	private:
		std::ofstream m_foutStream;
		unsigned profileSize;
	public:
		Instrumentor():profileSize(0){}
		void WriteProfile(const Profile& profile);
		void StartSession(const char* fileName = "result.json");
		void EndSession();
		inline static Instrumentor& GetIns() {
			static Instrumentor instance;
			return instance;
		}
	};
	struct InstrumentationTimer {
		const char* m_timerName;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint;
		bool logSec;
		InstrumentationTimer(const char* name) :m_timerName(name) {
			logSec = false;
			m_startTimePoint = std::chrono::high_resolution_clock::now();
		}
		~InstrumentationTimer() {
			auto endTimePoint = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTimePoint - m_startTimePoint).count();
#if BenchmarkLogConsole
			std::cout << m_timerName << " duration: " << duration << " us (" << duration * 0.001f << ") ms\n";
			if (logSec) {
				Log(m_timerName << " duration: " << duration * 0.000001 << " s");
			}
#endif
#if BenchmarkVisualization
			Instrumentor::GetIns().WriteProfile(
					{m_timerName,std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count(),duration});
#endif
		}
	};
}
#endif
