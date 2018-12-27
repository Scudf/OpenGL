#include <GL/glew.h>

#include "GameScene.h"
#include "Game.h"
#include "GraphicScene.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	Game::GetInstancePtr()->getGameScene()->processKeyCallback(window, key, scancode, action, mode);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Game::GetInstancePtr()->getGameScene()->processCursorPosCallback(window, xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Game::GetInstancePtr()->getGameScene()->processMouseButtonCallback(window, button, action, mods);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Game::GetInstancePtr()->getGameScene()->processScrollCallback(window, xoffset, yoffset);
}

GameScene::GameScene()
	: m_firstMousePos(true)
	, m_cameraSpeed(1000.0f)
	, m_mouseSensitivity(0.15f)
	, m_worldMousePosition(0)
	, m_cameraAnchor(0)
	, m_cameraTarget(0)
{
	GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();

	m_lastX = (float)(gs->getWidth() / 2.0f);
	m_lastY = (float)(gs->getHeight() / 2.0f);
}

bool GameScene::initialize()
{
	GLFWwindow* window = Game::GetInstancePtr()->getGraphicScene()->getWindow();
	GraphicScene*	gs = Game::GetInstancePtr()->getGraphicScene();

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	m_plane = GraphicObj::Create(gs->getModel("normPlane"), gs->getGLShader("normalsShader"));
	m_plane->setPosition(0.0f, 0.0f, -1.0f);
	m_plane->setDiffuseColor(glm::vec3(0.0f, 1.0f, 0.0f));
	gs->addObject(m_plane);

	return true;
}

bool GameScene::update(float dt)
{


	return true;
}

void GameScene::updateCameraPosition(float dt)
{
	GraphicScene* gs = Game::GetInstancePtr()->getGraphicScene();
	CameraPtr camera = gs->getCamera();

	float velocity = m_cameraSpeed * dt;

	if (m_keys[GLFW_KEY_W])
		camera->setPosition(camera->getPosition() + camera->getFront() * velocity);
	if (m_keys[GLFW_KEY_S])
		camera->setPosition(camera->getPosition() - camera->getFront() * velocity);
	if (m_keys[GLFW_KEY_A])
		camera->setPosition(camera->getPosition() - camera->getRight() * velocity);
	if (m_keys[GLFW_KEY_D])
		camera->setPosition(camera->getPosition() + camera->getRight() * velocity);
}

void GameScene::processKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void GameScene::processCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	CameraPtr camera = Game::GetInstancePtr()->getGraphicScene()->getCamera();

	if (m_firstMousePos)
	{
		m_lastX = (float)xpos;
		m_lastY = (float)ypos;
		m_firstMousePos = false;
	}

	float xoffset = (float)xpos - m_lastX;
	float yoffset = m_lastY - (float)ypos;

	m_lastX = (float)xpos;
	m_lastY = (float)ypos;

	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	camera->setYaw(camera->getYaw() + xoffset);
	camera->setPitch(camera->getPitch() + yoffset);

	if (camera->getPitch() > 89.0f)
		camera->setPitch(89.0f);
	if (camera->getPitch() < -89.0f)
		camera->setPitch(-89.0f);

	camera->updateCameraVectors();
}

void GameScene::processPressMouseButton(int button)
{

}

void GameScene::processMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

}

void GameScene::processScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	CameraPtr camera = Game::GetInstancePtr()->getGraphicScene()->getCamera();

	if (camera->getZoom() >= 1.0f && camera->getZoom() <= 45.0f)
		camera->setZoom(camera->getZoom() - (float)yoffset);
	if (camera->getZoom() <= 1.0f)
		camera->setZoom(1.0f);
	if (camera->getZoom() >= 45.0f)
		camera->setZoom(45.0f);
}