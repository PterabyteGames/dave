#pragma once

#include "dave/core/platform.hpp"

#include <string>

namespace dave::video
{
class window
{
public:
	struct events
	{
		struct create_event
		{
			window* w;
		};

		struct destroy_event
		{
			window* w;
		};
	};

public:
	window(int width, int height, std::string const& title);
	DAVEAPI ~window();

	window(window&& w);
	window& operator=(window&& w);

	// disable copying
	window(window const&) = delete;
	window& operator=(window const&) = delete;

public:
	bool should_close();

	void make_current();
	void swap_buffers();

	native_window_handle get_native_handle();

private:
	int width;
	int height;

	std::string title;

	native_window_handle handle;
};
}
