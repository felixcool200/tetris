#pragma once

#include <optional>

#include "tetromino.hpp"

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
class UI {
   public:
    static void drawHold(std::optional<Tetromino<screenInterface>> hold);
    static void drawNext(Tetromino<screenInterface>& next);
    static void drawBorders();
    static void render(std::optional<Tetromino<screenInterface>> hold,
                       Tetromino<screenInterface> next, size_t score, size_t lines, size_t level);
    static void drawStats(size_t score, size_t lines, size_t level);
    static void renderPauseScreen(size_t score, size_t lines, size_t level);
};
