#pragma once

#include "Core.h"

#include "Window.h"
#include "AALife_Engine/LayerStack.h"
#include "AALife_Engine/Events/Event.h"
#include "AALife_Engine/Events/ApplicationEvent.h"

#include "AALife_Engine/ImGui/ImGuiLayer.h"

namespace ale {

	class ALE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	Application* CreateApplication();

}


