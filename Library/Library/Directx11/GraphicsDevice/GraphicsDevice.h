#ifndef LIB_DX11_GRAPHICSDEVICE_H
#define LIB_DX11_GRAPHICSDEVICE_H
#include <D3D11.h>
#include <Windows.h>

namespace Lib
{
	namespace Dx11
	{
		class GraphicsDevice
		{
		public:
			/**
			 * スクリーンの設定を切り替える関数
			 * @param[in] _isFullScreen フルスクリーンならtrue ウィンドウならfalse
			 */
			inline void SetFullScreenState(bool _isFullScreen)
			{
				m_pDXGISwapChain->SetFullscreenState(_isFullScreen, nullptr);
			}

			/**
			 * DX11Managerクラスの初期化関数
			 * @param[in] _hWnd DX11Managerが対応するウィンドウのハンドル
			 * @param[in] _windowSize クライアントウィンドウのサイズ
			 * @return 初期化に成功したらtrue
			 */
			bool Initialize(HWND _hWnd, RECT _windowSize);

			/*** DX11Managerクラスの解放関数 */
			void Finalize();

			/*** 描画前処理を行う関数 */
			void BeginScene();

			/*** 描画後処理を行う関数 */
			void EndScene();

			/**
			 * 深度テストのオンオフを切り替える関数
			 * @param[in] _isStencil 深度テストを使用するかのフラグ
			 */
			void SetDepthStencilTest(bool _isStencil);

		private:
			GraphicsDevice() : 
				m_pDevice(nullptr),
				m_pDeviceContext(nullptr),
				m_pDXGI(nullptr),
				m_pAdapter(nullptr),
				m_pDXGIFactory(nullptr),
				m_pDXGISwapChain(nullptr),
				m_pBackBuffer(nullptr),
				m_pRenderTargetView(nullptr),
				m_pDepthStencilBuffer(nullptr),
				m_pDepthStencilView(nullptr),
				m_pRasterizerState(nullptr),
				m_hWnd(nullptr)
			{
			}


			~GraphicsDevice() {};

			/**
			 * デバイスの初期化関数
			 * @return 初期化に成功したらtrue
			 */
			bool InitDevice();

			/**
			 * ディスプレイ系の初期化関数
			 * @return 初期化に成功したらtrue
			 */
			bool InitDisplay();

			/*** デバイスの解放関数 */
			void ReleaseDevice();

			/*** ディスプレイ系の解放関数 */
			void ReleaseDisplay();

			static GraphicsDevice*	m_pGraphicsDevice;
			static float			m_ClearColor[4];
			ID3D11Device*			m_pDevice;
			ID3D11DeviceContext*	m_pDeviceContext;
			IDXGIDevice1*			m_pDXGI;
			IDXGIAdapter*			m_pAdapter;
			IDXGIFactory*			m_pDXGIFactory;
			IDXGISwapChain*			m_pDXGISwapChain;
			DXGI_SWAP_CHAIN_DESC	m_DXGISwapChainDesc;
			ID3D11Texture2D*		m_pBackBuffer;
			ID3D11RenderTargetView* m_pRenderTargetView;
			ID3D11Texture2D*		m_pDepthStencilBuffer;
			D3D11_TEXTURE2D_DESC	m_DepthDesc;
			ID3D11DepthStencilView* m_pDepthStencilView;
			D3D11_VIEWPORT			m_ViewPort;
			ID3D11RasterizerState*  m_pRasterizerState;
			D3D11_RASTERIZER_DESC	m_RasterizerDesc;
			HWND					m_hWnd;
			RECT					m_WindowRect;

		};
	}
}


#endif
