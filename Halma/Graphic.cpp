#include <allegro5\allegro.h>
#include "Graphic.h"


Graphic::Graphic(float x, float y, int width, int height)
	:m_x(x), m_y(y)
{
	m_bitmap = al_create_bitmap(width, height);
	al_set_target_bitmap(m_bitmap);
	al_clear_to_color(al_map_rgba(255, 255, 255, 0));
}


Graphic::~Graphic()
{
	al_destroy_bitmap(m_bitmap);
}
