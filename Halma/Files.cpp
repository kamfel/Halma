#include <string>
#include <fstream>
#include <allegro5\allegro_native_dialog.h>
#include "Board.h"
#include "Files.h"

typedef unsigned int ALLEGRO_FILECHOOSER_FLAG;

const char* GetPath(ALLEGRO_DISPLAY* display, ALLEGRO_FILECHOOSER_FLAG flag) {
	ALLEGRO_FILECHOOSER* filechooser = al_create_native_file_dialog("C:", "Wybierz plik", "*.hsav;*.*;", flag);
	al_show_native_file_dialog(display, filechooser);
	const char* path = al_get_native_file_dialog_path(filechooser, 0);
	al_destroy_native_file_dialog(filechooser);
	return path;
}

bool SaveToFile(ALLEGRO_DISPLAY* display, const Board& board)
{
	const char* path = GetPath(display, ALLEGRO_FILECHOOSER_SAVE);
	if (path == nullptr) return true;
	std::ofstream ofs(path, std::ios_base::trunc | std::ios_base::binary);
	if (!ofs.is_open()) return false;
	board.SaveToFile(ofs);
	ofs.close();
	return true;
}

bool LoadFromFile(ALLEGRO_DISPLAY* display, Board& board)
{
	const char* path = GetPath(display, ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
	if (path == nullptr) return true;
	std::ifstream ifs(path, std::ios_base::binary);
	if (!ifs.is_open()) return false;
	board.LoadFromFile(ifs);
	ifs.close();
	return true;
}
