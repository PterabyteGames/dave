#include "dave/core/task.hpp"

#include <type_traits>

namespace dave
{
core::detail::wrapped_task make_task(task t, bool repeating, bool background)
{
	return core::detail::wrapped_task{std::move(t), repeating, background};
}

namespace core::detail
{
	wrapped_task::wrapped_task()
	    : t{nullptr}
	    , repeating{false}
	    , background{false}
	{
	}

	wrapped_task::wrapped_task(task t, bool repeating, bool background)
	    : t{std::move(t)}
	    , repeating{repeating}
	    , background{background}
	{
	}

	void wrapped_task::operator()() const
	{
		if (t)
		{
			t();
		}
	}

	bool wrapped_task::is_repeating() const
	{
		return repeating;
	}

	bool wrapped_task::is_background() const
	{
		return background;
	}
}
}
