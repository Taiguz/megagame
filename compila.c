#include <stdio.h>
#include <stdlib.h>



int main(int argc, char const *argv[])
{



	system("gcc mega_game.c megalib.c -lm -c");
	system("gcc mega_game.o megalib.o -o megagame");

	return 0;
}
