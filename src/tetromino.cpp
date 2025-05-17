#include "tetromino.hpp"

#include <array>
#include <functional>
#include <iostream>

#include "common.hpp"

/*
    https://stackoverflow.com/questions/37812817/finding-element-at-x-y-in-a-given-matrix-after-rotation-in-c-c
    m_direction = 0
            0 1 2 3
            4 5 6 7
            8 9 A B
            C D E F

    m_direction = 1
            C 8 4 0
            D 9 5 1
            E A 6 2
            F B 7 3

    m_direction = 2
            F E D C
            B A 9 8
            7 6 5 4
            3 2 1 0

    m_direction = 3
            3 7 B F
            2 6 A E
            1 5 9 D
            0 4 8 C
*/
bool Tetromino::isFilledAt(int x, int y) const {
    static constexpr std::array<std::array<std::array<bool, tetris::SHAPESIZE>, tetris::SHAPESIZE>,
                                Tetromino::TETROMINOS>
        PIECES = {{
            // O_PIECE
            {{
                {false, false, false, false},
                {false, true, true, false},
                {false, true, true, false},
                {false, false, false, false},
            }},
            // I_PIECE
            {{
                {false, false, false, false},
                {true, true, true, true},
                {false, false, false, false},
                {false, false, false, false},
            }},
            // S_PIECE
            {{
                {false, false, false, false},
                {false, true, true, false},
                {true, true, false, false},
                {false, false, false, false},
            }},
            // Z_PIECE
            {{
                {false, false, false, false},
                {true, true, false, false},
                {false, true, true, false},
                {false, false, false, false},
            }},
            // L_PIECE
            {{
                {false, false, false, false},
                {true, true, true, false},
                {true, false, false, false},
                {false, false, false, false},
            }},
            // J_PIECE
            {{
                {false, false, false, false},
                {true, true, true, false},
                {false, false, true, false},
                {false, false, false, false},
            }},
            // T_PIECE
            {{
                {false, false, false, false},
                {true, true, true, false},
                {false, true, false, false},
                {false, false, false, false},
            }},
        }};

    switch (m_direction) {
        case tetris::Direction::UP:
            return PIECES[m_shapeIndex][x][y];
        case tetris::Direction::RIGHT:
            return PIECES[m_shapeIndex][y][tetris::SHAPESIZE - 1 - x];
        case tetris::Direction::DOWN:
            return PIECES[m_shapeIndex][tetris::SHAPESIZE - 1 - x][tetris::SHAPESIZE - 1 - y];
        case tetris::Direction::LEFT:
            return PIECES[m_shapeIndex][tetris::SHAPESIZE - 1 - y]
                         [tetris::SHAPESIZE - 1 - (tetris::SHAPESIZE - 1 - x)];
    }
    return false;
}

char Tetromino::getShape() const {
    switch (m_shapeIndex) {
        case 0:
            return 'O';
        case 1:
            return 'I';
        case 2:
            return 'S';
        case 3:
            return 'Z';
        case 4:
            return 'L';
        case 5:
            return 'J';
        case 6:
            return 'T';
    }
    return 'O';
}

void Tetromino::hold() {
    // Reset position
    m_x = START_X;
    m_y = START_Y;
    m_direction = DEFAULT_SHAPE_DIRECTION;

    m_beenHeld = true;
}

void Tetromino::move(tetris::Direction directionToMove) {
    switch (directionToMove) {
        // Rotate the Tetromino
        case tetris::Direction::UP:
            m_y -= 1;
            break;
        // Move Tetromino one step to the right
        case tetris::Direction::RIGHT:
            m_x += 1;
            break;

        // Move tetramino one extra step
        // TODO: Change this to a factor(2) that is multiplied when a tick is performed.
        case tetris::Direction::DOWN:
            m_y += 1;
            break;

        // Move Tetromino one step to the left
        case tetris::Direction::LEFT:
            m_x -= 1;
            break;
    }
}

// Templated render functions
template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void Tetromino::render(bool isPreview) const {
    const auto color = isPreview ? getPreviewColor() : getColor();
    for (int dx = 0; dx < tetris::SHAPESIZE; ++dx) {
        for (int dy = 0; dy < tetris::SHAPESIZE; ++dy) {
            if (isFilledAt(dx, dy)) {
                screenInterface::addCharAtBoard('B', (m_x + dx), (m_y + dy), color);
            }
        }
    }
}

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void Tetromino::renderAt(int x, int y, bool isPreview) const {
    const auto color = isPreview ? getPreviewColor() : getColor();
    for (int dx = 0; dx < tetris::SHAPESIZE; ++dx) {
        for (int dy = 0; dy < tetris::SHAPESIZE; ++dy) {
            if (isFilledAt(dx, dy)) {
                screenInterface::addCharAt('B', (x + dx), (y + dy), color);
            }
        }
    }
}

#include "screenTypeSelector.hpp"

template void Tetromino::render<ScreenType>(bool) const;
template void Tetromino::renderAt<ScreenType>(int, int, bool) const;