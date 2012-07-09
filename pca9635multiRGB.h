// safety againts double-include
#ifndef pca9635multiRGB_h
#define pca9635multiRGB_h
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
        void set_board_no(byte board);
        boolean set_rgb(byte ledno, byte rcycle, byte gcycle, byte bcycle);
        pca9635RGB board_instance;

    protected:
        byte current_board_num;
        byte first_board;
        byte last_board;
        byte board_count;
};

#endif
// *********** END OF CODE **********
