#include "ui.hpp"

#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

#include "common.hpp"

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void UI<screenInterface>::render(std::optional<Tetromino> hold, Tetromino next, size_t score,
                                 size_t lines, size_t level) {
    drawBorders();
    drawHold(hold);
    drawNext(next);
    drawStats(score, lines, level);
}

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void UI<screenInterface>::drawStats(size_t score, size_t lines, size_t level) {
    using namespace std::string_view_literals;
    constexpr size_t offset = tetris::BOARD_WIDTH + tetris::BORDER_LEFT + 1;
    constexpr size_t SCORE_OFFSET = 1;
    constexpr size_t LINES_OFFSET = 3;
    constexpr size_t LEVEL_OFFSET = 5;
    constexpr size_t CONTROL_OFFSET = 10;

    // Score
    screenInterface::addStringAt("Score:"sv, offset, SCORE_OFFSET);
    screenInterface::addStringAt(std::to_string(score), offset, SCORE_OFFSET + 1,
                                 tetris::Color::TEXT_CYAN);

    // Lines Cleared
    screenInterface::addStringAt("Lines:"sv, offset, LINES_OFFSET);
    screenInterface::addStringAt(std::to_string(lines), offset, LINES_OFFSET + 1,
                                 tetris::Color::TEXT_GREEN);

    // Level
    screenInterface::addStringAt("Level:"sv, offset, LEVEL_OFFSET);
    screenInterface::addStringAt(std::to_string(level), offset, LEVEL_OFFSET + 1,
                                 tetris::Color::TEXT_CYAN);

    // Control
    screenInterface::addStringAt("Control"sv, offset, CONTROL_OFFSET, tetris::Color::TEXT_RED);

    screenInterface::addStringAt("Drop:\""sv, offset, CONTROL_OFFSET + 1);
    screenInterface::addCharAt(tetris::ControlTools::enumToValue(tetris::Control::DROP), offset + 6,
                               CONTROL_OFFSET + 1);
    screenInterface::addStringAt("\"", offset + 7, CONTROL_OFFSET + 1);

    std::array<std::pair<std::string_view, tetris::Control>, 8> controls = {{
        {"Preview:"sv, tetris::Control::TOGGLE_PREVIEW},
        {"Rotate:"sv, tetris::Control::ROTATE},
        {"Left:"sv, tetris::Control::LEFT},
        {"Right:"sv, tetris::Control::RIGHT},
        {"Down:"sv, tetris::Control::DOWN},
        {"Quit:"sv, tetris::Control::QUIT},
        {"Hold"sv, tetris::Control::HOLD},
        {"Pause"sv, tetris::Control::PAUSE},
    }};

    for (auto const [index, control] : std::views::enumerate(controls)) {
        const auto yOffset = static_cast<int>(CONTROL_OFFSET + 2 + static_cast<size_t>(index));
        screenInterface::addStringAt(control.first, offset, yOffset);
        screenInterface::addCharAt(tetris::ControlTools::enumToValue(control.second), offset + 8,
                                   yOffset, tetris::Color::TEXT_YELLOW);
    }
}

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void UI<screenInterface>::drawBorders() {
    // std::string hline = std::string(BOARD_WIDTH+2, '#');
    const std::string hline =
        std::string(tetris::BOARD_WIDTH + tetris::BORDER_LEFT + tetris::BORDER_RIGHT, '#');

    screenInterface::addStringAt(hline, 0, 0);  // Top border
    screenInterface::addStringAt(
        hline, 0,
        tetris::BOARD_HEIGHT + tetris::BORDER_TOP + tetris::BORDER_BOTTOM - 1);  // Bottom border

    // Vertical Lines
    for (int i = 1; i < tetris::BOARD_HEIGHT + 1; ++i) {
        screenInterface::addCharAt('#', 0, i);                        // Left border
        screenInterface::addCharAt('#', tetris::BORDER_LEFT - 1, i);  // Left Game border
        screenInterface::addCharAt('#', (tetris::BOARD_WIDTH + tetris::BORDER_LEFT),
                                   i);  // Right Game border
        screenInterface::addCharAt(
            '#', (tetris::BOARD_WIDTH + tetris::BORDER_LEFT + tetris::BORDER_RIGHT - 1),
            i);  // Right border
    }
}

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void UI<screenInterface>::drawHold(std::optional<Tetromino> bl) {
    using namespace std::string_view_literals;
    const std::string hline = std::string(tetris::BORDER_LEFT, '#');
    screenInterface::addStringAt("Hold"sv, 1, 1);
    screenInterface::addStringAt(hline, 0, tetris::SHAPESIZE + 3);
    // screenInterface::addStringAt(screen,hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1);
    if (!bl) {
        return;
    }
    // This makes the blocks look better in the holding space
    if (bl->getShape() == Tetromino::Shape::I) {
        bl->rotateRight();
    }
    bl->rotateRight();
    bl->render<screenInterface>(std::pair(1, 2));
}

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void UI<screenInterface>::drawNext(Tetromino bl) {
    const std::string hline = std::string(tetris::BORDER_LEFT, '#');
    screenInterface::addStringAt("Next", 1, 1 + tetris::SHAPESIZE + 3);
    screenInterface::addStringAt(hline, 0, 2 * (tetris::SHAPESIZE + 3));

    // This makes the blocks look better in the holding space
    if (bl.getShape() == Tetromino::Shape::I) {
        bl.rotateRight();
    }
    bl.rotateRight();
    bl.render<screenInterface>(std::pair(1, 2 + tetris::SHAPESIZE + 3));
}

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void UI<screenInterface>::renderPauseScreen(size_t score, size_t lines, size_t level) {
    using namespace std::string_view_literals;
    drawBorders();
    constexpr std::array<std::string_view, 2> message = {{"Game is"sv, "paused"sv}};
    for (auto const [index, text] : std::views::enumerate(message)) {
        const auto x = tetris::BORDER_LEFT + (tetris::BOARD_WIDTH - text.length()) / 2;
        const auto y = tetris::BORDER_TOP + tetris::BOARD_HEIGHT / 2 + index;
        screenInterface::addStringAt(text, static_cast<int>(x), static_cast<int>(y));
    }
    drawStats(score, lines, level);
}

#include "screenTypeSelector.hpp"
template class UI<ScreenType>;