#pragma once

#include <ncursesScreen.hpp>
using ScreenType = NcursesScreen;


#include <screenInterface.hpp>
static_assert(Screen::ScreenInterface<NcursesScreen>, "Selected screen does not implement interface");

// Needed to make sure the instance is created. If possible the headers should be remove to make the dependecy tree easier.
#include <tetromino.hpp>
#include <game.hpp>
#include <ui.hpp>
template class Game<ScreenType>;
template class Tetromino<ScreenType>;
template class UI<ScreenType>;