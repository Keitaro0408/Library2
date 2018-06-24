/**
 * @file   EventManager.cpp
 * @brief  EventManagerクラスの実装
 * @author kotani
 */
#include "EventManager.h"
#include "Event.h"

namespace Lib
{
//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

	void EventManager::AddListener(IEventListener* _pEventListnerBaseList, LPSTR _category)
	{
		m_pEventListener[_category].push_back(_pEventListnerBaseList);
	}
	
	void EventManager::SendEvent(Event& _pEvent, LPSTR _category)
	{
		for (const auto& itr : m_pEventListener[_category])
		{
			itr->OnEvent(_pEvent);
		}
	}

	void EventManager::AllEventClear()
	{
		m_pEventListener.clear();
	}
}
