#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "functions.h"
#include "menu.h"

int main() {

	Map * mapTask = createMap(is_equal_int);
	
	mostrarMenu(mapTask);
	return 0;

}