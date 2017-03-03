#include "dave/video/window.hpp"

#include "dave/core/event_channel.hpp"

#include <GLFW/glfw3.h>

namespace dave::video
{
namespace
{
}

window::window(int width, int height, std::string const& title)
    : width{width}
    , height{height}
    , title{title}
{
	handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(handle, this);

	core::event_channel::broadcast<events::create_event>(
	    events::create_event{this});
}

window::~window()
{
	if (handle)
	{
		glfwDestroyWindow(handle);
		core::event_channel::broadcast<events::destroy_event>(
		    events::destroy_event{this});
	}
}

window::window(window&& w)
    : width{std::move(w.width)}
    , height{std::move(w.height)}
    , title{std::move(w.title)}
    , handle{std::move(handle)}
{
	w.handle = nullptr;

	if (handle)
	{
		glfwSetWindowUserPointer(handle, this);
	}

	core::event_channel::broadcast<events::create_event>(
	    events::create_event{this});
}

window& window::operator=(window&& w)
{
	if (handle)
	{
		glfwDestroyWindow(handle);
	}

	width    = std::move(w.width);
	height   = std::move(w.height);
	title    = std::move(w.title);
	handle   = std::move(handle);
	w.handle = nullptr;

	if (handle)
	{
		glfwSetWindowUserPointer(handle, this);
	}

	core::event_channel::broadcast<events::create_event>(
	    events::create_event{this});

	return *this;
}

bool window::should_close()
{
	return glfwWindowShouldClose(handle);
}

void window::make_current()
{
	glfwMakeContextCurrent(handle);
}

void window::swap_buffers()
{
	glfwSwapBuffers(handle);
}

native_window_handle window::get_native_handle()
{
	return handle;
}
}
