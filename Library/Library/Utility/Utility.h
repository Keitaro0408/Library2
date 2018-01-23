/**
 * @file   Utility.h
 * @brief  便利関数のヘッダファイル
 * @author kotani
 */
#ifndef Utility_H
#define Utility_H
#include <functional>
#include <string>
#include <windows.h>
#include <stdio.h>

/* コピー禁止マクロ */
#define NON_COPYABLE(Class) Class(const Class &); \
                        void operator=(const Class &)

#define STRING_HASH(str) std::hash<std::string>()(str)

#ifdef _DEBUG
#   define MyOutputDebugString( str, ... ) \
      { \
        TCHAR c[256]; \
        sprintf_s( c, str, __VA_ARGS__ ); \
        OutputDebugString( c ); \
      }
#else
#    define MyOutputDebugString( str, ... ) // 空実装
#endif

namespace Lib
{
	template <class Type>
	inline void SafeDelete(Type*& p)
	{
		static_assert(sizeof(Type),"incomplete type delete");
		delete p;
		p = nullptr;
	}

	template <class Type>
	inline void SafeArrayDelete(Type*& p)
	{
		static_assert(sizeof(Type), "incomplete type delete");
		delete[] p;
		p = nullptr;
	}

	template <class Type>
	inline void SafeRelease(Type*& p)
	{
		static_assert(sizeof(Type), "incomplete type delete");
		if (p != nullptr)
		{
			p->Release();
			p = nullptr;
		}
	}

	template <class Type>
	inline void SafeFinalize(Type*& p)
	{
		static_assert(sizeof(Type), "incomplete type delete");
		if (p != nullptr)
		{
			p->Finalize();
			delete p;
			p = nullptr;
		}
	}
}


#endif
