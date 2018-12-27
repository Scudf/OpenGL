#pragma once

#include <GLFW/glfw3.h>

#include "GraphicObj.h"


class GameScene
{
public:
	GameScene();

	bool initialize();
	bool update(float dt);

	void updateCameraPosition(float dt);

	void processKeyCallback(
		GLFWwindow* window,
		int key,
		int scancode,
		int action,
		int mods);

	void processCursorPosCallback(
		GLFWwindow*	window,
		double xpos,
		double ypos);

	void processPressMouseButton(int button);

	void processMouseButtonCallback(
		GLFWwindow* window,
		int button,
		int action,
		int mode);

	void processScrollCallback(
		GLFWwindow* window,
		double xoffset,
		double yoffset);

	inline bool getKey(int key) const { return m_keys[key]; }

private:
	GraphicObjPtr m_plane;

	bool m_keys[1024];
	bool m_buttons[16];

	bool m_firstMousePos;

	float m_lastX;
	float m_lastY;

	float m_cameraSpeed;
	float m_mouseSensitivity;

	glm::vec3 m_worldMousePosition;

	glm::vec3 m_cameraAnchor;
	glm::vec3 m_cameraTarget;
};