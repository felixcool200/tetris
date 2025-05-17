#pragma once
#include <common.hpp>
#include <screenInterface.hpp>
#include <string_view>

// Implementation of the ScreenInterface for mocking
namespace Screen {
class MockScreen {
   public:
    static Screen::StatusCode initScreen() { return Screen::StatusCode::OKEY; };
    static Screen::StatusCode closeScreen() { return Screen::StatusCode::OKEY; };

    static tetris::Control getInput();

    static Screen::StatusCode clearScreen() { return Screen::StatusCode::OKEY; };
    static Screen::StatusCode redrawScreen() { return Screen::StatusCode::OKEY; };

    // Chars
    static Screen::StatusCode addCharAtBoard(char ch, int x, int y,
                                             tetris::Color color = tetris::Color::NONE) {
        return Screen::StatusCode::OKEY;
    };
    static Screen::StatusCode addCharAt(char ch, int x, int y,
                                        tetris::Color color = tetris::Color::NONE) {
        return Screen::StatusCode::OKEY;
    };

    // Strings
    static Screen::StatusCode addStringAt(std::string_view s, int x, int y,
                                          tetris::Color color = tetris::Color::NONE) {
        return Screen::StatusCode::OKEY;
    };
    static Screen::StatusCode addStringAtBoard(std::string_view s, int x, int y,
                                               tetris::Color color = tetris::Color::NONE) {
        return Screen::StatusCode::OKEY;
    };
};
}  // namespace Screen