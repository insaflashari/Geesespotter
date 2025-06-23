#include <ctime>
#include "geesespotter_lib.h"

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    game();
    return 0;
}
