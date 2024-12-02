#import <time.h>

clock_t clock(void) {
    return (clock_t)(get_now());
}
