#pragma once
#include "SceneManager\SceneBase\SceneBase.h"
#include "TaskManager\TaskBase\DrawTask\DrawTask.h"
#include "TaskManager\TaskBase\UpdateTask\UpdateTask.h"
#include "Vertex2D\Vertex2D.h"


class TestScene : public Lib::SceneBase
{
public:
	TestScene();
	~TestScene();

	bool Initialize() override;

	void Finalize() override;

	void Run() override;

private:
	Lib::Vertex2D* m_pVertex;
	int			   m_TextureIndex;

};

