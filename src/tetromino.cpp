#include "tetromino.hpp"

#include <functional>
#include <random>

#include "common.hpp"
namespace {
static int randomTetrominoIndex() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, Tetromino::TETROMINOS - 1);

    return dist(gen);
}

}  // namespace

Tetromino::Tetromino(std::optional<int> shapeIndex) {
    m_shapeIndex = shapeIndex.value_or(randomTetrominoIndex());
}

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
bool Tetromino::isFilledAt(size_t x, size_t y) const {
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

        case tetris::Direction::RIGHT:
            m_x += 1;
            break;

        case tetris::Direction::DOWN:
            m_y += 1;
            break;

        case tetris::Direction::LEFT:
            m_x -= 1;
            break;
    }
}

// Templated render function
template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void Tetromino::render(std::optional<std::pair<size_t, size_t>> pos, bool isPreview) const {
    const auto color = isPreview ? getPreviewColor() : getColor();
    const auto drawFunc = [&](size_t dx, size_t dy) {
        if (pos.has_value()) {
            screenInterface::addCharAt('B', (pos->first + dx), (pos->second + dy), color);
        } else {
            screenInterface::addCharAtBoard('B', (m_x + dx), (m_y + dy), color);
        }
    };
    for (size_t dx = 0; dx < tetris::SHAPESIZE; ++dx) {
        for (size_t dy = 0; dy < tetris::SHAPESIZE; ++dy) {
            if (isFilledAt(dx, dy)) {
                drawFunc(dx, dy);
            }
        }
    }
}

#include "screenTypeSelector.hpp"

template void Tetromino::render<ScreenType>(std::optional<std::pair<size_t, size_t>> pos,
                                            bool isPreview) const;
