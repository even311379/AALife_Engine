#include <AALife_Engine.h>

class ExampleLayer : public ale::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		ALE_INFO("ExampleLayer::Update");
	}

	void OnEvent(ale::Event& event) override
	{
		ALE_TRACE("{0}", event);
	}

};



class Sandbox : public ale::Application
{
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushOverlay(new ale::ImGuiLayer());
	}

	~Sandbox() {
		 
	}
};


ale::Application* ale::CreateApplication()
{
	return new Sandbox();
}