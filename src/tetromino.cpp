#include <ScreenToUse.hpp>
#include <common.hpp>
#include <functional>
#include <iostream>
#include <screenInterface.hpp>
#include <tetromino.hpp>

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
template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
bool Tetromino<screenInterface>::isFilledAt(int x, int y) const {
    switch (m_direction) {
        case tetris::Direction::North:
            return tetris::PIECES[m_shapeIndex][x][y];
        case tetris::Direction::East:
            return tetris::PIECES[m_shapeIndex][y][tetris::SHAPESIZE - 1 - x];
        case tetris::Direction::South:
            return tetris::PIECES[m_shapeIndex][tetris::SHAPESIZE - 1 - x]
                                 [tetris::SHAPESIZE - 1 - y];
        case tetris::Direction::West:
            return tetris::PIECES[m_shapeIndex][tetris::SHAPESIZE - 1 - y]
                                 [tetris::SHAPESIZE - 1 - (tetris::SHAPESIZE - 1 - x)];
    }
    return false;
}

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
char Tetromino<screenInterface>::getShape() const {
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

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void Tetromino<screenInterface>::hold() {
    // Reset position
    m_x = startX;
    m_y = startY;
    m_direction = tetris::DEFAULT_SHAPE_DIRECTION;

    m_beenHeld = true;
}

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void Tetromino<screenInterface>::move(tetris::Direction directionToMove) {
    switch (directionToMove) {
        // Rotate the Tetromino
        case tetris::Direction::North:
            rotateRight();
            break;
        // Move Tetromino one step to the right
        case tetris::Direction::East:
            m_x += 1;
            break;

        // Speed up Tetromino
        // TODO: Change this to a factor(2) that is multiplied when a tick is performed.
        case tetris::Direction::South:
            m_y += 1;
            break;

        // Move Tetromino one step to the left
        case tetris::Direction::West:
            m_x -= 1;
            break;
    }
}

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void Tetromino<screenInterface>::render(bool isPreview) const {
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
void Tetromino<screenInterface>::renderAt(int x, int y, bool isPreview) const {
    const auto color = isPreview ? getPreviewColor() : getColor();
    for (int dx = 0; dx < tetris::SHAPESIZE; ++dx) {
        for (int dy = 0; dy < tetris::SHAPESIZE; ++dy) {
            if (isFilledAt(dx, dy)) {
                screenInterface::addCharAt('B', (x + dx), (y + dy), color);
            }
        }
    }
}

// Functions
template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
Tetromino<screenInterface> Tetromino<screenInterface>::testMove(Tetromino<screenInterface> bl,
                                                                tetris::Direction directionToMove) {
    // Make sure it is a copy of bl
    bl.move(directionToMove);
    return bl;
}

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
Tetromino<screenInterface> Tetromino<screenInterface>::testTick(Tetromino<screenInterface> bl) {
    // Make sure it is a copy of bl
    bl.tick();
    return bl;
}