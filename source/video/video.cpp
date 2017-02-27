#include "dave/video/video.hpp"

#include "dave/core/engine.hpp"
#include "dave/core/event_channel.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace dave::video
{
void key_callback(GLFWwindow* window,
                  int         key,
                  int         scancode,
                  int         action,
                  int         mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);

		using stop_event = dave::core::engine::stop_event;
		dave::core::event_channel::broadcast<stop_event>(stop_event{});
	}
}

video::video()
    : core::system{"Video System"}
{
}

void video::start()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(800, 600, "demo", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSetKeyCallback(window, key_callback);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
}

void video::update(std::chrono::milliseconds delta)
{
	if (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}
}

void video::stop()
{
	glfwTerminate();
}
}
