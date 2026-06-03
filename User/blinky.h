#ifndef BLINKY_H_
#define BLINKY_H_

#include "qpc.h"

typedef struct {
    QActive super;
    QTimeEvt timeEvt;
} Blinky;

void Blinky_ctor(void);
void Blinky_start(void);

#endif
