#pragma once
#include <string>
#include "Board.h"

bool SaveToFile(ALLEGRO_DISPLAY* display, const Board&board);

bool LoadFromFile(ALLEGRO_DISPLAY* display, Board& board);