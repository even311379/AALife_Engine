#include "Application.h"

#include "AALife_Engine/Events/ApplicationEvent.h"
#include "AALife_Engine/Log.h"


namespace ale {


	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		ALE_TRACE(e);

		while (true);
	}

}
