#pragma once

#include <common.hpp>
#include <tetromino.hpp>
#include <square.hpp>

#include <array>
#include <optional>

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>  // Ensure Screen implements the required interface
class Game{
    private:
        std::array<std::array<Square,tetris::BOARD_HEIGHT>, tetris::BOARD_WIDTH> m_board;
        Tetromino<screenInterface> m_tetromino;
        std::optional<Tetromino<screenInterface>> m_hold;
        Tetromino<screenInterface> m_next;   
        Tetromino<screenInterface> m_tetrominoPreview;
        unsigned int m_score = 0;
        unsigned int m_linesCleared = 0;
        unsigned int m_level = 0;
        bool m_showPreview = true;
        bool m_isGameOver = false;
        bool m_tetrominoJustPlaced = true;
        
        bool checkForObstruction(const Tetromino<screenInterface>& bl) const;
 
        void createPreview();     
        void dropTetromino();   
        void placeTetromino();
        void addTetrominoToBoard(const Tetromino<screenInterface> &bl);
        void removeCompleteRows();
        void createNewTetromino();
        void removeRow(int index);
        void updateLevel();

    public:
        Game();
        int getFramesPerTick() const;
        void update(tetris::Control keyPressed);
        void tick();
        void draw() const;
        std::string getResult() const;
        bool wasTetrominoJustPlaced() const;
        bool isGameOver() const;

        static constexpr bool isOnBoard(int x, int y) {
            return ((x <= tetris::BOARD_WIDTH - 1) && (x >= 0) && (y <= tetris::BOARD_HEIGHT - 1) && (y >= 0));
        }
};
