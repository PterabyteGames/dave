#pragma once

#include <chrono>
#include <string>

namespace dave::core
{
class system
{
public:
	system(std::string const& name);
	virtual ~system();

	virtual void start()                                 = 0;
	virtual void update(std::chrono::milliseconds delta) = 0;
	virtual void stop()                                  = 0;

	virtual std::string get_name() const;

private:
	std::string const name;
};
}
