/**
 * @file   Event.h
 * @brief  Eventクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include <unordered_map>
#include "../Utility/Utility.h"

namespace Lib
{
	struct Event
	{
		Event(char* _eventName)
		{
			eventName = _eventName;
		}

		union Data
		{
			int   m_Int;
			float m_Float;
			bool  m_Bool;
		};

		std::unordered_map<std::string, Data> eventData; //!< 格納されているデータ
		std::string eventName; //!< イベントの名前
	};
}


#endif
