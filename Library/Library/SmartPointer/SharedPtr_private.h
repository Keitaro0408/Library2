﻿#ifndef SHARED_PTR_PRIVATE_H
#define SHARED_PTR_PRIVATE_H

template<typename Type>
SharedPtr<Type>::SharedPtr(Type* _type) :
SmartPtr(_type)
{
	m_pRefCount = new unsigned int;
	*m_pRefCount = 1;

	m_pWeakCount = new unsigned int;
	*m_pWeakCount = 1;
}

template<typename Type>
SharedPtr<Type>::SharedPtr()
{
	m_pRefCount = nullptr;
	m_pWeakCount = nullptr;
	m_pInstance = nullptr;
}

template<typename Type>
SharedPtr<Type>::~SharedPtr()
{
	Release();
}

template<typename Type>
void SharedPtr<Type>::Reset()
{
	SafeDelete(m_pRefCount);
	SafeDelete(m_pWeakCount);
	if (m_pInstance != nullptr)
	{
		(*m_pDeleter)(m_pInstance);
	}
	m_pInstance = nullptr;
}

template<typename Type>
void SharedPtr<Type>::Reset(Type* _type)
{
	SafeDelete(m_pRefCount);
	if (m_pInstance != nullptr)
	{
		(*m_pDeleter)(m_pInstance);
		m_pInstance = nullptr;
		m_pDeleter = nullptr;
	}

	m_pRefCount = new unsigned int;
	*m_pRefCount = 1;

	m_pWeakCount = new unsigned int;
	*m_pWeakCount = 1;

	m_pDeleter = new DeleterImpl<Type>();
	m_pInstance = _type;
}


template<typename Type>
SharedPtr<Type>& SharedPtr<Type>::operator=(const SharedPtr& _obj)
{
	m_pRefCount = _obj.m_pRefCount;

	/* 違うポインタなら参照カウンタを増やす */
	if (m_pInstance != _obj.m_pInstance)
	{
		AddRef();
		++m_pWeakCount;
		m_pInstance = _obj.m_pInstance;
	}
	return *this;
}

template<typename Type>
Type* SharedPtr<Type>::operator->() const
{
	return m_pInstance;
}

template<typename Type>
void SharedPtr<Type>::AddRef()
{
	if (m_pRefCount != nullptr)
	{
		++(*m_pRefCount);
	}
}

template<typename Type>
void SharedPtr<Type>::Release()
{
	if (m_pRefCount != nullptr)
	{
		--(*m_pRefCount);
		--(*m_pWeakCount);

		if (*m_pRefCount == 0)
		{
			if (m_pInstance != nullptr)
			{
				(*m_pDeleter)(m_pInstance);
				m_pInstance = nullptr;
			}
		}

		if (*m_pWeakCount == 0)
		{
			SafeDelete(m_pWeakCount);
			SafeDelete(m_pRefCount);
		}
	}
}


#endif
