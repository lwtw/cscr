#ifndef CUBE_H
#define CUBE_H




#include <stdbool.h>




struct cube_turn {
	char face;
	bool half_turn;
	bool prime;
};

struct cube_scramble {
	struct cube_turn *sequence;
	int              length;
};




void cube_generate_scramble (struct cube_scramble *s, int length);
void cube_destroy_scramble  (struct cube_scramble *s);




#endif
