#include "dave/core/system.hpp"

namespace dave::core
{
system::system(std::string const& name)
    : name{name}
{
}

system::~system()
{
}

std::string system::get_name() const
{
	return name;
}
}
