/**
 * @file   IEventListener.h
 * @brief  IEventListenerクラスのヘッダファイル
 * @author kotani
 */
#ifndef IEVENT_LISTENER
#define IEVENT_LISTENER
#include "Event.h"
#include "../Utility/Utility.h"

namespace Lib
{
	interface IEventListener
	{
		IEventListener(){}
		virtual ~IEventListener(){}

		virtual void OnEvent(const Event& _event) = 0;

	};
}
#endif