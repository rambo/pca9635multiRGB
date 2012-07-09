#include "pca9635multiRGB.h"

/**
 * board_num is the number selected on the BCD rotary switch
 */
void pca9635multiRGB::begin(byte board_count, boolean wire_begin)
{
    if (wire_begin)
    {
        I2c.begin();
    }
    PCA9635.reset(); // This should reset all drivers on the bus
    PCA9635.set_sleep(0x0); // Wake up oscillators (via all-call)
    delayMicroseconds(500); // Wait for the oscillators to stabilize
    PCA9635.set_driver_mode(0x0); // Default to open-drain mode for all drivers (via all-call)
    PCA9635.set_led_mode(3); // Default to PWM mode for all drivers (via all-call)

    // Initialize each board
    for (byte i=0; i<board_count; i++)
    {
        this->board_instance.begin(i, false, false);
    }
    this->board_instance.set_board_address(0);
    this->current_board_num = 0;
    this->board_count = board_count;
}

// Funky way to handle default arguments
void pca9635multiRGB::begin(byte board_count)
{
    pca9635multiRGB::begin(board_count, true);
}

void pca9635multiRGB::set_board_no(byte board)
{
    if (this->current_board_num == board)
    {
        return;
    }
    this->board_instance.set_board_address(board);
    this->current_board_num = board;
}


boolean pca9635multiRGB::set_rgb(byte ledno, byte rcycle, byte gcycle, byte bcycle)
{

    byte board_no = (ledno/16) % this->board_count;
    this->set_board_no(board_no);
    byte real_ledno = ledno % 16;

    Serial.print("pca9635multiRGB::set_rgb ledno=");
    Serial.println(ledno, DEC);
    Serial.print("pca9635multiRGB::set_rgb board_no=");
    Serial.println(board_no, DEC);
    Serial.print("pca9635multiRGB::set_rgb real_ledno=");
    Serial.println(real_ledno, DEC);


    return this->board_instance.set_rgb(real_ledno, rcycle, gcycle, bcycle);
}

