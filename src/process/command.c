
#include "../../editor.h"

/*
buffer command quand \n send et empty it
*/

/*
raccourcis en cmd

/name file
/tp
/doc
/tabstop
*/
void	command(t_editor *e, char *input)
{
	update_statbar(e, "HELLO");
	e->mode = INSERT;
}
