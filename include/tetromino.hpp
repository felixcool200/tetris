#pragma once

#include <array>
#include <optional>

#include "common.hpp"
#include "screenInterface.hpp"

class Tetromino {
   public:
    static constexpr int TETROMINOS = 7;

   private:
    static constexpr std::array<tetris::Color, TETROMINOS> TETROMINO_COLORS = {
        tetris::Color::TETROMINO_YELLOW,  tetris::Color::TETROMINO_CYAN,
        tetris::Color::TETROMINO_GREEN,   tetris::Color::TETROMINO_RED,
        tetris::Color::TETROMINO_WHITE,   tetris::Color::TETROMINO_BLUE,
        tetris::Color::TETROMINO_MAGENTA,
    };

    static constexpr std::array<tetris::Color, TETROMINOS> PREVIEW_COLORS = {
        tetris::Color::PREVIEW_YELLOW,  tetris::Color::PREVIEW_CYAN,  tetris::Color::PREVIEW_GREEN,
        tetris::Color::PREVIEW_RED,     tetris::Color::PREVIEW_WHITE, tetris::Color::PREVIEW_BLUE,
        tetris::Color::PREVIEW_MAGENTA,
    };

    static constexpr tetris::Direction DEFAULT_SHAPE_DIRECTION = tetris::Direction::RIGHT;
    static constexpr int START_X = (tetris::BOARD_WIDTH - tetris::SHAPESIZE) / 2;
    static constexpr int START_Y = -1;  // All block has a line of zeros at the top as they are
                                        // stored in a 4x4 matrix and rotate around the middle
    int m_x = START_X;
    int m_y = START_Y;
    bool m_beenHeld = false;
    size_t m_shapeIndex = 0;
    tetris::Direction m_direction = DEFAULT_SHAPE_DIRECTION;

    // Allow unit tests to access private data
    friend class TetrominoTestHelper;

   public:
    Tetromino() : Tetromino(0) {};
    explicit Tetromino(std::optional<int> shapeIndex);
    bool isFilledAt(size_t x, size_t y) const;
    void hold();
    bool hasBeenHeld() const { return m_beenHeld; };

    void tick() { m_y += 1; };
    void move(tetris::Direction directionToMove);
    void rotateRight() {
        m_direction = static_cast<tetris::Direction>((static_cast<int>(m_direction) + 1) % 4);
    };

    tetris::Color getColor() const { return TETROMINO_COLORS[m_shapeIndex]; };
    tetris::Color getPreviewColor() const { return PREVIEW_COLORS[m_shapeIndex]; };
    int getX() const { return m_x; };
    int getY() const { return m_y; };
    char getShape() const;

    template <typename screenInterface>
        requires Screen::ScreenInterface<screenInterface>
    void render(std::optional<std::pair<size_t, size_t>> pos = std::nullopt,
                bool isPreview = false) const;
};