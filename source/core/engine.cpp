#include "dave/core/engine.hpp"

#include "dave/core/event_channel.hpp"
#include "dave/core/system.hpp"

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
	s->start();
	scheduler.add_task([s] { s->update(std::chrono::milliseconds{}); },
	                   repeating,
	                   background);
	systems.emplace_back(s);
}

void engine::operator()(engine::stop_event const& event)
{
	stop();
}
}
