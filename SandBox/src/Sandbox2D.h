#pragma once

#include "AALife_Engine.h"

class Sandbox2D :public ale::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(ale::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(ale::Event& e) override;

private:
    ale::OrthographicCameraController m_CameraController;

    //temp
    ale::Ref<ale::VertexArray> m_SquareVA;
    ale::Ref<ale::Shader> m_FlatColorShader;
    ale::Ref<ale::Texture2D> m_CheckerboardTexture;
    ale::Ref<ale::Texture2D> m_HoeTexture;

    glm::vec4 m_SquareColor = { 0.71f, 0.3f, 0.43f, 1.0f};
    glm::vec2 m_Size = { 1.0f, 1.0f };


};