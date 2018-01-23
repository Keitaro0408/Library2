/**
 * @file   TaskBase.cpp
 * @brief  TaskBaseクラスの実装
 * @author kotani
 */
#include "TaskBase.h"

namespace Lib
{
	int TaskBase::m_TaskMaxNum = 0;

	TaskBase::TaskBase(int _priority) :
		m_Priority(_priority)
	{
		m_TaskMaxNum++;
	}


	TaskBase::~TaskBase()
	{
	}

}