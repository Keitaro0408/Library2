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
#include "EventListenerBase.h"

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
		void AddListener(EventListenerBase* _pEventListenerBaseList, LPSTR _category);

		/**
		 * イベントを送信する
		 * @param[in] _pEvent イベントクラス
		 * @param[in] _category 送信するイベントのカテゴリ
		 */
		void SendEvent(Event& _pEvent, LPSTR _category);

		/**
		 * リストにイベントを追加する
		 * @param[in] _pEvent イベントクラス
		 */
		void AddEventList(Event* _pEvent);

		/**
		 * リストに登録しているイベントを実行して、リストを削除する。
		 * @param[in] _category 実行するイベントのカテゴリ
		 */
		void Execute(LPSTR _category);

		/**
		 * 登録されている全てのイベントをリストから削除する
		 */
		void AllEventClear();

	private:
		EventManager(){};
		~EventManager(){};

		std::unordered_map<char*, std::list<EventListenerBase*>> m_pEventListenerBase;
		 
		std::list<Event>			  m_pEventList;
	};
}


#endif
