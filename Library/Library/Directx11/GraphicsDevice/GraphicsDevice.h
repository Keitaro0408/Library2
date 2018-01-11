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
			 * �X�N���[���̐ݒ��؂�ւ���֐�
			 * @param[in] _isFullScreen �t���X�N���[���Ȃ�true �E�B���h�E�Ȃ�false
			 */
			inline void SetFullScreenState(bool _isFullScreen)
			{
				m_pDXGISwapChain->SetFullscreenState(_isFullScreen, nullptr);
			}

			/**
			 * DX11Manager�N���X�̏������֐�
			 * @param[in] _hWnd DX11Manager���Ή�����E�B���h�E�̃n���h��
			 * @param[in] _windowSize �N���C�A���g�E�B���h�E�̃T�C�Y
			 * @return �������ɐ���������true
			 */
			bool Initialize(HWND _hWnd, RECT _windowSize);

			/*** DX11Manager�N���X�̉���֐� */
			void Finalize();

			/*** �`��O�������s���֐� */
			void BeginScene();

			/*** �`��㏈�����s���֐� */
			void EndScene();

			/**
			 * �[�x�e�X�g�̃I���I�t��؂�ւ���֐�
			 * @param[in] _isStencil �[�x�e�X�g���g�p���邩�̃t���O
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
			 * �f�o�C�X�̏������֐�
			 * @return �������ɐ���������true
			 */
			bool InitDevice();

			/**
			 * �f�B�X�v���C�n�̏������֐�
			 * @return �������ɐ���������true
			 */
			bool InitDisplay();

			/*** �f�o�C�X�̉���֐� */
			void ReleaseDevice();

			/*** �f�B�X�v���C�n�̉���֐� */
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
