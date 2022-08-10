#ifndef __TIMER_BLINKING_LEDS_H__
#define __TIMER_BLINKING_LEDS_H__

#include <gpiod.h>

#ifndef LED1_NUM_BLINKS
# define LED1_NUM_BLINKS 5
#endif

#ifndef LED1_PERIOD_USECS
# define LED1_PERIOD_USECS 3000000
#endif

#ifndef LED1_BLINK_PERIOD
# define  LED1_BLINK_PERIOD ((LED1_PERIOD_USECS)/(LED1_NUM_BLINKS))
#endif

#ifndef LED0_USECS_PER_PERIOD
# define LED0_USECS_PER_PERIOD 65536
#endif

#ifndef MY_CEILING
# define MY_CEILING(N, D)  (((N) + ((D)-1))/(D))
#endif

#ifndef NUM_LED0_PERIODS
# define NUM_LED0_PERIODS MY_CEILING(LED1_PERIOD_USECS, LED0_USECS_PER_PERIOD)
#endif

#ifndef LED0_GPIO_LINE 
# define LED0_GPIO_LINE 23
#endif

#ifndef LED1_GPIO_LINE 
# define LED1_GPIO_LINE 17
#endif

#ifndef TOGGLE_LED
# define TOGGLE_LED( L, S ) { \
  (S) = gpiod_line_get_value((L)); \
  gpiod_line_set_value((L), !(S)); \
}
#endif

#endif // end of #ifndef __TIMER_BLINKING_LEDS_H__
