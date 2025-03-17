#include "../../../editor.h"

void	sc_delete_line(t_editor *e)
{
	e->sel->is_active = 0;
	delete_line(e, get_line(e, e->cursor->y));
}
