#include "dave/core/platform.hpp"

#include <GLFW/glfw3.h>

namespace dave::platform
{
void init()
{
	glfwInit();
}

void poll_events()
{
	glfwPollEvents();
}

void deinit()
{
	glfwTerminate();
}
}
