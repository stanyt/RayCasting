#include "pch.h"
#include "InstrumentationBenchmark.h"
/// <summary>
/// "name": "休息",  // 事件名，会展示在 timeline 上
///"cat": "测试",  // 事件分类，类似 Tag，会在选中一个事件的时候，在下方选项卡中显示
///"ph" : "X", // phase,常用的有B / E / X / M，分别表示begin /end / complete / metadata event
///"ts" : 0,  //事件 开始发生的时刻点
///"pid" : 0,  // process id
///"tid" : 1, // thread id
///"dur" : 28800000000, // duration，跟 phase X 搭配使用，表示事件的持续时间
///"args" : {"duration_hour": 8, "start_hour" : 0}} // 附加参数，在选中一个事件的时候，在下方选项卡中显示
/// </summary>
void Instrumentation::Instrumentor::WriteProfile(const Profile& profile)
{
	if (profileSize++ > 0) {
		m_foutStream << ",";
	}
	m_foutStream << "\n{\n\"name\":\"" << profile.name<<"\",\n";
	m_foutStream << "\"cat\":\"" << "Test"<<"\",\n";
	m_foutStream << "\"ph\":\"" << "X"<<"\",\n";
	m_foutStream << "\"ts\":" << profile.start<<",\n";
	m_foutStream << "\"pid\":" << 0<<",\n";
	m_foutStream << "\"tid\":" << 0<<",\n";
	m_foutStream << "\"dur\":" << profile.duration<<",\n";
	m_foutStream << "\"args\":{\"endts\":" << profile.start + profile.duration << " }\n}";
	m_foutStream.flush();
}

/// <summary>
/// Json头
/// {"displayTimeUnit": "ms", "traceEvents":[
/// </summary>
void Instrumentation::Instrumentor::StartSession(const char* fileName)
{
	m_foutStream.open(fileName, std::ios_base::out);
	m_foutStream<<"{\"displayTimeUnit\":\"ms\",\"traceEvents\":[";
	m_foutStream.flush();
}
/// <summary>
/// Json尾
/// ]}
/// </summary>
void Instrumentation::Instrumentor::EndSession()
{
	m_foutStream << "\n]}";
	m_foutStream.flush();
	m_foutStream.close();
}
