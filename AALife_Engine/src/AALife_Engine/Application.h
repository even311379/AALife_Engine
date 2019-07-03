#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace ale {

	class ALE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();

}


