#ifndef DIAGRAM_H
#define DIAGRAM_H




#include "cube.h"




struct cube_diagram {
	char *up[3];
	char *left[3];
	char *front[3];
	char *right[3];
	char *back[3];
	char *down[3];
};




void cube_diagram_init (struct cube_diagram *d);
void cube_diagram_show (struct cube_diagram *d);
void cube_diagram_free (struct cube_diagram *d);
void cube_diagram_apply_turn (struct cube_diagram *d, struct cube_turn *t);




#endif
