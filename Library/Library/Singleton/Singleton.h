﻿/**
 * @file   Singleton.h
 * @brief  Singletonクラスのヘッダファイル
 * @author kotani
 */
#ifndef SINGLETON_H
#define SINGLETON_H

#define	SINGLETON_CREATE(InstanceType)	 Lib::Singleton<InstanceType>::Create()
#define	SINGLETON_DELETE(InstanceType)	 Lib::Singleton<InstanceType>::Delete()
#define	SINGLETON_INSTANCE(InstanceType) Lib::Singleton<InstanceType>::GetInstance()

namespace Lib
{
	/**
	 * シングルトンクラスを使う際にこいつを使う
	 */
	template <class T> 
	class Singleton {
	public:
		//typedefをしないとクラステンプレート外からは使えない
		typedef T InstanceType;
		/**
		 * インスタンスを取得する
		 * @return インスタンス
		 */
		inline static InstanceType& GetInstance()
		{
			return *m_Instance;
		}

		/**
		 * インスタンスを生成する
		 */
		inline static void Create()
		{
			if (m_Instance == nullptr)
			{
				m_Instance = new InstanceType;
			}
		}

		/**
		 * インスタンスを破棄する
		 */
		inline static void Delete()
		{
			delete m_Instance;
			m_Instance = nullptr;
		}

	private:
		Singleton(const Singleton& obj) = delete;
		Singleton& operator=(const Singleton& obj) = delete;

		Singleton(){};
		virtual ~Singleton(){};
		static T* m_Instance;

	};

	template <class Type>
	//Singleton<Type>::InstanceTypeを型と明示的に宣言している
	typename Singleton<Type>::InstanceType* Singleton<Type>::m_Instance = nullptr;
}

#endif

