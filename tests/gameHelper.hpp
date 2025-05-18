#include "game.hpp"

class GameTestHelper {
   private:
    Game game;

   public:
    void setCurrentTetromino(Tetromino tetromino) { game.m_tetromino = tetromino; };

    void setHoldTetromino(Tetromino tetromino) { game.m_hold = tetromino; };

    void setNextTetromino(Tetromino tetromino) { game.m_next = tetromino; };

    auto getBoard() { return game.m_board; };

    // Careful with lifetime here, return weak_ptr?
    Game& getGame() { return game; };
};