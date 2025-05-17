#include <catch2/catch_test_macros.hpp>

#include "square.hpp"

TEST_CASE("Square default state") {
    Square sq;

    REQUIRE_FALSE(sq.isPlaced());
    REQUIRE(sq.getColor() == tetris::Color::NONE);
}

TEST_CASE("Square::place sets filled and color") {
    Square sq;
    sq.place(tetris::Color::TETROMINO_RED);

    REQUIRE(sq.isPlaced());
    REQUIRE(sq.getColor() == tetris::Color::TETROMINO_RED);
}

TEST_CASE("Square::remove clears filled and sets color to NONE") {
    Square sq;
    sq.place(tetris::Color::TETROMINO_BLUE);
    REQUIRE(sq.isPlaced());

    sq.remove();

    REQUIRE_FALSE(sq.isPlaced());
    REQUIRE(sq.getColor() == tetris::Color::NONE);
}

TEST_CASE("Square::replace copies state from another square") {
    Square source;
    source.place(tetris::Color::TETROMINO_GREEN);

    Square target;
    REQUIRE_FALSE(target.isPlaced());

    target.replace(source);

    REQUIRE(target.isPlaced());
    REQUIRE(target.getColor() == tetris::Color::TETROMINO_GREEN);
}

SCENARIO("A Square can be placed, removed, and replaced", "[square]") {
    GIVEN("An empty Square") {
        Square s;

        THEN("It should not be placed initially") {
            REQUIRE_FALSE(s.isPlaced());
            REQUIRE(s.getColor() == tetris::Color::NONE);
        }

        WHEN("It is placed with a color") {
            s.place(tetris::Color::TETROMINO_RED);

            THEN("It should be marked as placed") {
                REQUIRE(s.isPlaced());
            }

            THEN("It should store the correct color") {
                REQUIRE(s.getColor() == tetris::Color::TETROMINO_RED);
            }
        }

        WHEN("It is removed after being placed") {
            s.place(tetris::Color::TETROMINO_BLUE);
            s.remove();

            THEN("It should no longer be placed") {
                REQUIRE_FALSE(s.isPlaced());
            }

            THEN("Its color should be NONE") {
                REQUIRE(s.getColor() == tetris::Color::NONE);
            }
        }

        WHEN("It is replaced with another placed square") {
            Square other;
            other.place(tetris::Color::TETROMINO_GREEN);
            s.replace(other);

            THEN("It should copy the placed state and color") {
                REQUIRE(s.isPlaced());
                REQUIRE(s.getColor() == tetris::Color::TETROMINO_GREEN);
            }
        }

        WHEN("It is replaced with an empty square") {
            Square other;
            s.place(tetris::Color::TETROMINO_RED);
            s.replace(other);

            THEN("It should no longer be placed") {
                REQUIRE_FALSE(s.isPlaced());
                REQUIRE(s.getColor() == tetris::Color::NONE);
            }
        }
    }
}