#include "dave/core/engine.hpp"

#include "dave/core/event_channel.hpp"
#include "dave/core/system.hpp"

#include "sol.hpp"

#include <iostream>

namespace dave::core
{
engine::engine()
{
	event_channel::add_handler<stop_event>(this);
}

engine::~engine()
{
	event_channel::remove_handler<stop_event>(this);
}

void engine::run()
{
	scheduler.start();
}

void engine::stop()
{
	scheduler.stop();

	for (auto s : systems)
	{
		s->stop();
	}
	systems.clear();
}

void engine::add_system(std::shared_ptr<system> s,
                        bool                    repeating,
                        bool                    background)
{
	scheduler.add_task([s] { s->update(std::chrono::milliseconds{}); },
	                   repeating,
	                   background);
	systems.emplace_back(s);
}

void engine::initialise_systems()
{
	sol::state lua;
	// open some common libraries
	lua.open_libraries(sol::lib::base, sol::lib::package);
	lua.script_file("dave_config.lua");

	for (auto s: systems)
	{
		s->start(lua);
	}
}

void engine::operator()(engine::stop_event const& event)
{
	stop();
}
}
