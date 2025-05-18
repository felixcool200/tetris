#include <catch2/catch_test_macros.hpp>

#include "square.hpp"

TEST_CASE("Square default state") {
    Square sq;

    CHECK_FALSE(sq.isPlaced());
    CHECK(sq.getColor() == tetris::Color::NONE);
}

TEST_CASE("Square::place sets filled and color") {
    Square sq;
    sq.place(tetris::Color::TETROMINO_RED);

    CHECK(sq.isPlaced());
    CHECK(sq.getColor() == tetris::Color::TETROMINO_RED);
}

TEST_CASE("Square::remove clears filled and sets color to NONE") {
    Square sq;
    sq.place(tetris::Color::TETROMINO_BLUE);
    CHECK(sq.isPlaced());

    sq.remove();

    CHECK_FALSE(sq.isPlaced());
    CHECK(sq.getColor() == tetris::Color::NONE);
}

TEST_CASE("Square::replace copies state from another square") {
    Square source;
    source.place(tetris::Color::TETROMINO_GREEN);

    Square target;
    CHECK_FALSE(target.isPlaced());

    target.replace(source);

    CHECK(target.isPlaced());
    CHECK(target.getColor() == tetris::Color::TETROMINO_GREEN);
}

TEST_CASE("Square double placement overwrites color and remains placed") {
    Square sq;
    sq.place(tetris::Color::TETROMINO_RED);
    CHECK(sq.isPlaced());
    CHECK(sq.getColor() == tetris::Color::TETROMINO_RED);

    sq.place(tetris::Color::TETROMINO_BLUE);
    CHECK(sq.isPlaced());
    CHECK(sq.getColor() == tetris::Color::TETROMINO_BLUE);
}

TEST_CASE("Square replace with empty square clears state") {
    Square filled;
    filled.place(tetris::Color::TETROMINO_GREEN);

    Square empty;
    filled.replace(empty);

    CHECK_FALSE(filled.isPlaced());
    CHECK(filled.getColor() == tetris::Color::NONE);
}

TEST_CASE("Square replace with itself does not change state") {
    Square sq;
    sq.place(tetris::Color::TETROMINO_MAGENTA);

    sq.replace(sq);

    CHECK(sq.isPlaced());
    CHECK(sq.getColor() == tetris::Color::TETROMINO_MAGENTA);
}

TEST_CASE("Square remove after replace works correctly") {
    Square sq1;
    sq1.place(tetris::Color::TETROMINO_YELLOW);

    Square sq2;
    sq2.place(tetris::Color::TETROMINO_CYAN);

    sq1.replace(sq2);
    CHECK(sq1.isPlaced());
    CHECK(sq1.getColor() == tetris::Color::TETROMINO_CYAN);

    sq1.remove();
    CHECK_FALSE(sq1.isPlaced());
    CHECK(sq1.getColor() == tetris::Color::NONE);
}