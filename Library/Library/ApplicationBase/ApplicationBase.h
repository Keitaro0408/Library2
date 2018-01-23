#ifndef APPLICATIONBASE_H
#define APPLICATIONBASE_H

#include <Windows.h>
#ifdef _MSC_VER
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"strmiids.lib")
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"Imm32.lib")
//#pragma comment(lib,"libfbxsdk-mt.lib")
#endif

namespace Lib
{
	class ApplicationBase
	{
	public:
		/*** コンストラクタ */
		ApplicationBase(LPCTSTR _appName, int _windowWidth, int _windowHeight, int _refreshRate);

		/*** デストラクタ */
		virtual ~ApplicationBase();

		static inline ApplicationBase* GetInstance()
		{
			return m_pInstance;
		}

		/**
		 * 初期化処理
		 *
		 * ライブラリで自動に呼ばれる
		 */
		virtual bool Initialize() = 0;

		/**
		 * 開放処理
		 *
		 * ライブラリで自動に呼ばれる
		 */
		virtual void Finalize() = 0;

		/**
		 * この関数が毎フレーム呼ばれる
		 * @return trueになると終了する
		 */
		virtual bool MainLoop();

		int Boot();

	private:
		/*** ライブラリの初期化 */
		void InitLib();

		/*** ライブラリの解放 */
		void ReleaseLib();

		static ApplicationBase* m_pInstance;
		int						m_WindowWidth;
		int						m_WindowHeight;
		int						m_RefreshRate;
		LPCTSTR					m_AppName;

	};
}


#endif
