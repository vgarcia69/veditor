#include "../../editor.h"

int	is_same_pos(t_cursor *p1, t_cursor *p2)
{
	if (p1->xview == p2->xview && p1->yview == p2->yview)
		return (1);
	return (0);
}
