/**
 * @file   EventManager.cpp
 * @brief  EventManagerクラスの実装
 * @author kotani
 */
#include "EventManager.h"
#include "Event.h"
#include "EventListenerBase.h"

namespace Lib
{
//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

	void EventManager::AddListener(EventListenerBase* _pEventListnerBaseList, LPSTR _category)
	{
		m_pEventListenerBase[_category].push_back(_pEventListnerBaseList);
	}
	
	void EventManager::SendEvent(Event& _pEvent, LPSTR _category)
	{
		for (auto itr : m_pEventListenerBase[_category])
		{
			itr->OnEvent(_pEvent);
		}
	}

	void EventManager::AddEventList(Event* _pEvent)
	{
		m_pEventList.push_back(*_pEvent);
	}

	void EventManager::Execute(LPSTR _category)
	{
		std::list<Event>::iterator eventItr = m_pEventList.begin();

		for (auto itr : m_pEventList)
		{
			for (auto itr2 : m_pEventListenerBase[_category])
			{
				itr2->OnEvent(itr);
			}
		}
		m_pEventList.clear();
	}

	void EventManager::AllEventClear()
	{
		m_pEventListenerBase.clear();
	}
}
