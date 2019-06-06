#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <fstream>
#include <string>
#include "Pawn.h"

Pawn::Pawn(int player_nr, float x, float y)
	: Graphic(x, y, 40, 40), m_player_nr(player_nr)
{
	al_set_target_bitmap(m_bitmap);
	al_clear_to_color(al_map_rgba(255, 255, 255, 0));
	SetBitmap();
}


Pawn::~Pawn()
{
}

void Pawn::SetBitmap()
{
	switch (m_player_nr) {
	case 1:
		al_draw_filled_triangle(20, 5, 5, 35, 35, 35, al_map_rgb(255, 0, 0));
		al_draw_triangle(20, 5, 5, 35, 35, 35, al_map_rgb(0, 0, 0), 2);
		break;
	case 2:
		al_draw_filled_triangle(20, 5, 5, 35, 35, 35, al_map_rgb(0, 255, 0));
		al_draw_triangle(20, 5, 5, 35, 35, 35, al_map_rgb(0, 0, 0), 2);
		break;
	case 3:
		al_draw_filled_triangle(20, 5, 5, 35, 35, 35, al_map_rgb(0, 0, 255));
		al_draw_triangle(20, 5, 5, 35, 35, 35, al_map_rgb(0, 0, 0), 2);
		break;
	case 4:
		al_draw_filled_triangle(20, 5, 5, 35, 35, 35, al_map_rgb(255, 255, 0));
		al_draw_triangle(20, 5, 5, 35, 35, 35, al_map_rgb(0, 0, 0), 2);
		break;
	}
}

void Pawn::DisplayBitmap()
{
	al_draw_bitmap(m_bitmap, m_x, m_y, 0);
}

void Pawn::HighlightPawn()
{
	al_set_target_bitmap(m_bitmap);
	al_clear_to_color(al_map_rgb(150, 150, 150));
	SetBitmap();
}

void Pawn::UnhighlightPawn()
{
	al_set_target_bitmap(m_bitmap);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	SetBitmap();
}

void Pawn::Move(int x, int y, int x_board, int y_board)
{
	m_x = x_board + 3 + x * 43;
	m_y = y_board + 3 + y * 43;
	UnhighlightPawn();
}