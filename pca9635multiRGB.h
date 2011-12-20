// safety againts double-include
#ifndef pca9635RGB_h
#define pca9635RGB_h
#include <WProgram.h> 
#include <pca9635.h>
#include <pca9635RGB.h>

//class pca9635multiRGB : public pca9635RGB
class pca9635multiRGB
{
    public:
        // Initialize the object and chip        
        void begin(byte first_board, byte last_board, boolean wire_begin);
        // A funky way to handle optional arguments
        void begin(byte first_board, byte last_board);
        void begin();
        boolean set_rgb(byte ledno, byte rcycle, byte gcycle, byte bcycle);
        
};

#endif
// *********** END OF CODE **********
