#ifndef __usart_H
#define __usart_H

#include "system.h"
#include <stdint.h>

void USART1_Init(u32 bound);
void USART1_SendByte(uint8_t byte);

#endif
