#include "alePCH.h"
#include "RenderCommand.h"

#include "AALife_Engine/Platform/OpenGL/OpenGLRendererAPI.h"

namespace ale
{
    Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();

}