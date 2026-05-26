#include "bsp.h"
#include "blinky.h"

int main(void) {
    BSP_init();
    QF_init();
    Blinky_ctor();
    Blinky_start();
    return QF_run();
}
