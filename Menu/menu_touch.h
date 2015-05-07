#include <stdint.h>

void menu_touch_init();
void menu_get_touch_coordinates(uint16_t* X, uint16_t* Y);
uint8_t menu_touch_pressed();