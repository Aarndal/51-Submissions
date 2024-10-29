#include <GLFW/glfw3.h>
#include "Time.h"

float Time::m_deltaTime{};
float Time::m_totalTime{};
float Time::m_lastTimeStamp{};


int Time::Init()
{
	m_lastTimeStamp = glfwGetTime();
	
	if (!m_lastTimeStamp)
		return -111;

	return 0;
}

int Time::Update()
{

	m_totalTime = glfwGetTime();

	if (!m_totalTime)
		return -100;

	m_deltaTime = m_totalTime - m_lastTimeStamp;
	m_lastTimeStamp = m_totalTime;

	return 0;
}
