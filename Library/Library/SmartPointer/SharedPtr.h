/**
 * @file   SharedPtr.h
 * @brief  SharedPtrクラスのヘッダファイル
 * @author kotani
 */
#ifndef SHARED_PTR_H
#define SHARED_PTR_H
#include "../Helper/Helper.h"
#include "SmartPtr.h"
#include <mutex>

template<typename Type>
class WeakPtr;

namespace Lib
{
	template<typename Type>
	/**
	 * ポインタを共有する際に仕様するスマートポインタ
	 */
	class SharedPtr : public SmartPtr<Type>
	{
		friend WeakPtr<Type>;
	public:
		SharedPtr(Type* _type);
		
		SharedPtr();

		virtual ~SharedPtr();

		/**
		 * メモリを解放する
		 */
		void Reset();

		/**
		 * メモリを解放した後に引数のポインタを扱う
		 * @param[in] _type 新しく管理するポインタ
		 */
		void Reset(Type* _type);

		SharedPtr& operator=(const SharedPtr&);

		SharedPtr& operator=(SharedPtr<Type>&& _obj)
		{
			m_pRefCount = _obj.m_pRefCount;
			m_pWeakCount = _obj.m_pWeakCount;
			++(*m_pWeakCount);
			++(*m_pRefCount);
			m_pInstance = _obj.m_pInstance;
			return *this;
		}

		Type* operator->() const;

	private:
		/**
		 * 参照カウンタ増加
		 */
		void AddRef();

		/**
		 * 参照カウンタを減少させて0なら持っている
		 * オブジェクトをdeleteする
		 */
		void Release();

		unsigned int* m_pRefCount;
		unsigned int* m_pWeakCount;

	};

	template<typename Type, class... Args>
	Type* MakeShared(Args&&... args)
	{
		return new Type(std::forward<Args>(args)...);
	}

#include "SharedPtr_private.h"

}

#endif
