#ifndef APP_H
#define APP_H

#include "ApplicationBase/ApplicationBase.h"
#include "TestScene.h"

class App : public Lib::ApplicationBase
{
public:
	App();
	~App();

	bool Initialize() override;

	void Finalize() override;

private:
	Lib::SceneBase* m_pTestScene;

} app;


#endif