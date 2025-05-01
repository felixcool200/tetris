#pragma once

// Define the screen type based on the preprocessor macro passed by CMake
#ifdef SCREEN_NCURSES
#include <ncursesScreen.hpp>
using ScreenType = NcursesScreen;

#elif defined(SCREEN_RAYLIB)
#include <raylibScreen.hpp>
using ScreenType = RaylibScreen;

#else
#error "No valid SCREEN_TYPE defined!"
#endif

#include <screenInterface.hpp>
static_assert(Screen::ScreenInterface<ScreenType>, "Selected screen does not implement interface");

// Needed to make sure the instance is created. If possible the headers should be removed to make
// the dependency tree easier.
#include <game.hpp>
#include <tetromino.hpp>
#include <ui.hpp>

template class Game<ScreenType>;
template class Tetromino<ScreenType>;
template class UI<ScreenType>;