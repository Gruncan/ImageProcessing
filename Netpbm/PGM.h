

#ifndef IMAGEPROCESSING_PGM_H
#define IMAGEPROCESSING_PGM_H

#include <string>
#include "Netpbm.h"

namespace Netpbm {


    class PGM : public Netpbm::Netpbm {
    private:
        unsigned char colour: 4;
    public:
        PGM(int width, int height, unsigned char colour) : Netpbm::Netpbm(width, height, 2) {
            this->colour = colour;
        }

        PGM(int width, int height) : PGM(width, height, 15) {

        }

        int getColour() {
            return this->colour;
        }

    };


}


#endif //IMAGEPROCESSING_PGM_H
