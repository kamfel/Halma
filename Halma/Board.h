#pragma once
#include <string>
#include <fstream>
#include "Graphic.h"
#include "Pawn.h"


class Board : public Graphic
{
private:
	Pawn* m_tiles[16 * 16];
	int m_highlighted_nr;
	int m_players;
	int m_has_move;
public:
	Board();
	Board(const Board& board);
	~Board();

	Pawn** GetTiles() { return m_tiles; }

	void Start2PlayerGame();
	void Start4PlayerGame();

	bool TryMove(int mouse_x, int mouse_y);
	int CheckWinner() const;
	int CheckWinner2Player() const;
	int CheckWinner4Player() const;

	void SetBitmap() override;
	void DisplayBitmap() override;
	void HighlightTile(int mouse_x, int mouse_y);
	void SetColorWhichPlayer(ALLEGRO_BITMAP* bitmap) const;

	void SaveToFile(std::ofstream& ofs) const;
	bool LoadFromFile(std::ifstream& ifs);

	Board& operator=(const Board& buffer);
};

