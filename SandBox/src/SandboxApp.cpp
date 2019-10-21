#include <AALife_Engine.h>
#include <AALife_Engine/Core/EntryPoint.h>

#include "AALife_Engine/Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"


class ExampleLayer : public ale::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = ale::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f,  0.0f,   0.8f,  0.2f,   0.2f,  1.0f,
			 0.5f, -0.5f,  0.0f, 0.001f,  0.95f,  0.05f, 1.0f,
			 0.0f,  0.5f,  0.0f,  0.05f,  0.0f,   0.8f,  1.0f,
		};

        ale::Ref<ale::VertexBuffer> vertexBuffer;

		vertexBuffer.reset(ale::VertexBuffer::Create(vertices, sizeof(vertices)));
		ale::BufferLayout layout = {
			{ale::ShaderDataType::Float3, "a_Position" },
			{ale::ShaderDataType::Float4, "a_Color"    },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
        ale::Ref<ale::IndexBuffer> indexBuffer;
		indexBuffer.reset(ale::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = ale::VertexArray::Create();

		float squareVertices[5 * 4] = {
		    -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		     0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		     0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		    -0.5f,  0.5f,  0.0f, 0.0f, 1.0f
		};

        ale::Ref<ale::VertexBuffer> squareVB;
		squareVB.reset(ale::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ale::ShaderDataType::Float3, "a_Position" },
            {ale::ShaderDataType::Float2, "a_TexCoord" },
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0 ,1 , 2, 2, 3, 0 };
        ale::Ref<ale::IndexBuffer> squareIB;
		squareIB.reset(ale::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position , 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec4 v_Color;			

			void main()
			{	
				color = v_Color;
			}
		)";

        m_Shader = ale::Shader::Create("VetexPosColor" ,vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position , 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;		
            
            uniform vec3 u_Color;

			void main()
			{	
				color = vec4(u_Color, 1.0);
			}
		)";


		m_FlatColorShader = ale::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

        auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

        m_Texture = ale::Texture2D::Create("assets/textures/Checkerboard.png");
        m_LogoTexture = ale::Texture2D::Create("assets/textures/Hoe.png");
        

        std::dynamic_pointer_cast<ale::OpenGLShader>(textureShader)->Bind();
        std::dynamic_pointer_cast<ale::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	
	void OnUpdate(ale::Timestep ts) override
	{
		//ALE_TRACE("Delta time: {0}s ({1}ms)", ts.GeySecond(), ts.GetMillisecond());
        m_CameraController.OnUpdate(ts);

		ale::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ale::RenderCommand::Clear();

		ale::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<ale::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<ale::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++)
			{

				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				ale::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

        auto textureShader = m_ShaderLibrary.Get("Texture");

        m_Texture->Bind();
        ale::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        m_LogoTexture->Bind();
        ale::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        // triangle
        //ale::Renderer::Submit(m_Shader, m_VertexArray);

		ale::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();

        bool my_tool_active;
        ImGui::Begin("My First Tool");
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
                if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // Edit a color (stored as ~4 floats)
        ImGui::ColorEdit4("Color", glm::value_ptr(m_SquareColor));

        // Plot some values
        const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
        ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

        // Display contents in a scrolling region
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
        ImGui::BeginChild("Scrolling");
        for (int n = 0; n < 50; n++)
            ImGui::Text("%04d: Some text", n);
        ImGui::EndChild();
        ImGui::End();
	}

	void OnEvent(ale::Event& e) override
	{
        m_CameraController.OnEvent(e);
	}

private:
    ale::ShaderLibrary m_ShaderLibrary;
	ale::Ref<ale::Shader> m_Shader;
    ale::Ref<ale::VertexArray> m_VertexArray;

	ale::Ref<ale::Shader> m_FlatColorShader;
	ale::Ref<ale::VertexArray> m_SquareVA;

    ale::Ref<ale::Texture2D> m_Texture, m_LogoTexture;

	ale::OrthographicCameraController m_CameraController;
	//glm::vec3 m_CameraPosition;
	//float m_CameraMoveSpeed = -5.0f; // per second
	//float m_CameraRotation = 0.0f;
	//float m_CameraRotationSpeed = 180.0f; //per secod

    glm::vec3 m_SquareColor = { 0.71f, 0.3f, 0.43f };

};



class Sandbox : public ale::Application
{
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
	}

	~Sandbox() {
		 
	}
};


ale::Application* ale::CreateApplication()
{
	return new Sandbox();
}