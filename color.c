#include <stdio.h>

#include "color.h"




void color_start (int c)
{
	printf("\033[38;5;%im", c);
}




void bg_color_start (int c)
{
	printf("\033[48;5;%im", c);
}




void color_end ()
{
	printf("\033[5;0m");
}
