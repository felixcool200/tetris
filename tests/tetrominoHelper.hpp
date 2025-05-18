#include <memory>

#include "tetromino.hpp"

class TetrominoTestHelper {
   private:
    Tetromino tetromino;

   public:
    void setShape(int shapeId = 0) { tetromino.m_shapeIndex = shapeId; };

    // Carefull with lifetime here, maybe return a weak_ptr
    Tetromino& getTetromino(int shapeId = 0) { return tetromino; };

    static constexpr size_t getTotalTetrominos() { return Tetromino::TETROMINOS; };
};
