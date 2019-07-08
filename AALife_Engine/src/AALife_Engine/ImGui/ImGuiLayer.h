#pragma once

#include "AALife_Engine/Layer.h"

#include "AALife_Engine/Events/ApplicationEvent.h"
#include "AALife_Engine/Events/MouseEvent.h"
#include "AALife_Engine/Events/KeyEvent.h"

namespace ale {

	class ALE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};


}