

#ifndef IMAGEPROCESSING_PPM_H
#define IMAGEPROCESSING_PPM_H

#include <cstddef>
#include "Netpbm.h"

namespace Netpbm {

    class PPM : public Netpbm::Netpbm {
    private:
        int colour: 8;
    public:
        PPM(int width, int height, unsigned char colour) : Netpbm::Netpbm(height, width, 3) {
            this->colour = colour;
        }

        int getColour() {
            return this->colour;
        }
    };


}


#endif //IMAGEPROCESSING_PPM_H
