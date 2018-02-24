#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "diagram.h"
#include "color.h"
#include "cube.h"




void cube_diagram_init (struct cube_diagram *d)
{
	for (int i = 0; i< 3; i++) {
		d->up[i]   = calloc(sizeof(char), 3);
		d->left[i] = calloc(sizeof(char), 3);
		d->front[i] = calloc(sizeof(char), 3);
		d->right[i] = calloc(sizeof(char), 3);
		d->back[i]  = calloc(sizeof(char), 3);
		d->down[i]  = calloc(sizeof(char), 3);

		memcpy(d->up[i],    "www", 3);
		memcpy(d->left[i],  "ooo", 3);
		memcpy(d->front[i], "ggg", 3);
		memcpy(d->right[i], "rrr", 3);
		memcpy(d->back[i],  "bbb", 3);
		memcpy(d->down[i],  "yyy", 3);
	}
}




void triple_free (char **c)
{
	for (int i = 0; i < 3; i++) {
		free(c[i]);
	}
}




void cube_diagram_row (char **f, int row)
{
	char *r = f[row];

	printf("  ");

	for (int i = 0; i < 3; i++) {
		switch (r[i]) {
		case 'w':
			color_start(WHITE);
			break;
		case 'o':
			color_start(ORANGE);
			break;
		case 'g':
			color_start(GREEN);
			break;
		case 'r':
			color_start(RED);
			break;
		case 'b':
			color_start(BLUE);
			break;
		case 'y':
			color_start(YELLOW);
			break;
		}

		printf("▗▖"); // U+2597 U+2596
		color_end();
	}
}




void cube_diagram_show (struct cube_diagram *d)
{
	printf("\n");

	for (int i = 0; i < 3; i++) {
		printf("           ");
		cube_diagram_row(d->up, i);
		printf("\n");
	}

	printf("\n");

	for (int i = 0; i < 3; i++) {
		printf("   ");
		cube_diagram_row(d->left, i);
		cube_diagram_row(d->front, i);
		cube_diagram_row(d->right, i);
		cube_diagram_row(d->back, i);
		printf("\n");
	}

	printf("\n");

	for (int i = 0; i < 3; i++) {
		printf("           ");
		cube_diagram_row(d->down, i);
		printf("\n");
	}

	printf("\n");
}




void cube_diagram_turn_face (struct cube_diagram *d, struct cube_turn *t)
{
	char **f1;
	char f2[3][3];




	switch (t->face) {
	case 'U':
		f1 = d->up;
		break;
	case 'D':
		f1 = d->down;
		break;
	case 'L':
		f1 = d->left;
		break;
	case 'R':
		f1 = d->right;
		break;
	case 'F':
		f1 = d->front;
		break;
	case 'B':
		f1 = d->back;
		break;
	default:
		return;
	}




	memcpy(f2, f1, 3);

	for (int i = 0; i < 3; i++) {
		memcpy(f2[i], f1[i], 3);
	}




	if (t->prime) {
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				f1[y][x] = f2[x][2 - y];
			}
		}
	} else {
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				f1[y][x] = f2[2 - x][y];
			}
		}
	}
}




void cube_diagram_apply_turn (struct cube_diagram *d, struct cube_turn *t)
{
	char tmp[3];
	bool reverse;
	bool lock = false;
	int  x;
	int  y;

	switch (t->face) {
	case 'U':
		reverse = t->prime;
		y       = 0;
		lock    = true;

	case 'E':
		if (!lock) {
			reverse = !t->prime;
			y       = 1;
			lock    = true;
		}

	case 'D':
		if (!lock) {
			reverse = !t->prime;
			y       = 2;
		}


		if (reverse) {
			memcpy(tmp, d->back[y], 3);
			memcpy(d->back[y], d->right[y], 3);
			memcpy(d->right[y], d->front[y], 3);
			memcpy(d->front[y], d->left[y], 3);
			memcpy(d->left[y], tmp, 3);
		} else {
			memcpy(tmp, d->left[y], 3);
			memcpy(d->left[y], d->front[y], 3);
			memcpy(d->front[y], d->right[y], 3);
			memcpy(d->right[y], d->back[y], 3);
			memcpy(d->back[y], tmp, 3);
		}

		break;




	case 'L':
		reverse = t->prime;
		x       = 0;
		lock    = true;

	case 'M':
		if (!lock) {
			reverse = t->prime;
			x       = 1;
			lock    = true;
		}

	case 'R':
		if (!lock) {
			reverse = !t->prime;
			x       = 2;
		}


		if (reverse) {
			for (int i = 0; i < 3; i++) {
				tmp[i]                = d->up[i][x];
				d->up[i][x]           = d->front[i][x];
				d->front[i][x]        = d->down[i][x];
				d->down[i][x]         = d->back[2 - i][2 - x];
				d->back[2 - i][2 - x] = tmp[i];
			}
		} else {
			for (int i = 0; i < 3; i++) {
				tmp[i]                = d->up[i][x];
				d->up[i][x]           = d->back[2 - i][2 - x];
				d->back[2 - i][2 - x] = d->down[i][x];
				d->down[i][x]         = d->front[i][x];
				d->front[i][x]        = tmp[i];
			}
		}

		break;




	case 'F':
		reverse = t->prime;
		y       = 2;
		lock    = true;

	case 'S':
		if (!lock) {
			reverse = t->prime;
			y       = 1;
			lock    = true;
		}

	case 'B':
		if (!lock) {
			reverse = !t->prime;
			y       = 0;
		}


		if (reverse) {
			for (int i = 0; i < 3; i++) {
				tmp[i]                = d->up[y][i];
				d->up[y][i]           = d->right[i][2 - y];
				d->right[i][2 - y]    = d->down[2 - y][2 - i];
				d->down[2 - y][2 - i] = d->left[2 - i][y];
				d->left[2 - i][y]     = tmp[i];
			}
		} else {
			for (int i = 0; i < 3; i++) {
				tmp[i]                = d->up[y][i];
				d->up[y][i]           = d->left[2 - i][y];
				d->left[2 - i][y]     = d->down[2 - y][2 - i];
				d->down[2 - y][2 - i] = d->right[i][2 - y];
				d->right[i][2 - y]    = tmp[i];
			}
		}

		break;

	}




	cube_diagram_turn_face(d, t);




	if (t->half_turn) {
		struct cube_turn tt;

		tt.face      = t->face;
		tt.half_turn = false;
		tt.prime     = t->prime;

		cube_diagram_apply_turn(d, &tt);
	}
}




void cube_diagram_free (struct cube_diagram *d)
{
	triple_free(d->up);
	triple_free(d->left);
	triple_free(d->front);
	triple_free(d->right);
	triple_free(d->back);
	triple_free(d->down);
}
