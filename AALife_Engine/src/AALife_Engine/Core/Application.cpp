#include "alePCH.h"
#include "Application.h"

#include "AALife_Engine/Core/Log.h"

#include "AALife_Engine/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>

namespace ale {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;




	Application::Application()
		
	{
		ALE_CORE_ASSERT(!s_Instance, "Application already exist!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		//m_Window->SetVSync(false);

        Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}

		//ALE_CORE_TRACE("{0}", e);
	}


	void Application::Run()
	{
		while (m_Running) 
		{
			float time = (float)glfwGetTime(); // Platfrom::GetTime
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

            if (!m_Minimized) {
			    for (Layer* layer : m_LayerStack)
				    layer->OnUpdate(timestep);
            }

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        if (e.GetHeight() == 0 || e.GetWidth() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        return false;
    }
}
