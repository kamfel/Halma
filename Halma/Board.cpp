#include <fstream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <string>
#include <iostream>
#include "Board.h"

Board::Board()
	: Graphic(4, 4, 691, 691), m_highlighted_nr(-1), m_players(0), m_has_move(0)
{
	memset(m_tiles, NULL, sizeof(Pawn*) * 16 * 16);
	SetBitmap();
}

Board::Board(const Board & board)
	:Graphic(4, 4, 691, 691), m_highlighted_nr(board.m_highlighted_nr), m_players(board.m_players), m_has_move(board.m_has_move)
{
}

Board::~Board()
{
	for (int i = 0; i < 16 * 16; i++) {
		if (!m_tiles[i]) continue;
		else delete m_tiles[i];
	}
}

void Board::Start2PlayerGame()
{
	for (int i = 0; i < 16 * 16; i++) {
		if (!m_tiles[i]) continue;
		else {
			delete m_tiles[i];
			m_tiles[i] = nullptr;
		}
	}
	m_players = 2;
	m_has_move = 1;
	al_set_target_bitmap(m_bitmap);

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (i + j < 6) m_tiles[i + 16 * j] = new Pawn(1, m_x + 3 + 43 * i, m_y + 3 + 43 * j);
		}
	}

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (i + j < 6) m_tiles[15 - i + 16 * (15 - j)] = new Pawn(2, m_x + 648 - 43 * i, m_y + 648 - 43 * j);
		}
	}
}

void Board::Start4PlayerGame()
{
	for (int i = 0; i < 16 * 16; i++) {
		if (!m_tiles[i]) continue;
		else {
			delete m_tiles[i];
			m_tiles[i] = nullptr;
		}
	}
	m_players = 4;
	m_has_move = 1;
	al_set_target_bitmap(m_bitmap);

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (i + j < 5) m_tiles[i + 16 * j] = new Pawn(1, m_x + 3 + 43 * i, m_y + 3 + 43 * j);
		}
	}

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (i + j < 5) m_tiles[i + 16 * (15 - j)] = new Pawn(2, m_x + 3 + 43 * i, m_y + 648 - 43 * j);
		}
	}

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (i + j < 5) m_tiles[15 - i + 16 * (15 - j)] = new Pawn(3, m_x + 648 - 43 * i, m_y + 648 - 43 * j);
		}
	}

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (i + j < 5) m_tiles[15 - i + 16 * j] = new Pawn(4, m_x + 648 - 43 * i, m_y + 3 + 43 * j);
		}
	}
}

bool Board::TryMove(int mouse_x, int mouse_y)
{
	//Sprawdzenie czy wybrano pionek
	if (m_has_move == 0) return false;
	if (m_highlighted_nr == -1) return false;
	if (!m_tiles[m_highlighted_nr]->CheckOwner(m_has_move)) return false;

	int x = (mouse_x - 1.5f - m_x) / 43;
	int y = (mouse_y - 1.5f - m_y) / 43;
	if (x >= 16 || y >= 16) return false;
	int tile_nr = x + 16 * y;

	bool ok = false;

	int offset = tile_nr - m_highlighted_nr;
	int offset_table[8] = { -33, -31, -18, -14, 14, 18, 31, 33 };

	if (tile_nr % 16 <= m_highlighted_nr % 16 + 2 && tile_nr % 16 >= m_highlighted_nr % 16 - 2 && offset >= -34 && offset <= 34) {
		for (int i = 0; i < 8; i++) {
			if (offset == offset_table[i]) return false;
		}

		if (tile_nr % 16 < m_highlighted_nr % 16 + 2 && tile_nr % 16 > m_highlighted_nr % 16 - 2 && offset >= -17 && offset <= 17) {
			ok = true;
		}
		else {
			if (m_tiles[m_highlighted_nr + offset / 2]) ok = true;
		}
	}
	if (m_tiles[tile_nr]) return false;

	if (ok) {
		//std::cout << "Move from (" << m_highlighted_nr % 16 << ", " << m_highlighted_nr / 16 << ") to (" << x << ", " << y << ")" << std::endl;
		m_tiles[m_highlighted_nr]->Move(x, y, m_x, m_y);
		m_tiles[tile_nr] = m_tiles[m_highlighted_nr];
		m_tiles[m_highlighted_nr] = nullptr;
		m_highlighted_nr = -1;
		if (m_players == 2) {
			if (m_has_move == 1) m_has_move = 2;
			else m_has_move = 1;
		}
		else {
			switch (m_has_move)
			{
			case 1:
				m_has_move = 2;
				break;
			case 2:
				m_has_move = 3;
				break;
			case 3:
				m_has_move = 4;
				break;
			case 4:
				m_has_move = 1;
				break;
			}
		}
		return true;
	}
	return false;
}

int Board::CheckWinner() const
{
	if (m_players == 2) return CheckWinner2Player();
	else if (m_players == 4) return CheckWinner4Player();
	else return false;
}

int Board::CheckWinner2Player() const
{
	bool winning = true;

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (i + j < 5)
				if (!m_tiles[15 - i + 16 * (15 - j)] || m_tiles[15 - i + 16 * (15 - j)]->GetPlayerNr() != 1) winning = false;
		}
	}
	if (winning) return 1;
	else winning = true;

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			if (i + j < 5) 
				if (!m_tiles[i + 16 * j] || m_tiles[i + 16 * j]->GetPlayerNr() != 2) winning = false;
		}
	}
	if (winning) return 2;

	return 0;
}

int Board::CheckWinner4Player() const
{
	bool winning = true;

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (i + j < 5) if (!m_tiles[15 - i + 16 * (15 - j)] || m_tiles[15 - i + 16 * (15 - j)]->GetPlayerNr() != 1) winning = false;
		}
	}
	if (winning) return 1;
	else winning = true;

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (i + j < 5) if (!m_tiles[15 - i + 16 * j] || m_tiles[15 - i + 16 * j]->GetPlayerNr() != 2) winning = false;
		}
	}
	if (winning) return 2;
	else winning = true;

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (i + j < 5) if (!m_tiles[i + 16 * j] || m_tiles[i + 16 * j]->GetPlayerNr() != 3) winning = false;
		}
	}
	if (winning) return 3;
	else winning = true;

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (i + j < 5) if (!m_tiles[i + 16 * (15 - j)] || m_tiles[i + 16 * (15 - j)]->GetPlayerNr() != 4) winning = false;
		}
	}
	if (winning) return 4;

	return 0;
}

void Board::SetBitmap()
{
	al_set_target_bitmap(m_bitmap);
	for (int i = 0; i < 17; i++) {
		al_draw_line(0, 1.5f + 43 * i, 691, 1.5f + 43 * i, al_map_rgb(0, 0, 0), 3);
		al_draw_line(1.5f + 43 * i, 0, 1.5f + 43 * i, 691, al_map_rgb(0, 0, 0), 3);
	}
}

void Board::DisplayBitmap()
{
	al_draw_bitmap(m_bitmap, m_x, m_y, 0);
}

void Board::HighlightTile(int mouse_x, int mouse_y)
{
	if (m_has_move == 0) return;
	int x = (mouse_x - 1.5f - m_x) / 43;
	int y = (mouse_y - 1.5f - m_y) / 43;
	if (x >= 16 || y >= 16) return;
	if (!m_tiles[x + 16 * y]) return;
	if (!m_tiles[x + 16 * y]->CheckOwner(m_has_move)) return;

	//std::cout << "Highlight at (" << x << ", " << y << ")" << std::endl;
	m_tiles[x + 16 * y]->HighlightPawn();
	if (m_highlighted_nr != -1) m_tiles[m_highlighted_nr]->UnhighlightPawn();
	m_highlighted_nr = x + 16 * y;
}

void Board::SetColorWhichPlayer(ALLEGRO_BITMAP * bitmap) const
{
	al_set_target_bitmap(bitmap);
	switch (m_has_move)
	{
	case 1:
		al_clear_to_color(al_map_rgb(255, 0, 0));
		break;
	case 2:
		al_clear_to_color(al_map_rgb(0, 255, 0));
		break;
	case 3:
		al_clear_to_color(al_map_rgb(0, 0, 255));
		break;
	case 4:
		al_clear_to_color(al_map_rgb(255, 255, 0));
		break;
	default:
		al_clear_to_color(al_map_rgb(255, 255, 255));
		break;
	}
}

void Board::SaveToFile(std::ofstream& ofs) const
{
	Board board(*this);
	memcpy_s(board.m_tiles, sizeof(Pawn*) * 16 * 16, this->m_tiles, sizeof(Pawn*) * 16 * 16);

	for (int i = 0; i < 16 * 16; i++) {
		if (!board.m_tiles[i]) continue;
		board.m_tiles[i] = (Pawn*)board.m_tiles[i]->GetPlayerNr();
	}

	ofs.write((char*)&board, sizeof(Board));
	for (int i = 0; i < 16 * 16; i++) {
		board.m_tiles[i] = nullptr;
	}
}

bool Board::LoadFromFile(std::ifstream& ifs)
{
	char buffer[1200] = { 0 };

	ifs.read(buffer, sizeof(Board));
	if (ifs.eof()) return 0;

	Board* board = (Board*)buffer;

	for (int i = 0; i < 16 * 16; i++) {
		if (!board->m_tiles[i]) continue;
		if ((int)board->m_tiles[i] < 0 || (int)board->m_tiles[i] > 4) return false;

		int x = i % 16;
		int y = i / 16;

		board->m_tiles[i] = new Pawn((int)board->m_tiles[i], m_x + 3 + 43 * x, m_y + 3 + 43 * y);
	}

	*this = *board;
	SetBitmap();

	return true;
}

Board& Board::operator=(const Board& board)
{
	for (int i = 0; i < 16 * 16; i++) {
		if (!m_tiles[i]) continue;
		else delete m_tiles[i];
	}

	memcpy_s(this->m_tiles, sizeof(Pawn*) * 16 * 16, board.m_tiles, sizeof(Pawn*) * 16 * 16);
	m_highlighted_nr = board.m_highlighted_nr;
	m_players = board.m_players;
	m_has_move = board.m_has_move;

	return *this;
}
