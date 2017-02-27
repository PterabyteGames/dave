#pragma once

#include "dave/core/task.hpp"
#include "dave/util/concurrent_queue.hpp"

#include <cstdint>
#include <thread>
#include <vector>

namespace dave::core
{
class task_scheduler
{
	using task_queue = util::concurrent_queue<detail::wrapped_task>;

public:
	task_scheduler(std::size_t num_threads = 0);
	task_scheduler(task_scheduler const&)  = delete;
	task_scheduler(task_scheduler&&)       = delete;
	task_scheduler operator=(task_scheduler const&) = delete;
	task_scheduler operator=(task_scheduler&&) = delete;
	~task_scheduler();

	void add_task(task t, bool repeating, bool background);

	void start();
	void stop();

private:
	void add_wrapped_task(detail::wrapped_task t);
	void execute(detail::wrapped_task task);

	task_queue main_tasks;
	task_queue background_tasks;

	bool        running;
	std::size_t num_threads;

	std::vector<std::thread> threads;
};
}
