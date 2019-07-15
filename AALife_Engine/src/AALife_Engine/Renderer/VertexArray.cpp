#include "alePCH.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "AALife_Engine/Platform/OpenGL/OpenGLVertexArray.h"

namespace ale{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ALE_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}
		ALE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}

