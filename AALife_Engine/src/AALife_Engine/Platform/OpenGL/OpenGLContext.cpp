#include "alePCH.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include <gl/GL.h>

namespace ale {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ALE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		//ALE_CORE_ASSERT(status, "Failed to initialize Glad!");

		ALE_INFO("OpenGL iNFO:");
		ALE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		ALE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		ALE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}