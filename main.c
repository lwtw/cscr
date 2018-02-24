#include <stdio.h>
#include <stdlib.h>




#include "diagram.h"
#include "cube.h"
#include "color.h"




int main (int argc, const char **argv)
{
	struct cube_scramble s;
	struct cube_diagram  d;
	int    count = 0;
	int    col   = 0;
	int    row   = 0;




	if (argc > 1) {
		count = atoi(argv[1]);
	}

	if (count <= 0) {
		count = 24;
	}




	cube_diagram_init(&d);
	cube_generate_scramble(&s, count);




	for (int i = 0; i < s.length; i++) {
		cube_diagram_apply_turn(&d, &s.sequence[i]);


		if (col >= 31 || col == 0) {
			color_start(GREY);
			printf("\n %i:  ", row);
			col = 0;
			row++;
			color_end();
		}


		switch (s.sequence[i].face) {
		case 'F':
			color_start(GREEN);
			break;
		case 'B':
			color_start(BLUE);
			break;
		case 'L':
			color_start(ORANGE);
			break;
		case 'R':
			color_start(RED);
			break;
		case 'U':
			color_start(WHITE);
			break;
		case 'D':
			color_start(YELLOW);
			break;
		default:
			color_start(GREY);
		}




		printf("%c", s.sequence[i].face);

		if (s.sequence[i].half_turn) {
			printf("2");
			col++;
		} else if (s.sequence[i].prime) {
			printf("'");
			col++;
		}

		col += 2;




		color_end();
		printf(" ");
	}

	printf("\n");

	cube_diagram_show(&d);

	cube_diagram_free(&d);
	cube_destroy_scramble(&s);
}
