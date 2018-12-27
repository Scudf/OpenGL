#pragma once

#include "GameScene.h"
#include "GraphicScene.h"


class Game
{
public:
	Game();
	~Game();

	bool initialize();
	bool update();

	GameScene* getGameScene() const { return m_gameScene; }
	GraphicScene* getGraphicScene() const { return m_graphicScene; }

	static Game* GetInstancePtr() { return s_instance; }

private:
	GameScene* m_gameScene;
	GraphicScene* m_graphicScene;

	static Game* s_instance;

	float m_lastFrameTime;
};
