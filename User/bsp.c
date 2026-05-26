#include "bsp.h"
#include "led.h"
#include "usart.h"

#include "../3rd_party/qpc_7_3_4/include/qpc.h"

static volatile uint32_t l_ticks;

void BSP_init(void) {
    SystemCoreClockUpdate();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    LED_Init();
    USART1_Init(115200U);
    BSP_ledOff();
    l_ticks = 0U;
}

void BSP_ledOn(void) {
    led1 = 0;
}

void BSP_ledOff(void) {
    led1 = 1;
}

void BSP_ledToggle(void) {
    led1 = !led1;
}

void BSP_uartPut(uint8_t byte) {
    USART1_SendByte(byte);
}

uint32_t BSP_getTicks(void) {
    return l_ticks;
}

void BSP_onTick(void) {
    ++l_ticks;
}

void QF_onStartup(void) {
    (void)SysTick_Config(SystemCoreClock / 1000U);
#ifdef Q_SPY
    QS_INIT((void *)0);
    QS_GLB_FILTER(QS_ALL_RECORDS);
#endif
}

void QF_onCleanup(void) {
}

uint8_t QS_onStartup(void const *arg) {
    (void)arg;
    static uint8_t qsBuf[1024];
    QS_initBuf(qsBuf, (uint_fast32_t)sizeof(qsBuf));
    return 1U;
}

void QS_onFlush(void) {
    uint16_t b;
    while ((b = QS_getByte()) != QS_EOD) {
        BSP_uartPut((uint8_t)b);
    }
}

QSTimeCtr QS_onGetTime(void) {
    return BSP_getTicks();
}

void QS_onReset(void) {
    NVIC_SystemReset();
}

void QS_onTestSetup(void) {
}

void QS_onTestTeardown(void) {
}

