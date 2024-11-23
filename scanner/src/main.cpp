/**
 * @file main.cpp
 * @brief Entry point for the scanner application.
 */

#include "app.hpp"

int main(int argc, char *argv[]) {
    // Create an App object and run the application
    try {
        TINY::SCANNER::App app(argc, argv);
        app.run();
    } catch (std::exception &e) {
        // set color to red
        std::cout << "\033[1;31m";
        std::cerr << "Error: " << e.what() << std::endl;
        // reset
        std::cout << "\033[0m";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}