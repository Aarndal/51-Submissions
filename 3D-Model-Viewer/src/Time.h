#ifndef TIME_H
#define TIME_H

struct Time
{
	static float GetDeltaTime() { return m_deltaTime; };
	static float GetTime() { return m_totalTime; };

	static int Init();
	static int Update();

private:
	static float m_deltaTime;
	static float m_totalTime;
	static float m_lastTimeStamp;
};

#endif //TIME_H
