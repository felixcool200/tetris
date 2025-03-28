#pragma once
#include <ncursesScreen.hpp>
#include <tetromino.hpp>
#include <game.hpp>
#include <ui.hpp>
template class Game<NcursesScreen>;
template class Tetromino<NcursesScreen>;
template class UI<NcursesScreen>;