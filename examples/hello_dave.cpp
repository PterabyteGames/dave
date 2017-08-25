#include <dave/core/engine.hpp>
#include <dave/video/video.hpp>

int main(int argc, char const *argv[])
{
    dave::core::engine engine{};
    engine.add_system(dave::core::make_system<dave::video::video>(), true, false);
    engine.initialise_systems();
    engine.run();

    return 0;
}
