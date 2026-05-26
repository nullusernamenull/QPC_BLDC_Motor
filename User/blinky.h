#ifndef BLINKY_H_
#define BLINKY_H_

#include "../3rd_party/qpc_7_3_4/include/qpc.h"

typedef struct {
    QActive super;
    QTimeEvt timeEvt;
} Blinky;

void Blinky_ctor(void);
void Blinky_start(void);

#endif
