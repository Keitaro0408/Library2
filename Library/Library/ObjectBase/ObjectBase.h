/**
 * @file   ObjectBase.h
 * @brief  ObjectBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H
#include "..\stdafx.h"

namespace Lib
{
	class UpdateTask;
	class DrawTask;

	/*** タスクの実行等に使用されるオブジェクトの基底クラス */
	class ObjectBase
	{
	public:
		ObjectBase() = default;

		virtual ~ObjectBase() = default;

		/*** 更新処理 */
		virtual void Update() = 0;

		/*** 描画処理 */
		virtual void Draw() = 0;

	protected:
		UpdateTask* m_pUpdateTask;
		DrawTask*   m_pDrawTask;

	};
}


#endif
