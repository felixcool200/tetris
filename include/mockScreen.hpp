#pragma once
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

#include "common.hpp"
#include "screenInterface.hpp"

namespace Screen {
struct MockScreen {
    static inline std::vector<std::string> drawnStrings;
    static inline std::vector<std::tuple<char, size_t, size_t>> drawnChars;

    static void reset() {
        drawnStrings.clear();
        drawnChars.clear();
    }

    // Required by concept
    static Screen::StatusCode initScreen() { return Screen::StatusCode::OKEY; }
    static Screen::StatusCode closeScreen() { return Screen::StatusCode::OKEY; }
    static tetris::Control getInput() { return tetris::Control::NONE; }
    static Screen::StatusCode clearScreen() { return Screen::StatusCode::OKEY; }
    static Screen::StatusCode redrawScreen() { return Screen::StatusCode::OKEY; }

    static Screen::StatusCode addCharAt(char c, size_t x, size_t y,
                                        tetris::Color = tetris::Color::NONE) {
        drawnStrings.push_back(std::string(1, c));
        drawnChars.emplace_back(c, x, y);
        return Screen::StatusCode::OKEY;
    }
    static Screen::StatusCode addCharAtBoard(char c, size_t x, size_t y,
                                             tetris::Color = tetris::Color::NONE) {
        drawnStrings.push_back(std::string(1, c));
        drawnChars.emplace_back(c, x, y);
        return Screen::StatusCode::OKEY;
    }
    static Screen::StatusCode addStringAt(std::string_view str, size_t, size_t,
                                          tetris::Color = tetris::Color::NONE) {
        drawnStrings.push_back(std::string(str));
        return Screen::StatusCode::OKEY;
    }
    static Screen::StatusCode addStringAtBoard(std::string_view str, size_t, size_t,
                                               tetris::Color = tetris::Color::NONE) {
        drawnStrings.push_back(std::string(str));
        return Screen::StatusCode::OKEY;
    }

    static bool wasStringDrawn(const std::string& s) {
        for (const auto& str : drawnStrings)
            if (str.find(s) != std::string::npos) return true;
        return false;
    }
    static int countChar(char c) {
        int count = 0;
        for (const auto& str : drawnStrings) {
            for (char ch : str) {
                if (ch == c) {
                    ++count;
                }
            }
        }
        return count;
    }

    static bool wasCharDrawnAt(char c, size_t x, size_t y) {
        for (const auto& [ch, cx, cy] : drawnChars) {
            if (ch == c && cx == x && cy == y) {
                return true;
            }
        }
        return false;
    }

    static int countCharAt(char c, size_t x, size_t y) {
        int count = 0;
        for (const auto& [ch, cx, cy] : drawnChars) {
            if (ch == c && cx == x && cy == y) {
                ++count;
            }
        }
        return count;
    }
};
}  // namespace Screen