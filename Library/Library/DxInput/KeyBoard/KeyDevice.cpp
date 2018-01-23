/**
* @file   KeyDevice.cpp
* @brief  KeyDeviceクラスの実装
* @author kotani
*/
#include "..\..\stdafx.h"
#include "KeyDevice.h"

namespace Lib
{
	KeyDevice::KeyDevice()
	{
		for (int i = 0; i < 256; i++)
		{
			m_pDIKeyState[i] = 0;
			m_pOldDIKeyState[i] = 0;
		}
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool KeyDevice::Init(LPDIRECTINPUT8 _pDInput8, HWND _hWnd)
	{
		if (m_pDInput8 != NULL)
		{
			MyOutputDebugString(TEXT("KeyDeviceクラスは既に初期化されています"));
			return false;
		}

		m_pDInput8 = _pDInput8;
		m_hWnd = _hWnd;

		if (m_pDInput8 == NULL)
		{
			MyOutputDebugString(TEXT("DirectInput8オブジェクトが有効ではありません"));
			return false;
		}

		if (FAILED(m_pDInput8->CreateDevice(GUID_SysKeyboard, &m_pDInputDevice8, NULL)))
		{
			MyOutputDebugString(TEXT("DirectInput8キーデバイスの生成に失敗しました"));
			return false;
		}

		if (FAILED(m_pDInputDevice8->SetDataFormat(&c_dfDIKeyboard)))
		{
			MyOutputDebugString(TEXT("DirectInput8キーデバイスのデータフォーマットの設定に失敗しました"));
			m_pDInputDevice8->Release();
			return false;
		}

		DIPROPDWORD DiProp;
		DiProp.diph.dwSize = sizeof(DiProp);
		DiProp.diph.dwHeaderSize = sizeof(DiProp.diph);
		DiProp.diph.dwObj = 0;
		DiProp.diph.dwHow = DIPH_DEVICE;
		DiProp.dwData = 1000;
		if (FAILED(m_pDInputDevice8->SetProperty(DIPROP_BUFFERSIZE, &DiProp.diph)))
		{
			MyOutputDebugString(TEXT("DirectInput8キーデバイスのバッファ設定に失敗しました"));
			m_pDInputDevice8->Release();
			return false;
		}

		if (FAILED(m_pDInputDevice8->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
		{
			MyOutputDebugString(TEXT("DirectInput8キーデバイスの協調レベルの設定に失敗しました"));
			m_pDInputDevice8->Release();
			return false;
		}

		m_pDInputDevice8->Acquire();

		MyOutputDebugString(TEXT("DirectInputのKeyDeviceの初期化に成功した\n"));

		return true;
	}

	void KeyDevice::Release()
	{
		if (m_pDInputDevice8 != NULL)
		{
			m_pDInputDevice8->Release();
			m_pDInputDevice8 = NULL;
			m_pDInput8 = NULL;
			MyOutputDebugString(TEXT("DirectInputのKeyDeviceを解放しました\n"));
		}
	}

	void KeyDevice::Update()
	{
		HRESULT hr = m_pDInputDevice8->Acquire();
		if ((hr == DI_OK) || (hr == S_FALSE))
		{
			m_pDInputDevice8->GetDeviceState(sizeof(m_pDIKeyState), &m_pDIKeyState);
		}
	}

	void KeyDevice::KeyCheck(int _dik)
	{
		if (m_pDIKeyState[_dik] & 0x80)
		{
			if (m_pOldDIKeyState[_dik] == KEY_OFF)
			{
				m_pKeyState[_dik] = KEY_PUSH;
			}
			else
			{
				m_pKeyState[_dik] = KEY_ON;
			}
			m_pOldDIKeyState[_dik] = KEY_ON;
		}
		else
		{
			if (m_pOldDIKeyState[_dik] == KEY_ON)
			{
				m_pKeyState[_dik] = KEY_RELEASE;
			}
			else
			{
				m_pKeyState[_dik] = KEY_OFF;
			}
			m_pOldDIKeyState[_dik] = KEY_OFF;
		}
	}

	const KEYSTATE* Lib::KeyDevice::GetKeyState() const
	{
		return m_pKeyState;
	}
}
