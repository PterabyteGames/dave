#pragma once

#include "dave/core/platform.hpp"

#include <functional>

namespace dave
{
using task = std::function<void()>;

namespace core
{
	class task_scheduler;

	namespace detail
	{
		class wrapped_task;
	}
}

core::detail::wrapped_task make_task(task t, bool repeating, bool background);

namespace core::detail
{
	class wrapped_task
	{
	private:
		friend core::detail::wrapped_task
		dave::make_task(task t, bool repeating, bool background);

		friend class dave::core::task_scheduler;

		wrapped_task();
		wrapped_task(task t, bool repeating, bool background);

	public:
		void operator()() const;

	private:
		bool is_repeating() const;
		bool is_background() const;

	private:
		task t;
		bool repeating;
		bool background;
	};
}
}
