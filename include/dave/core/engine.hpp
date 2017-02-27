#pragma once

#include "dave/core/system.hpp"

#include "dave/core/task_scheduler.hpp"

#include <memory>
#include <vector>

namespace dave::core
{
class system;

class engine
{
public:
	engine();
	~engine();

	void run();
	void stop();

	void add_system(std::shared_ptr<system> s, bool repeating, bool background);

	struct stop_event
	{
	};

	void operator()(stop_event const& event);

	template <typename Function>
	void add_job(Function&& function, bool repeating, bool background)
	{
		scheduler.add_task(std::move(function), repeating, background);
	}

private:
	task_scheduler scheduler;

	std::vector<std::shared_ptr<system>> systems;
};
}
