// safety againts double-include
#ifndef pca9635RGB_h
#define pca9635RGB_h
#include <Arduino.h> 
#include <pca9635.h>
#include <pca9635RGB.h>

class pca9635multiRGB : public pca9635RGB
{
    public:
        // Initialize the object and chip        
        void begin(uint8_t first_board, byte last_board, uint8_t wire_begin);
        // A funky way to handle optional arguments
        void begin(uint8_t first_board, byte last_board);
        void begin();
        uint8_t set_rgb(uint8_t ledno, byte rcycle, byte gcycle, byte bcycle);
        
};

#endif
// *********** END OF CODE **********
