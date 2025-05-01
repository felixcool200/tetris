#include <raylib.h>

#include <common.hpp>
#include <game.hpp>
#include <iostream>
#include <ranges>
#include <raylibScreen.hpp>
#include <string>

namespace {

constexpr int TILE_SIZE = 24;
constexpr int SCREEN_WIDTH =
    (tetris::BOARD_WIDTH + tetris::BORDER_LEFT + tetris::BORDER_RIGHT) * TILE_SIZE;
constexpr int SCREEN_HEIGHT =
    (tetris::BOARD_HEIGHT + tetris::BORDER_TOP + tetris::BORDER_BOTTOM) * TILE_SIZE;

// Mapping from tetris::Color to Raylib Color
Color toRaylibColor(tetris::Color color) {
    using enum tetris::Color;
    switch (color) {
        case TETROMINO_RED:
            return RED;
        case TETROMINO_GREEN:
            return GREEN;
        case TETROMINO_YELLOW:
            return YELLOW;
        case TETROMINO_BLUE:
            return BLUE;
        case TETROMINO_MAGENTA:
            return MAGENTA;
        case TETROMINO_CYAN:
            return SKYBLUE;
        case TETROMINO_WHITE:
            return RAYWHITE;
        case TETROMINO_BLACK:
            return BLACK;

        // Text colors
        case TEXT_WHITE:
            return WHITE;
        case TEXT_RED:
            return MAROON;
        case TEXT_GREEN:
            return LIME;
        case TEXT_YELLOW:
            return GOLD;
        case TEXT_BLUE:
            return DARKBLUE;  // WAS BLUE
        case TEXT_MAGENTA:
            return PURPLE;
        case TEXT_CYAN:
            return VIOLET;
        case TEXT_BLACK:
            return DARKGRAY;

        // Preview Colors
        default:
            return GRAY;
    }
}

Vector2 toScreenPos(int x, int y) {
    return {static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE)};
}
}  // namespace

tetris::Control RaylibScreen::getInput() {
    const auto key = GetKeyPressed();
    switch (key) {
        case KEY_UP:
            return tetris::Control::ROTATE;

        case KEY_DOWN:
            return tetris::Control::DOWN;

        case KEY_LEFT:
            return tetris::Control::LEFT;

        case KEY_RIGHT:
            return tetris::Control::RIGHT;
    }

    // If the X button is pressed on the window, send a quit key
    if (WindowShouldClose()) {
        return tetris::Control::QUIT;
    }

    const auto ch = GetCharPressed();
    return tetris::ControlTools::valueToEnum(static_cast<char>(ch));
}

Screen::StatusCode RaylibScreen::initScreen() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris - Raylib");
    SetTargetFPS(tetris::fps);
    return Screen::StatusCode::OKEY;
}

Screen::StatusCode RaylibScreen::closeScreen() {
    CloseWindow();
    return Screen::StatusCode::OKEY;
}

Screen::StatusCode RaylibScreen::clearScreen() {
    BeginDrawing();
    ClearBackground(BLACK);
    return Screen::StatusCode::OKEY;
}

Screen::StatusCode RaylibScreen::redrawScreen() {
    EndDrawing();
    return Screen::StatusCode::OKEY;
}

Screen::StatusCode RaylibScreen::addCharAt(char ch, int x, int y, tetris::Color color) {
    Vector2 pos = toScreenPos(x, y);
    DrawText(TextFormat("%c", ch), static_cast<int>(pos.x), static_cast<int>(pos.y), TILE_SIZE,
             toRaylibColor(color));
    return Screen::StatusCode::OKEY;
}

Screen::StatusCode RaylibScreen::addCharAtBoard(char ch, int x, int y, tetris::Color color) {
    if (Game<RaylibScreen>::isOnBoard(x, y)) {
        return addCharAt(ch, x + tetris::BORDER_LEFT, y + tetris::BORDER_TOP, color);
    }
    return Screen::StatusCode::ERROR;
}

Screen::StatusCode RaylibScreen::addStringAt(std::string_view s, int x, int y,
                                             tetris::Color color) {
    for (auto const [index, letter] : std::views::enumerate(s)) {
        addCharAt(letter, x + static_cast<int>(index), y, color);
    }
    return Screen::StatusCode::OKEY;
}

Screen::StatusCode RaylibScreen::addStringAtBoard(std::string_view s, int x, int y,
                                                  tetris::Color color) {
    if (Game<RaylibScreen>::isOnBoard(x, y)) {
        return addStringAt(s, x + tetris::BORDER_LEFT, y + tetris::BORDER_TOP, color);
    }
    return Screen::StatusCode::ERROR;
}
