

#ifndef IMAGEPROCESSING_PGM_H
#define IMAGEPROCESSING_PGM_H

#include <string>
#include "Netpbm.h"

namespace Netpbm {


    class PGM : public Netpbm::Netpbm {
    private:
        int colour: 4;
    public:
        PGM(int width, int height, unsigned char colour) : Netpbm::Netpbm(width, height, 2) {
            this->colour = colour;
        }

        PGM(int width, int height) : PGM(width, height, 15) {

        }

        PGM() : Netpbm::Netpbm(2) {
            this->colour = -1;
        }

        int getColour() override {
            return this->colour;
        }

    };


}


#endif //IMAGEPROCESSING_PGM_H
