#pragma once

#include "dave/core/platform.hpp"

#include "sol.hpp"

#include <chrono>
#include <string>

namespace dave::core
{
class engine;

class system
{
public:
	DAVEAPI virtual ~system();

protected:
	friend class engine;

	system(std::string const& name);

	virtual void start(sol::state const& lua_state)      = 0;
	virtual void update(std::chrono::milliseconds delta) = 0;
	virtual void stop()                                  = 0;

	virtual std::string get_name() const;

private:
	std::string const name;
};

template<typename T, typename... Args>
DAVEAPI std::shared_ptr<system> make_system(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}
}
