// C File
//
// Blink two LEDs connected to the GPIO ports of a
// Raspberry Pi 3 in a binary pattern
// until Ctrl+C is entered;
//
// Uses GPIO23 and GPIO17

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "timer_blinking_leds.h"

const char *chipname = "gpiochip0";
struct gpiod_chip *chip;
struct gpiod_line *led0;    // Red LED 0
struct gpiod_line *led1;    // Red LED 1

int led_alarm_count;

void led_alarm( int sig_num ) {
  if ( sig_num == SIGALRM ) {
    ++led_alarm_count;
    int led0_state;

    TOGGLE_LED( led0, led0_state )

    if ( led_alarm_count == NUM_LED0_PERIODS ) {
      for( int index = 0; index < LED1_NUM_BLINKS; ++index ) {
        gpiod_line_set_value(led1, 1);
        usleep(LED1_BLINK_PERIOD/2);
        TOGGLE_LED( led0, led0_state )
        gpiod_line_set_value(led1, 0);
        usleep(LED1_BLINK_PERIOD/2);
      }
      led_alarm_count = 0;
    }    
    usleep(LED0_USECS_PER_PERIOD);
  } // end of if ( sig_num == SIGALRM ) {
}


int main(int argc, char **argv) {

  int i = 0;
  led_alarm_count = 0;

  // Open GPIO chip
  chip = gpiod_chip_open_by_name(chipname);

  // Open GPIO lines
  led0 = gpiod_chip_get_line(chip, LED0_GPIO_LINE);
  led1 = gpiod_chip_get_line(chip, LED1_GPIO_LINE);

  // Open LED lines for output
  gpiod_line_request_output(led0, "timer_blinking_leds", 0);
  gpiod_line_request_output(led1, "timer_blinking_leds", 0);

  struct sigaction act;
  act.sa_handler = led_alarm;
  sigaction( SIGALRM, &act, 0 );
  
  while (true) {
    ualarm( 5000, 0 );
   
    // Uses system timer which indirectly uses interrupt 
    // to determine the next time to signal SIGALRM
    usleep( LED0_USECS_PER_PERIOD );
  }

  // Release lines and chip
  gpiod_line_release(led0);
  gpiod_line_release(led1);
  gpiod_chip_close(chip);

  return 0;
}

// end of C file for main
