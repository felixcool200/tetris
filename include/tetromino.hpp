#pragma once

#include <common.hpp>
#include <screenInterface.hpp>

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
class Tetromino {
   private:
    static constexpr int startX = (tetris::BOARD_WIDTH - tetris::SHAPESIZE) / 2;
    static constexpr int startY = -1;  // All block has a line of zeros at the top as they are
                                       // stored in a 4x4 matrix and rotate around the middle
    int m_x = startX;
    int m_y = startY;
    bool m_beenHeld = false;
    int m_shapeIndex = tetris::randomTetrominoIndex();
    tetris::Direction m_direction = tetris::DEFAULT_SHAPE_DIRECTION;

   public:
    bool isFilledAt(int x, int y) const;
    void hold();
    bool hasBeenHeld() const { return m_beenHeld; };

    void tick() { m_y += 1; };
    void move(tetris::Direction directionToMove);
    void rotateRight() {
        m_direction = static_cast<tetris::Direction>((static_cast<int>(m_direction) + 1) % 4);
    };

    void render(bool isPreview = false) const;
    void renderAt(int x, int y, bool isPreview = false) const;

    tetris::Color getColor() const { return tetris::TETROMINO_COLORS[m_shapeIndex]; };
    tetris::Color getPreviewColor() const { return tetris::PREVIEW_COLORS[m_shapeIndex]; };
    int getX() const { return m_x; };
    int getY() const { return m_y; };
    char getShape() const;

    static Tetromino<screenInterface> testMove(Tetromino<screenInterface> bl,
                                               tetris::Direction directionToMove);
    static Tetromino<screenInterface> testTick(Tetromino<screenInterface> bl);
};