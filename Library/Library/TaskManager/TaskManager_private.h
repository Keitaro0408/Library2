#ifndef TASKMANAGER_PRIVATE_H
#define TASKMANAGER_PRIVATE_H

template<class Type>
void TaskManager<Type>::AddTask(Type* _pTask)
{
	m_TaskBaseList.push_back(_pTask);
	m_TaskBaseList.sort(TaskBase::TaskCmp());
}

template<class Type>
void TaskManager<Type>::Run()
{
	m_TaskBaseList.sort(TaskBase::TaskCmp());

	for (const auto& itr : m_TaskBaseList)
	{
		itr->Run();
	}
}

template<class Type>
void TaskManager<Type>::RemoveTask(Type* _pTask)
{
	for (const auto& itr : m_TaskBaseList)
	{
		if (*itr == _task)
		{
			m_TaskBaseList.erase(itr);
			return;
		}
	}

}

template<class Type>
void TaskManager<Type>::Clear()
{
	m_TaskBaseList.clear();
}


#endif
