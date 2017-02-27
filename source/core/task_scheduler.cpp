#include "dave/core/task_scheduler.hpp"

#include <exception>
#include <iostream>
#include <string>

namespace dave::core
{
namespace
{
	struct thread_stop : std::exception
	{
		char const* what() const noexcept override
		{
			return "Stopping thread";
		}
	};
}

task_scheduler::task_scheduler(std::size_t num_threads)
    : running{false}
{
	if (num_threads == 0)
	{
		num_threads = std::thread::hardware_concurrency() - 1;
	}

	if (num_threads < 1)
	{
		num_threads = 1;
	}

	threads.resize(num_threads);

	std::cout << " Using " << num_threads << " threads" << std::endl;
}

task_scheduler::~task_scheduler()
{
	for (auto&& thread : threads)
	{
		if (thread.joinable())
			thread.join();
	}
}

void task_scheduler::add_task(task t, bool repeating, bool background)
{
	auto wrapped = make_task(t, repeating, background);
	add_wrapped_task(wrapped);
}

void task_scheduler::start()
{
	if (running)
		return;

	running = true;

	for (auto& thread : threads)
	{
		thread = std::thread([this] {
			while (true)
			{
				try
				{
					auto t = std::move(background_tasks.pop());
					execute(t);
					std::this_thread::yield();
				}
				catch (thread_stop const& exception)
				{
					std::cout << exception.what() << std::endl;
					break;
				}
			}
		});
	}

	while (running)
	{
		task_queue local_tasks;
		main_tasks.swap(local_tasks);

		while (!local_tasks.empty_unsafe())
		{
			auto t = std::move(local_tasks.pop_unsafe());
			execute(t);
		}
		std::this_thread::yield();
	}
}

void task_scheduler::stop()
{
	running = false;
	for (auto& thread : threads)
	{
		add_task([] { throw thread_stop{}; }, false, true);
	}
}

void task_scheduler::add_wrapped_task(detail::wrapped_task t)
{
	if (t.is_background())
	{
		background_tasks.push(std::move(t));
	}
	else
	{
		main_tasks.push(std::move(t));
	}
}

void task_scheduler::execute(detail::wrapped_task t)
{
	t();

	if (t.is_repeating())
	{
		add_wrapped_task(std::move(t));
	}
}
}
