#include "dave/video/video.hpp"

#include "dave/core/engine.hpp"
#include "dave/core/event_channel.hpp"
#include "dave/core/platform.hpp"

#include "glad.h"
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

void video::start(sol::state const& lua_state)
{
	platform::init();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	auto window_config = lua_state.get<sol::table>("window");

	int         width  = window_config["width"].get_or(800);
	int         height = window_config["height"].get_or(600);
	std::string title  = window_config["title"].get_or(std::string{"demo"});

	main_window = std::make_unique<window>(width, height, title.c_str());
	main_window->make_current();
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSetKeyCallback(main_window->get_native_handle(), key_callback);
	glfwGetFramebufferSize(main_window->get_native_handle(), &width, &height);

	glViewport(0, 0, width, height);
}

void video::update(std::chrono::milliseconds delta)
{
	if (!main_window->should_close())
	{
		platform::poll_events();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		main_window->swap_buffers();
	}
}

void video::stop()
{
	platform::deinit();
}
}
