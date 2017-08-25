#pragma once

#include "dave/core/platform.hpp"
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
	DAVEAPI engine();
	DAVEAPI ~engine();

	DAVEAPI void run();
	DAVEAPI void stop();

	DAVEAPI void add_system(std::shared_ptr<system> s, bool repeating, bool background);
	DAVEAPI void initialise_systems();

	struct stop_event
	{
	};

	void operator()(stop_event const& event);

	template <typename Function>
	DAVEAPI void add_job(Function&& function, bool repeating, bool background)
	{
		scheduler.add_task(std::move(function), repeating, background);
	}

private:
	task_scheduler scheduler;

	std::vector<std::shared_ptr<system>> systems;
};
}
