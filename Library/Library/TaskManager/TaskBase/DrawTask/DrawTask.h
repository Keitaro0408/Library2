/**
 * @file   DrawTask.h
 * @brief  DrawTaskクラスのヘッダファイル
 * @author kotani
 */
#ifndef DRAWTASK_H
#define DRAWTASK_H

#include "../TaskBase.h"
#include "..\..\TaskManager.h"

namespace Lib
{
	/**
	 * 描画処理のタスククラス
	 */
	class DrawTask : public TaskBase
	{
	public:
		/**
		 * コンストラクタ
		 * @param[in] _priority 優先レベル
		 */
		DrawTask(int _priority = 0) :
			TaskBase(_priority)
		{}

		/**
		 * デストラクタ
		 */
		virtual ~DrawTask(){};

		/**
		 * 実行
		 */
		void Run() override
		{
			m_pObject->Draw();
		}

	};

	using DrawTaskTaskManager = TaskManager<DrawTask>;
}


#endif
