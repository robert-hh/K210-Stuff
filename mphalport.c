#include <string.h>

#include "py/obj.h"
#include "py/mpstate.h"
#include "py/mphal.h"
#include "extmod/misc.h"
#include "lib/utils/pyexec.h"
#include "mphalport.h"

#include "sleep.h"

#include "encoding.h"
void mp_hal_delay_ms(mp_uint_t ms) {
	msleep(ms);
}

void mp_hal_delay_us(mp_uint_t us) {
	usleep(us);
}

mp_uint_t mp_hal_ticks_us(void) {
    return (read_cycle())/160;
}

mp_uint_t mp_hal_ticks_ms(void) {
    return (read_cycle())/160000;
}

mp_uint_t mp_hal_ticks_cpu(void) {
    return (read_cycle());
}


