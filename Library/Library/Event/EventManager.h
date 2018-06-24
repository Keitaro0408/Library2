/**
 * @file   EventManager.h
 * @brief  EventManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <list>
#include <unordered_map>
#include <functional>
#include <Windows.h>
#include "..\Singleton\Singleton.h"
#include "Event.h"
#include "IEventListener.h"

namespace Lib
{
	/**
	 * コールバックのイベントを管理する
	 */
	class EventManager
	{
		friend Singleton<EventManager>;
	public:
		/**
		 * イベントの追加
		 * @param[in] _pEventListnerBaseList イベント待受クラス
		 * @param[in] _category 登録するイベントのカテゴリ
		 */
		void AddListener(IEventListener* _pIEventListener, LPSTR _category);

		/**
		 * イベントを送信する
		 * @param[in] _pEvent イベントクラス
		 * @param[in] _category 送信するイベントのカテゴリ
		 */
		void SendEvent(Event& _pEvent, LPSTR _category);

		/**
		 * 登録されている全てのイベントをリストから削除する
		 */
		void AllEventClear();

	private:
		EventManager(){};
		~EventManager(){};

		std::unordered_map<std::string, std::list<IEventListener*>> m_pEventListener;
		 
	};
}


#endif
