#pragma once

#include <ncursesScreen.hpp>
#include <tetromino.hpp>
#include <game.hpp>
#include <ui.hpp>

using ScreenType = NcursesScreen;

template class Game<ScreenType>;
template class Tetromino<ScreenType>;
template class UI<ScreenType>;