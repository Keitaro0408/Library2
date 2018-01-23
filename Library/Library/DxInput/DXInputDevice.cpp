/**
 * @file   DXInputDevice.cpp
 * @brief  DXInputDeviceクラスの実装
 * @author kotani
 */
#include "..\stdafx.h"
#include "DXInputDevice.h"


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::DXInputDevice::Initialize(HWND _hWnd)
{
	if (m_pDInput8 != nullptr)
	{
		MyOutputDebugString(TEXT("m_pDInput8の中身は空ではありません"));
		return false;
	}

	if (FAILED(DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		reinterpret_cast<void**>(&m_pDInput8),
		nullptr)))
	{
		MyOutputDebugString(TEXT("DirectInput8オブジェクトの生成に失敗しました"));
		return false;
	}

	m_hWnd = _hWnd;

	MyOutputDebugString(TEXT("DirectInput8オブジェクトの生成に成功\n"));

	return true;
}

void Lib::DXInputDevice::Finalize()
{
	SafeRelease(m_pDInput8);
}
