#pragma once

#include "event_channel_queue.hpp"

#include <cstdint>

namespace dave::core
{
struct event_channel
{
	template <typename Message, typename Handler>
	static void add_handler(Handler* handler)
	{
		event_channel_queue<Message>::instance().add(handler);
	}

	template <typename Message, typename Handler>
	static void remove_handler(Handler* handler)
	{
		event_channel_queue<Message>::instance().remove(handler);
	}

	template <typename Message> static void remove_all()
	{
		event_channel_queue<Message>::instance().remove_all();
	}

	template <typename Message> static std::size_t get_num_handlers()
	{
		return event_channel_queue<Message>::instance().get_num_handlers();
	}

	template <typename Message> static void broadcast(Message const& message)
	{
		event_channel_queue<Message>::instance().broadcast(message);
	}
};
}
