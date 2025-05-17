#pragma once

#include <array>
#include <cctype>  // For std::tolower
#include <chrono>
#include <stdexcept>

namespace tetris {

enum class Direction {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
};

enum class Color {
    NONE,
    TETROMINO_BLACK,
    TETROMINO_YELLOW,
    TETROMINO_CYAN,
    TETROMINO_GREEN,
    TETROMINO_RED,
    TETROMINO_WHITE,
    TETROMINO_BLUE,
    TETROMINO_MAGENTA,
    TEXT_BLACK,
    TEXT_YELLOW,
    TEXT_CYAN,
    TEXT_GREEN,
    TEXT_RED,
    TEXT_WHITE,
    TEXT_BLUE,
    TEXT_MAGENTA,
    PREVIEW_YELLOW,
    PREVIEW_CYAN,
    PREVIEW_GREEN,
    PREVIEW_RED,
    PREVIEW_WHITE,
    PREVIEW_BLUE,
    PREVIEW_MAGENTA,
    PREVIEW_GREY,
};

namespace ColorTools {
constexpr std::array<std::pair<short, Color>, 25> colorMappings = {{
    {-1, Color::NONE},           {0, Color::TETROMINO_BLACK}, {1, Color::TETROMINO_YELLOW},
    {2, Color::TETROMINO_CYAN},  {3, Color::TETROMINO_GREEN}, {4, Color::TETROMINO_RED},
    {5, Color::TETROMINO_WHITE}, {6, Color::TETROMINO_BLUE},  {7, Color::TETROMINO_MAGENTA},
    {8, Color::TEXT_BLACK},      {9, Color::TEXT_YELLOW},     {10, Color::TEXT_CYAN},
    {11, Color::TEXT_GREEN},     {12, Color::TEXT_RED},       {13, Color::TEXT_WHITE},
    {14, Color::TEXT_BLUE},      {15, Color::TEXT_MAGENTA},   {16, Color::PREVIEW_YELLOW},
    {17, Color::PREVIEW_CYAN},   {18, Color::PREVIEW_GREEN},  {19, Color::PREVIEW_RED},
    {20, Color::PREVIEW_WHITE},  {21, Color::PREVIEW_BLUE},   {22, Color::PREVIEW_MAGENTA},
    {23, Color::PREVIEW_GREY},
}};

// Short-to-Enum conversion
constexpr Color valueToEnum(short toFind) {
    for (const auto& [key, element] : colorMappings) {
        if (key == toFind) return element;
    }
    return Color::NONE;
    // throw std::invalid_argument("Invalid input to converter");
}

// Enum-to-Short conversion
constexpr short enumToValue(Color toFind) {
    for (const auto& [key, element] : colorMappings) {
        if (element == toFind) return key;
    }
    throw std::invalid_argument("Invalid input to converter");
}

}  // namespace ColorTools

enum class Control {
    NONE,
    PAUSE,
    QUIT,
    HOLD,
    TOGGLE_PREVIEW,
    ROTATE,
    DROP,
    LEFT,
    RIGHT,
    DOWN,
};

namespace ControlTools {

constexpr Direction controlToDirection(const tetris::Control keyPressed) {
    switch (keyPressed) {
        case Control::ROTATE:
            return Direction::UP;
        case Control::RIGHT:
            return Direction::RIGHT;
        case Control::DOWN:
            return Direction::DOWN;
        case Control::LEFT:
            return Direction::LEFT;
        default:
            return Direction::UP;
    }
}
// Character map
constexpr std::array<std::pair<char, Control>, 10> controlMappings = {{
    {'\0', Control::NONE},
    {'b', Control::PAUSE},
    {'q', Control::QUIT},
    {'c', Control::HOLD},
    {'p', Control::TOGGLE_PREVIEW},
    {' ', Control::DROP},
    {'w', Control::ROTATE},
    {'a', Control::LEFT},
    {'s', Control::DOWN},
    {'d', Control::RIGHT},
}};

// Char-to-Enum conversion
constexpr Control valueToEnum(char toFind) {
    for (const auto& [key, element] : controlMappings) {
        if (key == std::tolower(toFind)) return element;
    }
    return Control::NONE;
}

// Enum-to-Short conversion
constexpr char enumToValue(Control toFind) {
    for (const auto& [key, element] : controlMappings) {
        if (element == toFind) return key;
    }
    throw std::invalid_argument("Invalid input to converter");
}

}  // namespace ControlTools

//========== UI ==========
constexpr int BOARD_WIDTH = 10;
constexpr int BOARD_HEIGHT = 20;
constexpr int START_DELAY_FRAMES = 60;
constexpr int UI_WIDTH = 0;
constexpr int UI_HEIGHT = 0;
constexpr int BORDER_TOP = 1;
constexpr int BORDER_LEFT = 6;
constexpr int BORDER_BOTTOM = 1;
constexpr int BORDER_RIGHT = 11;

//========== DeltaTime ==========
constexpr auto frameDuration = std::chrono::duration<double>(1.0 / 120);
constexpr auto fps = 1 / tetris::frameDuration.count();

//========== Game logic ==========
constexpr int MAX_LEVEL = 29;

constexpr int SHAPESIZE = 4;

}  // namespace tetris