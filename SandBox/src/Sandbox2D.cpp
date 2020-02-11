#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "AALife_Engine/Platform/OpenGL/OpenGLShader.h"
#include <chrono>


Sandbox2D::Sandbox2D()
    :Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
    m_CheckerboardTexture = ale::Texture2D::Create("assets/textures/Checkerboard.png");
    m_HoeTexture = ale::Texture2D::Create("assets/textures/Hoe.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(ale::Timestep ts)
{
    ALE_PROFILE_FUNCTION();

    //update
    {
        ALE_PROFILE_SCOPE("CameraController::OnUpdate");
        m_CameraController.OnUpdate(ts);
    }

    //render
    {
        ALE_PROFILE_SCOPE("Renderer Prep");
        ale::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        ale::RenderCommand::Clear();
    }

    {
        ALE_PROFILE_SCOPE("Renderer Draw");
        ale::Renderer2D::BeginScene(m_CameraController.GetCamera());
        ale::Renderer2D::DrawQuad({ 0.0f, 0.0f }, m_Size, m_SquareColor);
        ale::Renderer2D::DrawQuad({ 1.0f, -1.0f }, { 0.5f, 0.2f }, { 0.62f, 0.53f, 0.31, 1.0f });
        ale::Renderer2D::DrawQuad({ 0.5f, 0.5f, -0.1f }, { 1.0f, 1.0f }, m_HoeTexture, { 0.5f, 0.5f, 0.1f, 1.0f });
        ale::Renderer2D::DrawQuad({ 0.5f, 0.5f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
        ale::Renderer2D::EndScene();
    }

    //// TODO: Shader::SetMat4, Shader::SetFloat4
    //std::dynamic_pointer_cast<ale::OpenGLShader>(m_FlatColorShader)->Bind();
    //std::dynamic_pointer_cast<ale::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

}

void Sandbox2D::OnImGuiRender()
{
    ALE_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::InputFloat2("Square Size", glm::value_ptr(m_Size));
    ImGui::End();

    static ImGuiID dockspaceID = 0;
    if (ImGui::Begin("Setting Window"/*, nullptr, ImGuiWindowFlags_MenuBar*/))
    {
        ImGui::TextUnformatted("DockSpace below");

        // Declare Central dockspace
        dockspaceID = ImGui::GetID("HUB_DockSpace");
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);
    }
    ImGui::End();
}

void Sandbox2D::OnEvent(ale::Event& e)
{
    m_CameraController.OnEvent(e);
}
