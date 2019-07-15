#pragma once

#include "Core.h"

#include "Window.h"
#include "AALife_Engine/LayerStack.h"
#include "AALife_Engine/Events/Event.h"
#include "AALife_Engine/Events/ApplicationEvent.h"

#include "AALife_Engine/ImGui/ImGuiLayer.h"

#include "AALife_Engine/Renderer/Shader.h"
#include "AALife_Engine/Renderer/Buffer.h"
#include "AALife_Engine/Renderer/VertexArray.h"


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

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_Shader2;
		std::shared_ptr<VertexArray> m_SquareVA;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}


