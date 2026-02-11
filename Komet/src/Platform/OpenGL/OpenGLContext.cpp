#include "kmpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>


namespace Komet {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		KM_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KM_CORE_ASSERT(status, "Failed to initialize Glad!");

		KM_CORE_INFO("OpenGL Info:");
		KM_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		KM_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		KM_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}