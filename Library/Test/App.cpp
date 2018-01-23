#include "App.h"

#include "SceneManager\SceneManager.h"
#include "Texture\TextureManager.h"
#include "Directx11\GraphicsDevice\GraphicsDevice.h"
#include "Texture\TextureManager.h"
#include "Window\Window.h"


App::App() :
	ApplicationBase(
		"Test", 
		1280, 
		720, 
		60)
{
}


App::~App()
{
}

bool App::Initialize()
{
	SINGLETON_CREATE(Lib::SceneManager);

	SINGLETON_CREATE(Lib::Dx11::GraphicsDevice);
	SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice).Initialize(
		SINGLETON_INSTANCE(Lib::Window).GetWindowHandle(),
		SINGLETON_INSTANCE(Lib::Window).GetWindowSize());

	SINGLETON_CREATE(Lib::TextureManager);
	SINGLETON_INSTANCE(Lib::TextureManager).Initialize(
		SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice).GetDevice());

	m_pTestScene = new TestScene();
	SINGLETON_INSTANCE(Lib::SceneManager).AddScene(m_pTestScene);
	SINGLETON_INSTANCE(Lib::SceneManager).ChangeScene("TestScene");
	return false;
}

void App::Finalize()
{
	Lib::SafeDelete(m_pTestScene);
	SINGLETON_INSTANCE(Lib::Dx11::GraphicsDevice).Finalize();
	SINGLETON_DELETE(Lib::Dx11::GraphicsDevice);
	SINGLETON_DELETE(Lib::TextureManager);

	SINGLETON_DELETE(Lib::SceneManager);
}
