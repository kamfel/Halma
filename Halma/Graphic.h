#pragma once

struct ALLEGRO_BITMAP;

class Graphic
{
protected:
	ALLEGRO_BITMAP* m_bitmap;
	float m_x, m_y;
	~Graphic();
public:
	Graphic() = delete;
	Graphic(float x, float y, int width, int height);

	virtual void SetBitmap() = 0;
	virtual void DisplayBitmap() = 0;
};

