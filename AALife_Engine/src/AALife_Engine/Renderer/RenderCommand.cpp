#include "alePCH.h"
#include "RenderCommand.h"

#include "AALife_Engine/Platform/OpenGL/OpenGLRendererAPI.h"

namespace ale
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}