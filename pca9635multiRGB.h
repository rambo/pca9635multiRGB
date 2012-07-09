// safety againts double-include
#ifndef pca9635RGB_h
#define pca9635RGB_h
#include <Arduino.h> 
#include <pca9635.h>
#include <pca9635RGB.h>

//class pca9635multiRGB : public pca9635RGB
class pca9635multiRGB
{
    public:
        // Initialize the object and chip        
        void begin(byte board_count, boolean wire_begin);
        // A funky way to handle optional arguments
        void begin(byte board_count);
        void begin();
        boolean set_rgb(byte ledno, byte rcycle, byte gcycle, byte bcycle);

    private:
        pca9635RGB board_instance;
        byte current_board_num;
        byte first_board;
        byte last_board;
        byte board_count;
};

#endif
// *********** END OF CODE **********
