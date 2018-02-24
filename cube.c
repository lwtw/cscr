#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "cube.h"




void cube_generate_scramble (struct cube_scramble *s, int length)
{
	char faces[]     = "UDFBLR";
	char opposites[] = "DUBFRL";




	s->sequence = calloc(sizeof(struct cube_turn), length);
	s->length   = 0;




	srand(time(NULL) + getpid());

	while (s->length < length) {
		struct cube_turn c;




		int face_choice = random() % strlen(faces);
		c.face          = faces[face_choice];
		c.half_turn     = (bool) (random() % 2);




		if (c.half_turn) {
			c.prime = false;
		} else {
			c.prime = (bool) (random() % 2);
		}




		for (int i = s->length - 1; i >= -1; i--) {
			if (
				s->sequence[i].face == c.face ||
				s->sequence[i].face == opposites[face_choice]
			) {
				break;
			} else {
				memcpy(&(s->sequence[s->length]), &c, sizeof(c));
				s->length++;

				break;
			}
		}
	}
}




void cube_destroy_scramble (struct cube_scramble *s)
{
	free(s->sequence);

	s->sequence = NULL;
	s->length   = 0;
}
