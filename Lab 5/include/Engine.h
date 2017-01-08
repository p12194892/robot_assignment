#pragma once
#include "WindowComponent.h"
class Engine
{
	private:
		bool m_bstartRunning;
		WindowComponent* m_window;
	public:
		Engine();
		void start();
		void stop();
};