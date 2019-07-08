#include <AALife_Engine.h>

#include "imgui/imgui.h"


class ExampleLayer : public ale::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (ale::Input::IsKeyPressed(ALE_KEY_TAB))
			ALE_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{

		ImGui::Begin("t");
		ImGui::Text("Hello World");
		ImGui::End();


		ImGui::Begin("Triangle Position/Color");
		static float rotation = 0.0;
		ImGui::SliderFloat("rotation", &rotation, 0, 2 * 3.16);
		static float translation[] = { 0.0, 0.0 };
		ImGui::SliderFloat2("position", translation, -1.0, 1.0);
		static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
		// pass the parameters to the shader
		// color picker
		ImGui::ColorEdit3("color", color);
		ImGui::End();
	}

	void OnEvent(ale::Event& event) override
	{
		if (event.GetEventType() == ale::EventType::KeyPressed)
		{
			ale::KeyPressedEvent& e = (ale::KeyPressedEvent&)event;
			if (e.GetKeyCode() == ALE_KEY_TAB)
				ALE_TRACE("Tab key is pressed (event)!");
			ALE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};



class Sandbox : public ale::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {
		 
	}
};


ale::Application* ale::CreateApplication()
{
	return new Sandbox();
}