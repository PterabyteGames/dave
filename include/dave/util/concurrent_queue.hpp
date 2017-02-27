#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>

namespace dave::util
{

template <typename T> class concurrent_queue
{
public:
	concurrent_queue()
	{
	}

	concurrent_queue(concurrent_queue const&) = delete;
	concurrent_queue& operator=(concurrent_queue const&) = delete;

	void push(T const& item)
	{
		{
			std::lock_guard<std::mutex> lock{mutex};
			internal_queue.push(item);
		}

		condition_variable.notify_one();
	}

	void push(T&& item)
	{
		{
			std::lock_guard<std::mutex> lock{mutex};
			internal_queue.push(std::forward<T>(item));
		}

		condition_variable.notify_one();
	}

	T pop()
	{
		std::unique_lock<std::mutex> lock{mutex};
		condition_variable.wait(lock, [&] { return !internal_queue.empty(); });

		auto result = std::move(internal_queue.front());
		internal_queue.pop();
		return result;
	}

	T pop_unsafe()
	{
		auto result = std::move(internal_queue.front());
		internal_queue.pop();
		return std::move(result);
	}

	void pop(T& result)
	{
		std::unique_lock<std::mutex> lock{mutex};
		condition_variable.wait(lock,
		                        [this] { return !internal_queue.empty(); });

		result = std::move(internal_queue.front());
		internal_queue.pop();
	}

	bool try_pop(T& result)
	{
		std::lock_guard<std::mutex> lock{mutex};

		if (internal_queue.empty())
			return false;

		result = std::move(internal_queue.front());
		internal_queue.pop();

		return result;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lock{mutex};
		return internal_queue.empty();
	}

	bool empty_unsafe() const
	{
		return internal_queue.empty();
	}

	void swap(concurrent_queue& other)
	{
		std::lock_guard<std::mutex> lock_other{other.mutex};
		std::lock_guard<std::mutex> lock_self{mutex};

		std::swap(other.internal_queue, internal_queue);
	}

private:
	std::mutex              mutex;
	std::condition_variable condition_variable;

	std::queue<T> internal_queue;
};
}
