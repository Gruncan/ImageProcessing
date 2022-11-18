

#ifndef IMAGEPROCESSING_PGM_H
#define IMAGEPROCESSING_PGM_H

#include <string>
#include "Netpbm.h"

namespace Netpbm {

    /**
     * F scale image going from 0-colour
     */
    class PGM : public Netpbm::Netpbm {
    private:
        unsigned int colour;
    public:
        PGM(unsigned int width, unsigned int height, unsigned int colour) : Netpbm::Netpbm(width, height, 2) {
            this->colour = colour;
        }

        PGM(unsigned int width, unsigned int height) : PGM(width, height, 15) {

        }

        PGM() : Netpbm::Netpbm(2) {
            this->colour = -1;
        }

        unsigned int getMaxColour() override {
            return this->colour;
        }

        void setMaxColour(unsigned int c) override {
            this->colour = c;
        }


    };


}


#endif //IMAGEPROCESSING_PGM_H
