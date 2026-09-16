#include <stdint.h>
#include <stdbool.h>

uint8_t read_cmos_register(uint8_t reg);
uint8_t bcd_to_decimal(uint8_t bcd_number);
bool cmos_update_register();
void readTime();
