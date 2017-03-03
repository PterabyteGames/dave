#pragma once

#include "dave/core/system.hpp"
#include "dave/video/window.hpp"

#include <memory>

struct GLFWwindow;

namespace dave::video
{
class video : public core::system
{
public:
	video();
	virtual ~video() = default;

	void start(sol::state const& lua_state) override;
	void update(std::chrono::milliseconds delta) override;
	void stop() override;

private:
	std::unique_ptr<window> main_window;
};
}
