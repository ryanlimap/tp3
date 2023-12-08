// main.c

#include "simulation.h"
#include <stdlib.h>

int main() {
    srand((unsigned int)time(NULL));
    simulate_process();
    return 0;
}
