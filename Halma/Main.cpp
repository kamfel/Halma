#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_native_dialog.h>
#include <crtdbg.h>
#include "Board.h"
#include "Pawn.h"
#include "Event.h"

#define _CRTDBG_MAP_ALLOC

int main(int argc, char** argv) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	al_init();
	al_init_primitives_addon();
	al_init_native_dialog_addon();
	al_install_mouse();
	al_install_keyboard();

	ALLEGRO_DISPLAY* main_display = al_create_display(850, 700);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_BITMAP* bitmap_which_player = al_create_bitmap(100, 100);
	al_set_target_bitmap(bitmap_which_player);
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_register_event_source(queue, al_get_display_event_source(main_display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());

	Board board = Board();
	Graphic* graphic;
	Pawn** tiles;

	while (ProcessEvent(board, queue, main_display)) {

		board.SetColorWhichPlayer(bitmap_which_player);
		al_set_target_bitmap(al_get_backbuffer(main_display));
		al_clear_to_color(al_map_rgb(255, 255, 255));

		graphic = &board;
		graphic->DisplayBitmap();

		tiles = board.GetTiles();
		for (int i = 0; i < 16 * 16; i++) {
			if (!tiles[i]) continue;
			graphic = tiles[i];
			graphic->DisplayBitmap();
		}

		al_draw_bitmap(bitmap_which_player, 700, 3, 0);
		al_flip_display();
	}
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_shutdown_native_dialog_addon();
	al_shutdown_primitives_addon();
	al_destroy_event_queue(queue);
	al_destroy_display(main_display);
	return 0;
}