#ifndef BSP_H_
#define BSP_H_

#include <stdint.h>

void BSP_init(void);
void BSP_ledOn(void);
void BSP_ledOff(void);
void BSP_ledToggle(void);
void BSP_uartPut(uint8_t byte);
uint32_t BSP_getTicks(void);
void BSP_onTick(void);

#endif

