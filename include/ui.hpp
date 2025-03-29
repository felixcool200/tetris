#pragma once

#include "tetromino.hpp"

#include <optional>

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>  // Ensure Screen implements the required interface
class UI {
    public:
        static void drawHold(std::optional<Tetromino<screenInterface>> hold);
        static void drawNext(Tetromino<screenInterface> next);
        static void drawBorders();
        static void draw(std::optional<Tetromino<screenInterface>> hold, Tetromino<screenInterface> next, unsigned int score, unsigned int lines, unsigned int level);
        static void drawStats(unsigned int score, unsigned int lines, unsigned int level);
};
