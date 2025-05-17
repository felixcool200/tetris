#pragma once

// Define the screen type based on the preprocessor macro passed by CMake
#ifdef SCREEN_NCURSES
#include "ncursesScreen.hpp"
using ScreenType = Screen::NcursesScreen;

#elif defined(SCREEN_RAYLIB)
#include "raylibScreen.hpp"
using ScreenType = Screen::RaylibScreen;

#else
#error "No valid SCREEN_TYPE defined!"
#endif

#include "screenInterface.hpp"
static_assert(Screen::ScreenInterface<ScreenType>, "Selected screen does not implement interface");