CC       = gcc
CFLAGS   = -Wall -Wpedantic -O3
PREFIX   = /usr/local/bin/
PROGNAME = cscr

all: main.o color.o cube.o diagram.o 
	$(CC) $(CFLAGS) main.o color.o cube.o diagram.o -o $(PROGNAME)

install:
	cp $(PROGNAME) $(PREFIX)

uninstall:
	rm $(PREFIX)$(PROGNAME)

clean:
	-rm -f *.o




main.o: main.c diagram.h cube.h color.h
color.o:  color.c color.h
cube.o: cube.c cube.h
diagram.o: diagram.c diagram.h cube.h color.h
