#pragma once

#include <random>

#include "common.hpp"
#include "screenInterface.hpp"

class Tetromino {
   private:
    static constexpr int TETROMINOS = 7;

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

    static int randomTetrominoIndex() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int> dist(0, TETROMINOS - 1);

        return dist(gen);
    }

    static constexpr tetris::Direction DEFAULT_SHAPE_DIRECTION = tetris::Direction::RIGHT;
    static constexpr int START_X = (tetris::BOARD_WIDTH - tetris::SHAPESIZE) / 2;
    static constexpr int START_Y = -1;  // All block has a line of zeros at the top as they are
                                        // stored in a 4x4 matrix and rotate around the middle
    int m_x = START_X;
    int m_y = START_Y;
    bool m_beenHeld = false;
    int m_shapeIndex = randomTetrominoIndex();
    tetris::Direction m_direction = DEFAULT_SHAPE_DIRECTION;

   public:
    bool isFilledAt(int x, int y) const;
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
    void render(bool isPreview = false) const;

    template <typename screenInterface>
        requires Screen::ScreenInterface<screenInterface>
    void renderAt(int x, int y, bool isPreview = false) const;
};