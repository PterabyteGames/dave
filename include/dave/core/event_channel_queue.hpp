#pragma once

#include <algorithm>
#include <mutex>
#include <vector>

#include <cstdint>

namespace dave::core
{
template <typename Message> class event_channel_queue
{
private:
	event_channel_queue()
	{
	}

public:
	static event_channel_queue& instance()
	{
		static event_channel_queue queue;
		return queue;
	}

	template <typename Handler> void add(Handler* handler)
	{
		std::lock_guard<std::mutex> lock{mutex};
		handlers.push_back(
		    [handler](Message const& message) { (*handler)(message); });

		original_pointers.push_back(handler);
	}

	template <typename Handler> void remove(Handler* handler)
	{
		std::lock_guard<std::mutex> lock{mutex};

		auto const iterator = std::find(std::cbegin(original_pointers),
		                                std::cend(original_pointers),
		                                static_cast<void*>(handler));

		if (iterator == std::cend(original_pointers))
		{
			throw std::runtime_error{"Trying to remove non-existent handler"};
		}

		auto index = iterator - std::cbegin(original_pointers);

		handlers.erase(std::cbegin(handlers) + index);
		original_pointers.erase(iterator);
	}

	void remove_all()
	{
		std::lock_guard<std::mutex> lock{mutex};

		handlers.clear();
		original_pointers.clear();
	}

	std::size_t get_num_handlers() const
	{
		std::lock_guard<std::mutex> lock{mutex};
		return handlers.size();
	}

	void broadcast(Message const& message)
	{
		std::vector<Handler> local_queue{handlers.size()};
		{
			std::lock_guard<std::mutex> lock{mutex};
			local_queue = handlers;
		}

		for (auto& handler : local_queue)
		{
			handler(message);
		}
	}

private:
	using Handler = std::function<void(Message const&)>;

	std::mutex mutex;

	std::vector<Handler> handlers;
	std::vector<void*>   original_pointers;
};
}
