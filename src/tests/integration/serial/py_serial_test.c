#include "gpio.h"
#include "serial.h"

int main(void) {
  int button = 12;
  int exit = 2;
  gpio_input(button);
  gpio_input(exit);
  serial_init();

  while (1) {
    if (gpio_pin(button, GET) == ON) {
      serial_put_char('1');
    }

    if (gpio_pin(exit, GET) == ON) {
      serial_put_char('q');
    }
  }
}
