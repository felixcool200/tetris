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

SCENARIO("A Square can be placed, removed, and replaced", "[square]") {
    GIVEN("An empty Square") {
        Square s;

        THEN("It should not be placed initially") {
            CHECK_FALSE(s.isPlaced());
            CHECK(s.getColor() == tetris::Color::NONE);
        }

        WHEN("It is placed with a color") {
            s.place(tetris::Color::TETROMINO_RED);

            THEN("It should be marked as placed") {
                CHECK(s.isPlaced());
            }

            THEN("It should store the correct color") {
                CHECK(s.getColor() == tetris::Color::TETROMINO_RED);
            }
        }

        WHEN("It is removed after being placed") {
            s.place(tetris::Color::TETROMINO_BLUE);
            s.remove();

            THEN("It should no longer be placed") {
                CHECK_FALSE(s.isPlaced());
            }

            THEN("Its color should be NONE") {
                CHECK(s.getColor() == tetris::Color::NONE);
            }
        }

        WHEN("It is replaced with another placed square") {
            Square other;
            other.place(tetris::Color::TETROMINO_GREEN);
            s.replace(other);

            THEN("It should copy the placed state and color") {
                CHECK(s.isPlaced());
                CHECK(s.getColor() == tetris::Color::TETROMINO_GREEN);
            }
        }

        WHEN("It is replaced with an empty square") {
            Square other;
            s.place(tetris::Color::TETROMINO_RED);
            s.replace(other);

            THEN("It should no longer be placed") {
                CHECK_FALSE(s.isPlaced());
                CHECK(s.getColor() == tetris::Color::NONE);
            }
        }
    }
}