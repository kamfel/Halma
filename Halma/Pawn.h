#pragma once
#include "Graphic.h"
class Pawn : public Graphic
{
private:
	int m_player_nr;
public:
	Pawn() = delete;
	Pawn(int player_nr, float x, float y);
	~Pawn();

	int GetPlayerNr() const { return m_player_nr; }

	void SetBitmap() override;
	void DisplayBitmap() override;
	void HighlightPawn();
	void UnhighlightPawn();

	void Move(int x, int y, int x_board, int y_board);
	bool CheckOwner(int player_nr) { return player_nr == m_player_nr ? true : false; }

};

