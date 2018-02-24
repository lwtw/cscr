TODO
====

## Features

* Add interactive Timer
* Add CLI options:
	* --version | -v, to print the program version to stdout
	* --help | -h, to print a short usage summary to stdout
	* --mode [options] | -m[options], for following modes:
		* interactive mode [i]
		* timer [t]
		* scramble [s]
		* diagram [d]
	* --scramble [sequence] | -s[sequence], to enter a custom scramble snd show its result
	* --read-scramble | -r, to read a scramble sequence from stdin and show its result
* Write a man page and add it to the install rule of the Makefile
