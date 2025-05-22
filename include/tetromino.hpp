#pragma once

#include <array>
#include <optional>

#include "common.hpp"
#include "screenInterface.hpp"

class Tetromino {
   public:
    static constexpr int TETROMINOS = 7;
    enum class Shape {
        O,  // Square
        I,  // Line
        S,  // S-shape
        Z,  // Z-shape
        L,  // L-shape
        J,  // J-shape
        T   // T-shape
    };

   private:
    constexpr int shapeToIndex(Shape shape) const {
        switch (shape) {
            case Shape::O:
                return 0;
            case Shape::I:
                return 1;
            case Shape::S:
                return 2;
            case Shape::Z:
                return 3;
            case Shape::L:
                return 4;
            case Shape::J:
                return 5;
            case Shape::T:
                return 6;
            default:
                return 0;  // Default to 'O' if unknown
        }
    }

    constexpr Shape indexToShape(int index) const {
        switch (index) {
            case 0:
                return Shape::O;
            case 1:
                return Shape::I;
            case 2:
                return Shape::S;
            case 3:
                return Shape::Z;
            case 4:
                return Shape::L;
            case 5:
                return Shape::J;
            case 6:
                return Shape::T;
            default:
                return Shape::O;  // Default to 'O' if unknown
        }
    }

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
    Shape m_shape = Shape::O;
    tetris::Direction m_direction = DEFAULT_SHAPE_DIRECTION;

   public:
    Tetromino() : Tetromino(std::nullopt) {};
    explicit Tetromino(std::optional<Shape> shape);
    bool isFilledAt(size_t x, size_t y) const;
    void hold();
    bool hasBeenHeld() const { return m_beenHeld; };

    void tick() { m_y += 1; };
    void move(tetris::Direction directionToMove);
    void rotateRight() {
        m_direction = static_cast<tetris::Direction>((static_cast<int>(m_direction) + 1) % 4);
    };

    tetris::Color getColor() const { return TETROMINO_COLORS[shapeToIndex(m_shape)]; };
    tetris::Color getPreviewColor() const { return PREVIEW_COLORS[shapeToIndex(m_shape)]; };
    int getX() const { return m_x; };
    int getY() const { return m_y; };
    Shape getShape() const { return m_shape; };

    template <typename screenInterface>
        requires Screen::ScreenInterface<screenInterface>
    void render(std::optional<std::pair<size_t, size_t>> pos = std::nullopt,
                bool isPreview = false) const;
};