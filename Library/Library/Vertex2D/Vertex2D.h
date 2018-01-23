/**
 * @file   Vertex2D.h
 * @brief  Vertex2Dクラスのヘッダファイル
 * @author kotani
 */
#ifndef VERTEX2D_H
#define VERTEX2D_H
#include <D3DX11.h>
#include <D3DX10.h>

#include "..\Math\MyVector.h"
#include "..\Math\MyMatrix.h"

#include "..\Directx11\GraphicsDevice\GraphicsDevice.h"

namespace Lib
{
	/**
	 * 2Dの矩形を描画するクラス
	 */
	class Vertex2D
	{
	public:
		/**
		 * Vertex2Dクラスのコンストラクタ
		 * @param[in] _pDevice バッファ作成などのために利用するDirectX11のデバイス
		 * @param[in] _pDeviceContext 描画などに利用するDirectX11のデバイスコンテキスト
		 * @param[in] _windowSize 2dの矩形を描画するウィンドウのハンドル
		 */
		Vertex2D(const Dx11::GraphicsDevice& _graphicDevice);

		/**
		 * Vertex2Dクラスのデストラクタ
		 */
		~Vertex2D(){};

		/**
		 * Vertex2Dクラスの初期化関数
		 * @param[in] _RectSize 矩形のサイズ
		 * @param[in] _minUV テクスチャの最小uv値
		 * @param[in] _maxUV テクスチャの最大uv値
		 * @return 初期化に成功したらtrue
		 */
		bool Initialize(
			const VECTOR2& _RectSize, 
			const VECTOR2& _minUV = VECTOR2(0.f, 0.f),
			const VECTOR2& _maxUV = VECTOR2(1.0f, 1.0f));

		/**
		 * Vertex2Dクラスの解放関数
		 */
		void Finalize();

		void SetUV(const VECTOR2& _minUV, const VECTOR2& _maxUV)
		{
			m_VertexData[0].UV = VECTOR2(_minUV.x, _minUV.y);
			m_VertexData[1].UV = VECTOR2(_maxUV.x, _minUV.y);
			m_VertexData[2].UV = VECTOR2(_minUV.x, _maxUV.y);
			m_VertexData[3].UV = VECTOR2(_maxUV.x, _maxUV.y);
		}

		void SetColor(const COLOR& _color)
		{
			for (int i = 0; i < 4; i++) m_VertexData[i].Color = _color;
		}

		void SetAngle(float _angle){ m_Angle = _angle; }

		/**
		 * 2Dの矩形を描画する関数
		 */
		void Draw();

		/**
		 * 2Dの矩形を描画する関数
		 * @param[in] _DrawPos 矩形を描画するスクリーン座標位置
		 */
		void Draw(const VECTOR2& _DrawPos);

		/**
		 * 描画するテクスチャをセットする関数
		 * @param[in] _pTextureResourceView セットするテクスチャ
		 */
		void SetTexture(ID3D11ShaderResourceView* _pTextureResourceView)
		{
			m_pTextureResourceView = _pTextureResourceView;
		}

	private:
		/**
		* 2D矩形の描画に利用する頂点構造体
		*/
		struct VERTEX
		{
			VECTOR3 Pos;	//!< 頂点座標
			VECTOR2 UV;		//!< テクスチャ座標
			COLOR   Color;
		};

		/**
		 * シェーダーに渡す定数バッファ
		 *
		 * 定数バッファは16バイト区切りじゃないとバッファ作成に失敗する
		 */
		struct SHADER_CONSTANT_BUFFER
		{
			MATRIX  MatWorld;	//!< ワールド変換行列
			VECTOR4 WindowSize;	//!< ウィンドウの縦横サイズ
		};

		/**
		 * 頂点シェーダーの初期化関数
		 * @return 初期化に成功したらtrue
		 */
		bool InitVertexShader();

		/**
		 * 頂点入力レイアウトの初期化関数
		 * @return 初期化に成功したらtrue
		 */
		bool InitVertexLayout();

		/**
		 * ピクセルシェーダーの初期化関数
		 * @return 初期化に成功したらtrue
		 */
		bool InitPixelShader();

		/**
		 * ブレンドステートの初期化関数
		 * @return 初期化に成功したらtrue
		 */
		bool InitBlendState();

		/**
		 * サンプラステートの初期化関数
		 * @return 初期化に成功したらtrue
		 */
		bool InitSamplerState();

		/**
		 * 頂点バッファの生成
		 * @param[in] _pSize 描画する2Dポリゴンの矩形サイズ
		 * @param[in] _pMinUV テクスチャのMin座標
		 * @param[in] _pMaxUV テクスチャのMax座標
		 * @param[in] _pColor 頂点色
		 * @return 初期化に成功したらtrue 失敗したらfalse
		 */
		bool InitVertexBuffer(
			const VECTOR2& _pSize,
			const VECTOR2& _pMinUV = VECTOR2(0.f, 0.f),
			const VECTOR2& _pMaxUV = VECTOR2(1.0f, 1.0f),
			const COLOR& _pColor = COLOR(0xffffffff));

		/**
		 * 定数バッファの初期化関数
		 * @return 初期化に成功したらtrue
		 */
		bool InitConstantBuffer();

		/**
		 * 定数バッファにデータを書き込む関数
		 * @param[in] _DrawPos 矩形を描画するスクリーン座標位置
		 */
		bool WriteConstantBuffer(const VECTOR2& _DrawPos = VECTOR2(0.f, 0.f));

		bool WriteVertexBuffer();

		/**
		 * 頂点シェーダーの解放関数
		 */
		void ReleaseVertexShader();

		/**
		 * 頂点インプットレイアウトの解放関数
		 */
		void ReleaseVertexLayout();

		/**
		 * ピクセルシェーダーの解放関数
		 */
		void ReleasePixelShader();

		/**
		 * ブレンドステートの解放関数
		 */
		void ReleaseBlendState();

		/**
		 * サンプラの解放関数
		 */
		void ReleaseSamplerState();

		/**
		 * 頂点バッファの解放関数
		 */
		void ReleaseVertexBuffer();

		/**
		 * 定数バッファの解放関数
		 */
		void ReleaseConstantBuffer();


		static const int			m_VertexNum;
		static const UINT			m_ColorMask;

		ID3D11Device* 				m_pDevice;
		ID3D11DeviceContext* 		m_pDeviceContext;
		ID3D11VertexShader*			m_pVertexShader;
		ID3DBlob*					m_pVertexCompiledShader;
		ID3D11InputLayout*			m_pVertexLayout;
		ID3D11PixelShader*			m_pPixelShader;
		ID3D11BlendState*			m_pBlendState;
		ID3D11SamplerState*			m_pSamplerState;
		ID3D11Buffer*				m_pVertexBuffer;
		ID3D11Buffer*				m_pConstantBuffer;
		ID3D11ShaderResourceView*	m_pTextureResourceView;
		VERTEX						m_VertexData[4];
		int							m_ClientWidth;
		int							m_ClientHeight;

		VECTOR2						m_RectSize;
		VECTOR2						m_Scale;
		float						m_Angle;
	};


}


#endif
