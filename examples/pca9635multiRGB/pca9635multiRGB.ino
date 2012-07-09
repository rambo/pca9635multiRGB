/**
 * RGB (3x PCA9625 drivers in a handy configuration) led driver board 
 *
 * @see https://github.com/HelsinkiHacklab/reactor/blob/master/blueprints/ledcontroller.brd
 *
 * Remember your I2C pull-up resistors
 */
// Get this from http://dsscircuits.com/articles/arduino-i2c-master-library.html
#include <I2C.h> // For some weird reason including this in the relevant .h file does not work
// For the weirdest reason this does not get to the scope of the libraries
#define I2C_DEVICE_DEBUG
#include <i2c_device.h> // For some weird reason including this in the relevant .h file does not work
#include <pca9635.h> // For some weird reason including this in the relevant .h file does not work
#include <pca9635RGB.h> // For some weird reason including this in the relevant .h file does not work
#include <pca9635multiRGB.h>

// Config defines
#define BOARD_COUNT 5
#define TEST_PWM 90

// Switch to change led to test
#include <Bounce.h>
#define SWITCHPIN 2
Bounce bouncer = Bounce(SWITCHPIN, 250); 

// Container for the device
pca9635multiRGB multirgb;

void setup()
{
    Serial.begin(115200);
    pinMode(SWITCHPIN, INPUT);          
    digitalWrite(SWITCHPIN, HIGH); // pull-up

    I2c.begin();
    I2c.timeOut(500); // 500ms timeout to avoid lockups
    I2c.pullup(false); //Disable internal pull-ups
    I2c.setSpeed(true); // Fast-mode support

    // Set device address and call I2c.begin()
    Serial.println("Initializing led drivers");
    multirgb.begin(5, true);


    // Dump the board register to verify
    for (byte i=0; i<BOARD_COUNT; i++)
    {
        multirgb.set_board_no(i);
        multirgb.board_instance.R.dump_registers(0x0, 0x01);
        multirgb.board_instance.G.dump_registers(0x0, 0x01);
        multirgb.board_instance.B.dump_registers(0x0, 0x01);
        // Dump the led mode registers to check they're correct
        multirgb.board_instance.R.dump_registers(0x14, 0x17);
        multirgb.board_instance.G.dump_registers(0x14, 0x17);
        multirgb.board_instance.B.dump_registers(0x14, 0x17);
        
    }

    /**
     * The init will take care of this
     *
    PCA9635.reset(); // This should reset all drivers on the bus
    PCA9635.set_sleep(0x0); // Wake up oscillators (via all-call)
    PCA9635.set_driver_mode(0x0); // Default to open-drain mode for all drivers (via all-call)
    PCA9635.set_led_mode(3); // Default to PWM mode for all drivers (via all-call)
     */

    Serial.println("Booted");
}

const byte test_leds_max = 16*BOARD_COUNT;
byte ledno=255;
byte bstate;
void loop()
{
    if (bouncer.update())
    {
        bstate = bouncer.read();
        Serial.print("State ");
        Serial.println(bstate, DEC);
        if (bstate)
        {
            Serial.print("Turning OFF led ");
            Serial.println(ledno, DEC);
            switch (ledno%3)
            {
                case 0:
                    multirgb.set_rgb(ledno/3, 0, 0, 0);
                    break;
                case 1:
                    multirgb.set_rgb(ledno/3, 0, 0, 0);
                    break;
                case 2:
                    multirgb.set_rgb(ledno/3, 0, 0, 0);
                    break;
            }

            ledno++;
            ledno = ledno % test_leds_max;
    
            Serial.print("Turning ON led ");
            Serial.println(ledno, DEC);

            switch (ledno%3)
            {
                case 0:
                    multirgb.set_rgb(ledno/3, TEST_PWM, 0, 0);
                    break;
                case 1:
                    multirgb.set_rgb(ledno/3, 0, TEST_PWM, 0);
                    break;
                case 2:
                    multirgb.set_rgb(ledno/3, 0, 0, TEST_PWM);
                    break;
            }
            
        }
    }
}
