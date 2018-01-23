#include "ApplicationBase.h"

#include <crtdbg.h>
#include "../Window/Window.h"
#include "../DxInput/DXInputDevice.h"
#include "../Texture/TextureManager.h"
#include "../Event/EventManager.h"
#include "../TaskManager/TaskManager.h"
#include "../XInput/XInput.h"
#include "../SceneManager/SceneManager.h"

Lib::ApplicationBase* Lib::ApplicationBase::m_pInstance = nullptr;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	return Lib::ApplicationBase::GetInstance()->Boot();
}


namespace Lib
{
	ApplicationBase::ApplicationBase(LPCTSTR _appName, int _windowWidth, int _windowHeight, int _refreshRate) :
		m_AppName(_appName),
		m_WindowWidth(_windowWidth),
		m_WindowHeight(_windowHeight),
		m_RefreshRate(_refreshRate)
	{
		::ImmDisableIME(NULL);
		m_pInstance = this;
	}

	ApplicationBase::~ApplicationBase()
	{
		SINGLETON_DELETE(Lib::Window);
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	int ApplicationBase::Boot()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		SINGLETON_CREATE(Lib::Window);
		SINGLETON_INSTANCE(Lib::Window).DispWindow(m_WindowWidth, m_WindowHeight, m_AppName);

		InitLib();
		Initialize();

		MSG Msg;
		ZeroMemory(&Msg, sizeof(Msg));
		while (Msg.message != WM_QUIT)
		{

			if (PeekMessage(&Msg, nullptr, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
			else
			{
				if (MainLoop())
				{
					break;
				}
			}
		}
		/* 先にサブクラスからデストラクタが実行されるのでここで解放する */
		SINGLETON_INSTANCE(Lib::SceneManager).AllRemoveScene();
		SINGLETON_DELETE(Lib::SceneManager);
		Finalize();
		ReleaseLib();
		return 0;
	}

	bool ApplicationBase::MainLoop()
	{
		static LARGE_INTEGER Time1;
		LARGE_INTEGER Frq, Time2;
		double TotalTime = 0;
		QueryPerformanceFrequency(&Frq);
		double MicroSec = 1000000 / (double)Frq.QuadPart;

		while (TotalTime<(1000000 / m_RefreshRate))
		{
			QueryPerformanceCounter(&Time2);
			TotalTime = (Time2.QuadPart - Time1.QuadPart)*MicroSec;
		}
		QueryPerformanceCounter(&Time1);
		return SINGLETON_INSTANCE(Lib::SceneManager).Run();
	}

	void ApplicationBase::InitLib()
	{
	}

	void ApplicationBase::ReleaseLib()
	{
	}
}
