#include "blinky.h"
#include "bsp.h"

enum AppSignals {
    TIMEOUT_SIG = Q_USER_SIG,
    MAX_PUB_SIG
};

static QState Blinky_initial(Blinky * const me, QEvt const * const e);
static QState Blinky_off(Blinky * const me, QEvt const * const e);
static QState Blinky_on(Blinky * const me, QEvt const * const e);

static Blinky l_blinky;
static QEvt const *l_blinkyQueueSto[8];

void Blinky_ctor(void) {
    QActive_ctor(&l_blinky.super, Q_STATE_CAST(&Blinky_initial));
    QTimeEvt_ctorX(&l_blinky.timeEvt, &l_blinky.super, TIMEOUT_SIG, 0U);
}

void Blinky_start(void) {
    QACTIVE_START(&l_blinky.super,
                  1U,
                  l_blinkyQueueSto,
                  Q_DIM(l_blinkyQueueSto),
                  0,
                  0,
                  0);
}

static QState Blinky_initial(Blinky * const me, QEvt const * const e) {
    (void)me;
    (void)e;
    return Q_TRAN(&Blinky_off);
}

static QState Blinky_off(Blinky * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            BSP_ledOff();
            QTimeEvt_armX(&me->timeEvt, 250U, 250U);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            QTimeEvt_disarm(&me->timeEvt);
            return Q_HANDLED();
        }
        case TIMEOUT_SIG: {
            return Q_TRAN(&Blinky_on);
        }
        default: {
            return Q_SUPER(&QHsm_top);
        }
    }
}

static QState Blinky_on(Blinky * const me, QEvt const * const e) {
    switch (e->sig) {
        case Q_ENTRY_SIG: {
            BSP_ledOn();
            QTimeEvt_armX(&me->timeEvt, 250U, 250U);
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            QTimeEvt_disarm(&me->timeEvt);
            return Q_HANDLED();
        }
        case TIMEOUT_SIG: {
            return Q_TRAN(&Blinky_off);
        }
        default: {
            return Q_SUPER(&QHsm_top);
        }
    }
}

