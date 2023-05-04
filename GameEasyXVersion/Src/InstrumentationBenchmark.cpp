#include "pch.h"
#include "InstrumentationBenchmark.h"
/// <summary>
/// "name": "��Ϣ",  // �¼�������չʾ�� timeline ��
///"cat": "����",  // �¼����࣬���� Tag������ѡ��һ���¼���ʱ�����·�ѡ�����ʾ
///"ph" : "X", // phase,���õ���B / E / X / M���ֱ��ʾbegin /end / complete / metadata event
///"ts" : 0,  //�¼� ��ʼ������ʱ�̵�
///"pid" : 0,  // process id
///"tid" : 1, // thread id
///"dur" : 28800000000, // duration���� phase X ����ʹ�ã���ʾ�¼��ĳ���ʱ��
///"args" : {"duration_hour": 8, "start_hour" : 0}} // ���Ӳ�������ѡ��һ���¼���ʱ�����·�ѡ�����ʾ
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
/// Jsonͷ
/// {"displayTimeUnit": "ms", "traceEvents":[
/// </summary>
void Instrumentation::Instrumentor::StartSession(const char* fileName)
{
	m_foutStream.open(fileName, std::ios_base::out);
	m_foutStream<<"{\"displayTimeUnit\":\"ms\",\"traceEvents\":[";
	m_foutStream.flush();
}
/// <summary>
/// Jsonβ
/// ]}
/// </summary>
void Instrumentation::Instrumentor::EndSession()
{
	m_foutStream << "\n]}";
	m_foutStream.flush();
	m_foutStream.close();
}
