#include "pca963multi5RGB.h"

/**
 * board_num is the number selected on the BCD rotary switch
 */
void pca9635RGB::begin(uint8_t first_board, byte last_board, uint8_t wire_begin)
{
    return false;
    /**
     * TODO: figure out a good way to handle multiple boards
    if (wire_begin)
    {
        I2c.begin();
    }
    PCA9635.reset(); // This should reset all drivers on the bus
    PCA9635.set_sleep(0x0); // Wake up oscillators (via all-call)
    delayMicroseconds(500); // Wait for the oscillators to stabilize
    // Initialize the pca9635 instances with correct addresses
    R.begin(board_num | (0x1 << 5), false, false);
    G.begin(board_num | (0x2 << 5), false, false);
    B.begin(board_num | (0x3 << 5), false, false);
    R.enable_subaddr(1);
    G.enable_subaddr(2);
    B.enable_subaddr(3);
    PCA9635.set_driver_mode(0x0); // Default to open-drain mode for all drivers (via all-call)
    PCA9635.set_led_mode(3); // Default to PWM mode for all drivers (via all-call)
     */
}

// Funky way to handle default arguments
void pca9635RGB::begin(uint8_t first_board, byte last_board)
{
    pca9635RGB::begin(first_board, last_board, true);
}

uint8_t pca9635RGB::set_rgb(uint8_t ledno, byte rcycle, byte gcycle, byte bcycle)
{
    // TODO: When I2C library allows lower level access write as single repeated-start sequence for atomicity
    uint8_t rstat = R.set_led_pwm(ledno, rcycle);
    uint8_t gstat = G.set_led_pwm(ledno, gcycle);
    uint8_t bstat = B.set_led_pwm(ledno, bcycle);
    return rstat && gstat && bstat;
}

/*
pca9635::set_led_pwm(uint8_t ledno, byte cycle)
{

*/
