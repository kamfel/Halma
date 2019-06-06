#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <iostream>
#include "Board.h"
#include "Event.h"
#include "Files.h"

bool ProcessEvent(Board & board, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display)
{
	ALLEGRO_MOUSE_STATE mouse_state;
	ALLEGRO_EVENT e;
	static int winner = 0;
	if (!al_get_next_event(queue, &e)) return true;

	char msg[50] = { 0 };

	switch (e.type) {
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		return false;
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		al_get_mouse_state(&mouse_state);
		if (!(mouse_state.buttons & 0x1)) break;
		if (winner) break;
		if (!board.TryMove(mouse_state.x, mouse_state.y)) {
			board.HighlightTile(mouse_state.x, mouse_state.y);
		}
		winner = board.CheckWinner();
		sprintf_s<50>(msg, "Gracz %d wygral gre.", winner);
		if (winner) {
			al_show_native_message_box(display, "Wygrana", msg, " ", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
		}
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		switch (e.keyboard.keycode)
		{
		case ALLEGRO_KEY_2:
			board.Start2PlayerGame();
			break;
		case ALLEGRO_KEY_4:
			board.Start4PlayerGame();
			break;
		case ALLEGRO_KEY_L:
			if (!LoadFromFile(display, board)) {
				al_show_native_message_box(display, "Blad", "Nie udalo sie otworzyc pliku", " ", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
			}
			break;
		case ALLEGRO_KEY_S:
			if (!SaveToFile(display, board)) {
				al_show_native_message_box(display, "Blad", "Nie udalo sie zapisac pliku", " ", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return true;
}


