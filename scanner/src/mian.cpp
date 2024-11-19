/**
 * @file main.cpp
 * @brief Entry point for the scanner application.
 */

#include "app.hpp"

int main(int argc, char *argv[]) {
    // Create an App object and run the application
    try {
        App app(argc, argv);
        app.run();
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}