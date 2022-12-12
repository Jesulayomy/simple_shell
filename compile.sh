#!/bin/bash

clear

echo "Compiling . . ."

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 add_node.c  get_commands.c  _getline.c util_funcs.c main.c -o testexec

# tests_rss/test.c

if [[ $? == 0 ]]; then
	echo -e "\tCompilation successful, No errors encountered\n"
	sleep 1
else
	echo -e "Unable to compile file, Resolve the errors above\n"
	exit 1
fi

echo -e "Running testexec with valgrind . . .\n"

valgrind --show-leak-kinds=all --tool=memcheck --leak-check=full --track-origins=yes ./testexec
