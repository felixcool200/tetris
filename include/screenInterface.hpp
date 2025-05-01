#pragma once
#include <common.hpp>
#include <concepts>

namespace Screen {

enum class StatusCode {
    ERROR = -1,
    OKEY = 0,
};

template <typename screenInterface>
concept ScreenInterface = requires(int x, int y, char ch, std::string_view s, tetris::Color color) {
    // Method to configure and start the screen
    { screenInterface::initScreen() } -> std::same_as<StatusCode>;
    { screenInterface::closeScreen() } -> std::same_as<StatusCode>;

    // Method for handling user input
    { screenInterface::getInput() } -> std::same_as<tetris::Control>;

    // Methods for clearing and redrawing the screen
    { screenInterface::clearScreen() } -> std::same_as<StatusCode>;
    { screenInterface::redrawScreen() } -> std::same_as<StatusCode>;

    // Methods for adding characters to the screen
    { screenInterface::addCharAt(ch, x, y, color) } -> std::same_as<StatusCode>;
    { screenInterface::addCharAtBoard(ch, x, y, color) } -> std::same_as<StatusCode>;

    // Methods for adding strings to the screen
    { screenInterface::addStringAt(s, x, y, color) } -> std::same_as<StatusCode>;
    { screenInterface::addStringAtBoard(s, x, y, color) } -> std::same_as<StatusCode>;
};

// Example of using the concept
template <ScreenInterface T>
void testScreenFunctions() {
    using namespace std::string_view_literals;
    T::initScreen();
    T::clearScreen();
    T::addCharAt('A', 5, 5, tetris::Color::TEXT_BLACK);
    T::addCharAtBoard('B', 10, 10, tetris::Color::TEXT_GREEN);
    T::addStringAt("Hello"sv, 15, 15, tetris::Color::TEXT_MAGENTA);
    T::addStringAtBoard("World"sv, 20, 20, tetris::Color::TEXT_CYAN);
    T::redrawScreen();
}
}  // namespace Screen