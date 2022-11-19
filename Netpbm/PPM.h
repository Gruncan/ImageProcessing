

#ifndef IMAGEPROCESSING_PPM_H
#define IMAGEPROCESSING_PPM_H

#include <cstddef>
#include "Netpbm.h"

namespace Netpbm {

    class PPM : public Netpbm::Netpbm {
    private:
    public:
        PPM(unsigned int width, unsigned int height, unsigned int colour) : Netpbm::Netpbm(height, width, 3, colour) {
        }

        PPM(int width, int height) : PPM(width, height, 255) {

        }

        PPM() : Netpbm::Netpbm(3) {

        }

    };


}


#endif //IMAGEPROCESSING_PPM_H
