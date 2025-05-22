#include <catch2/catch_test_macros.hpp>
#include <optional>
#include <string>
#include <vector>

#include "mockScreen.hpp"
#include "tetromino.hpp"
#include "ui.hpp"

TEST_CASE("UI::drawBorders draws all borders", "[ui][borders]") {
    Screen::MockScreen::reset();
    UI<Screen::MockScreen>::drawBorders();
    CHECK(Screen::MockScreen::countChar('#') > 0);
}

TEST_CASE("UI::drawStats draws score, lines, and level", "[ui][stats]") {
    Screen::MockScreen::reset();
    size_t score = 123, lines = 45, level = 6;
    UI<Screen::MockScreen>::drawStats(score, lines, level);

    CHECK(Screen::MockScreen::wasStringDrawn("Score:"));
    CHECK(Screen::MockScreen::wasStringDrawn("Lines:"));
    CHECK(Screen::MockScreen::wasStringDrawn("Level:"));
    CHECK(Screen::MockScreen::wasStringDrawn(std::to_string(score)));
    CHECK(Screen::MockScreen::wasStringDrawn(std::to_string(lines)));
    CHECK(Screen::MockScreen::wasStringDrawn(std::to_string(level)));
}

TEST_CASE("UI::drawHold draws hold box and tetromino if present", "[ui][hold]") {
    Screen::MockScreen::reset();
    UI<Screen::MockScreen>::drawHold(std::nullopt);
    CHECK(Screen::MockScreen::wasStringDrawn("Hold"));
    // TODO: Check that tetromino was drawn on the correct location.
    // CHECK(Screen::MockScreen::wasTetrominoDrawn());

    Screen::MockScreen::reset();
    Tetromino t(Tetromino::Shape::O);
    UI<Screen::MockScreen>::drawHold(t);
    // TODO: Check that tetromino was drawn on the correct location
    // CHECK(Screen::MockScreen::wasTetrominoDrawn());
}

TEST_CASE("UI::render calls all draw functions", "[ui][render]") {
    Screen::MockScreen::reset();
    Tetromino next(Tetromino::Shape::S);
    std::optional<Tetromino> hold = Tetromino(Tetromino::Shape::Z);
    size_t score = 10, lines = 2, level = 1;
    UI<Screen::MockScreen>::render(hold, next, score, lines, level);

    CHECK(Screen::MockScreen::wasStringDrawn("Hold"));
    CHECK(Screen::MockScreen::wasStringDrawn("Next"));
    CHECK(Screen::MockScreen::wasStringDrawn("Score:"));
    // TODO: Check that tetromino was drawn on the correct location
    // CHECK(Screen::MockScreen::wasTetrominoDrawn());
}

TEST_CASE("UI::renderPauseScreen draws pause message and stats", "[ui][pause]") {
    Screen::MockScreen::reset();
    size_t score = 5, lines = 1, level = 0;
    UI<Screen::MockScreen>::renderPauseScreen(score, lines, level);

    CHECK(Screen::MockScreen::wasStringDrawn("Game is"));
    CHECK(Screen::MockScreen::wasStringDrawn("paused"));
    CHECK(Screen::MockScreen::wasStringDrawn("Score:"));
    CHECK(Screen::MockScreen::wasStringDrawn("Lines:"));
    CHECK(Screen::MockScreen::wasStringDrawn("Level:"));
}
namespace holdAndNextBoxes {

// Helper to print all drawn chars for debugging
void printDrawnChars() {
    std::ostringstream oss;
    oss << "drawnChars: [";
    for (const auto& [ch, x, y] : Screen::MockScreen::drawnChars) {
        oss << "('" << ch << "', " << x - 1 << ", " << y - 9 << "), ";
    }
    oss << "]";
    UNSCOPED_INFO(oss.str());
}

// Helper function to check that a tetromino is drawn at expected positions in the "Next" box
void checkTetrominoDrawnInNextBox(const std::vector<std::pair<int, int>>& expectedOffsets) {
    constexpr size_t baseX = 1;  // X coordinate where the "Next" box starts
    constexpr size_t baseY = 9;  // Y coordinate where the "Next" box starts
    for (const auto& [dx, dy] : expectedOffsets) {
        INFO("Checking for 'B' at (" << (baseX + dx) << ", " << (baseY + dy) << ")");
        printDrawnChars();
        CHECK(Screen::MockScreen::wasCharDrawnAt('B', baseX + dx, baseY + dy));
    }
}

// Helper function to check that a tetromino is drawn at expected positions in the "Hold" box
void checkTetrominoDrawnInHoldBox(const std::vector<std::pair<int, int>>& expectedOffsets) {
    constexpr size_t baseX = 1;  // X coordinate where the "Hold" box starts
    constexpr size_t baseY = 2;  // Y coordinate where the "Hold" box starts
    for (const auto& [dx, dy] : expectedOffsets) {
        INFO("Checking for 'B' at (" << (baseX + dx) << ", " << (baseY + dy) << ")");
        printDrawnChars();
        CHECK(Screen::MockScreen::wasCharDrawnAt('B', baseX + dx, baseY + dy));
    }
}

struct TetrominoTestCase {
    Tetromino::Shape shape;
    std::vector<std::pair<int, int>> offsets;
    const std::string tag;
};

const std::vector<TetrominoTestCase> tetrominoTestCases = {
    {Tetromino::Shape::O, {{1, 1}, {2, 1}, {1, 2}, {2, 2}}, "[O]"},
    {Tetromino::Shape::I, {{0, 2}, {1, 2}, {2, 2}, {3, 2}}, "[I]"},
    {Tetromino::Shape::S, {{1, 2}, {1, 3}, {2, 1}, {2, 2}}, "[S]"},
    {Tetromino::Shape::Z, {{1, 1}, {1, 2}, {2, 2}, {2, 3}}, "[Z]"},
    {Tetromino::Shape::L, {{2, 1}, {2, 2}, {1, 3}, {2, 3}}, "[L]"},
    {Tetromino::Shape::J, {{1, 1}, {2, 1}, {2, 2}, {2, 3}}, "[J]"},
    {Tetromino::Shape::T, {{2, 1}, {1, 2}, {2, 2}, {2, 3}}, "[T]"},
};

TEST_CASE("UI::drawNext and drawHold draw all tetrominoes in correct positions",
          "[ui][next][hold]") {
    for (const auto& test : tetrominoTestCases) {
        DYNAMIC_SECTION("Shape " << test.tag) {
            Tetromino t(test.shape);

            // Test drawNext
            Screen::MockScreen::reset();
            UI<Screen::MockScreen>::drawNext(t);
            CHECK(Screen::MockScreen::wasStringDrawn("Next"));
            checkTetrominoDrawnInNextBox(test.offsets);

            // Test drawHold
            Screen::MockScreen::reset();
            UI<Screen::MockScreen>::drawHold(t);
            CHECK(Screen::MockScreen::wasStringDrawn("Hold"));
            checkTetrominoDrawnInHoldBox(test.offsets);
        }
    }
}
}  // namespace holdAndNextBoxes