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
	m_TaskBaseList.erase(
		std::remove(m_TaskBaseList.begin(), m_TaskBaseList.end(), _pTask),
		m_TaskBaseList.end());
}

template<class Type>
void TaskManager<Type>::Clear()
{
	m_TaskBaseList.clear();
}


#endif
