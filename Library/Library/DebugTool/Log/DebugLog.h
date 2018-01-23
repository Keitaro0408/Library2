#ifndef DEBUGLOG_H
#define DEBUGLOG_H
#include <stdlib.h>

class DebugLog
{
public:
	static DebugLog& Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new DebugLog();
			atexit(&Delete);
		}
	}

	static void Delete()
	{
		delete m_pInstance;
	}

private:
	DebugLog();
	~DebugLog();

	static DebugLog* m_pInstance;
};


#endif
