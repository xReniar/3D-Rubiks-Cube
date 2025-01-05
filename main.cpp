#include"src/Rubiks.hpp"

auto main() -> int{
    CubeApp app{};

    try {
        app.run();
    } catch(const std::exception &error) {
        std::cerr << error.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}