#include "TestScene.h"
#include "Directx11\GraphicsDevice\GraphicsDevice.h"
#include "Texture\TextureManager.h"


TestScene::TestScene() :
	SceneBase("TestScene"),
	m_TextureIndex(0)
{
}


TestScene::~TestScene()
{
}

bool TestScene::Initialize()
{
	SINGLETON_INSTANCE(Lib::TextureManager).Load("test.png",&m_TextureIndex);

	m_pVertex = new Lib::Vertex2D(SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice));
	m_pVertex->Initialize(Lib::VECTOR2(100,100));
	m_pVertex->SetTexture(SINGLETON_INSTANCE(Lib::TextureManager).GetTexture(m_TextureIndex));
	return false;
}

void TestScene::Finalize()
{
	Lib::SafeFinalize(m_pVertex);
	SINGLETON_INSTANCE(Lib::TextureManager).ReleaseTexture(m_TextureIndex);
}

void TestScene::Run()
{
	SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice).BeginScene();
	m_pVertex->Draw(Lib::VECTOR2(50,50));

	SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice).EndScene();
}
