#include "ApplicationBase.h"

Lib::ApplicationBase* Lib::ApplicationBase::m_pInstance = nullptr;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	return Lib::ApplicationBase::GetInstance()->Boot();
}


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------

	ApplicationBase::ApplicationBase(
		LPCTSTR _appName, 
		int _windowWidth, 
		int _windowHeight, 
		int _refreshRate = 60) :
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
	}
	
	
	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------

	bool ApplicationBase::MainLoop()
	{
		return false;
	}

	int ApplicationBase::Boot()
	{
		return 0;
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------

	void ApplicationBase::InitLib()
	{
	}

	void ApplicationBase::ReleaseLib()
	{
	}
}
