/**
 * @file   TaskManager.h
 * @brief  TaskManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <string>
#include <list>
#include <functional>
#include <algorithm>

#include "..\Singleton\Singleton.h"
#include "TaskBase\TaskBase.h"

namespace Lib
{
	/**
	 * タスクの管理クラス
	 */
	template<class Type>
	class TaskManager
	{
		friend Singleton<TaskManager>;
	public:
		/**
		 * タスクの追加
		 * @param[in] _pTask 追加するタスク
		 */
		void AddTask(Type* _pTask);

		/**
		 * タスクの削除
		 * @param[in] _pTask 削除するタスク
		 */
		void RemoveTask(Type* _pTask);

		/*** 登録しているタスクをに実行する */
		void Run();

		/*** 全てのタスクを削除する */
		void Clear();

	private:
		TaskManager() = default;
		~TaskManager() = default;

		std::list<Type*> m_TaskBaseList;
	};

#include "TaskManager_private.h"
}


#endif
