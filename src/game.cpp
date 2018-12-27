#include <Windows.h>
#include <conio.h>
#include <GL/glew.h>

#include "Game.h"


Game* Game::s_instance = nullptr;

Game::Game()
	: m_lastFrameTime(0.0f)
{
	s_instance = this;
}


Game::~Game()
{
	delete m_gameScene;
	delete m_graphicScene;
}

bool Game::initialize()
{
	m_graphicScene = new GraphicScene();
	if (!m_graphicScene->initialize())
		return false;

	m_gameScene = new GameScene();
	if (!m_gameScene->initialize())
		return false;

	m_lastFrameTime = (float)glfwGetTime();

	return true;
}

bool Game::update()
{
	float currentFrameTime = (float)glfwGetTime();
	float deltaTime = currentFrameTime - m_lastFrameTime;
	m_lastFrameTime = currentFrameTime;

	if (!m_gameScene->update(deltaTime))
		return false;

	if (!m_graphicScene->update(deltaTime))
		return false;

	return true;
}