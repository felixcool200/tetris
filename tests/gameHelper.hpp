#include "game.hpp"

class GameTestHelper {
   private:
    Game game;

   public:
    GameTestHelper() = default;
    GameTestHelper(Tetromino tetromino) { setCurrentTetromino(tetromino); }

    void setCurrentTetromino(Tetromino tetromino) { game.m_tetromino = tetromino; };

    void setHoldTetromino(Tetromino tetromino) { game.m_hold = tetromino; };

    void setNextTetromino(Tetromino tetromino) { game.m_next = tetromino; };

    auto& getBoard() { return game.m_board; };

    // Careful with lifetime here, return weak_ptr?
    Game& getGame() { return game; };

    // Private function access
    bool checkForObstruction(const Tetromino& bl) const { return game.checkForObstruction(bl); };

    void createPreview() { game.createPreview(); };
    void dropTetromino() { game.dropTetromino(); };
    void placeTetromino() { game.placeTetromino(); };
    void addTetrominoToBoard(const Tetromino& bl) { game.addTetrominoToBoard(bl); };
    void removeCompleteRows() { game.removeCompleteRows(); };
    void createNewTetromino() { game.createNewTetromino(); };
    void removeRow(int index) { game.removeRow(index); };
    void updateLevel() { game.updateLevel(); };
    void updateSpeed() { game.updateSpeed(); };

    // Extra functions for tests
    Tetromino getTetromino() { return game.m_tetromino; };
    Tetromino getTetrominoPreview() { return game.m_tetrominoPreview; };

    void setTetrominoPreview(Tetromino tetromino) { game.m_tetromino = tetromino; };

    size_t getLinesCleared() { return game.m_linesCleared; };
};