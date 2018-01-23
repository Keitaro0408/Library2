/**
 * @file   MouseDevice.cpp
 * @brief  MouseDeviceクラスの実装
 * @author kotani
 */
#include "..\..\stdafx.h"
#include "MouseDevice.h"


Lib::MouseDevice::MouseDevice() :
m_pDInput8(nullptr),
m_hWnd(nullptr),
m_pDInputDevice8(nullptr)
{
	for (int i = 0; i < 4; i++)
	{
		m_DIMouseState.rgbButtons[i] = 0;
		m_OldDIMouseState.rgbButtons[i] = 0;
	}
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::MouseDevice::Initialize(LPDIRECTINPUT8 _pDInput8, HWND _hWnd)
{
	if (m_pDInput8 != nullptr)
	{
		MyOutputDebugString(TEXT("MouseDeviceクラスは既に初期化されています"));
		return false;
	}

	m_pDInput8 = _pDInput8;
	m_hWnd = _hWnd;

	if (m_pDInput8 == nullptr)
	{
		MyOutputDebugString(TEXT("DirectInput8オブジェクトが有効ではありません"));
		return false;
	}

	if (FAILED(m_pDInput8->CreateDevice(GUID_SysMouse, &m_pDInputDevice8, nullptr)))
	{
		MyOutputDebugString(TEXT("DirectInput8マウスデバイスの生成に失敗しました"));
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetDataFormat(&c_dfDIMouse)))
	{
		MyOutputDebugString(TEXT("DirectInput8マウスデバイスのデータフォーマットの設定に失敗しました"));
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
		MyOutputDebugString(TEXT("DirectInput8マウスデバイスのバッファ設定に失敗しました"));
		m_pDInputDevice8->Release();
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		MyOutputDebugString(TEXT("DirectInput8マウスデバイスの協調レベルの設定に失敗しました"));
		m_pDInputDevice8->Release();
		return false;
	}

	m_pDInputDevice8->Acquire();

	MyOutputDebugString(TEXT("DirectInputのMouseDeviceの初期化に成功しました\n"));

	return true;
}

void Lib::MouseDevice::Finalize()
{
	if (m_pDInputDevice8 != nullptr)
	{
		m_pDInputDevice8->Release();
		m_pDInputDevice8 = nullptr;
		m_pDInput8 = nullptr;
	}
}

void Lib::MouseDevice::Update()
{
	HRESULT hr = m_pDInputDevice8->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		m_pDInputDevice8->GetDeviceState(sizeof(m_DIMouseState), &m_DIMouseState);
	}

	m_MouseState.X = m_DIMouseState.lX;
	m_MouseState.Y = m_DIMouseState.lY;
	m_MouseState.Z = m_DIMouseState.lZ;
	GetCursorPos(&m_MouseState.CursorPos);

	RECT WindowRect;
	RECT ClientRect;
	int TitleBarSize = GetSystemMetrics(SM_CYCAPTION);
	GetWindowRect(m_hWnd, &WindowRect);
	GetClientRect(m_hWnd, &ClientRect);
	m_MouseState.CursorPos.x -= WindowRect.left;
	m_MouseState.CursorPos.y -= WindowRect.top;

	m_MouseState.CursorPos.x -= (WindowRect.right - WindowRect.left - ClientRect.right - ClientRect.left) / 2;
	m_MouseState.CursorPos.y -= (WindowRect.bottom - WindowRect.top - ClientRect.bottom + TitleBarSize - ClientRect.top) / 2;

	for (int i = 0; i < MOUSEBUTTON_MAX; i++)
	{
		if (m_DIMouseState.rgbButtons[i])
		{
			if (m_OldDIMouseState.rgbButtons[i])
			{
				m_MouseState.Buttons[i] = MOUSEBUTTON_ON;
			}
			else
			{
				m_MouseState.Buttons[i] = MOUSEBUTTON_PUSH;
			}
			m_OldDIMouseState.rgbButtons[i] = m_DIMouseState.rgbButtons[i];
		}
		else
		{
			if (m_OldDIMouseState.rgbButtons[i])
			{
				m_MouseState.Buttons[i] = MOUSEBUTTON_RELEASE;
			}
			else
			{
				m_MouseState.Buttons[i] = MOUSEBUTTON_OFF;
			}
			m_OldDIMouseState.rgbButtons[i] = m_DIMouseState.rgbButtons[i];
		}
	}
}
