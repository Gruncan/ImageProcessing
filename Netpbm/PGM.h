

#ifndef IMAGEPROCESSING_PGM_H
#define IMAGEPROCESSING_PGM_H

#include <string>
#include "Netpbm.h"

namespace Netpbm {


    class PGM : public Netpbm::Netpbm {
    private:
        int colour;
    public:
        PGM(int width, int height, unsigned char colour) : Netpbm::Netpbm(width, height, 2) {
            this->colour = colour;
        }

        PGM(int width, int height) : PGM(width, height, 15) {

        }

        PGM() : Netpbm::Netpbm(2) {
            this->colour = -1;
        }

        int getMaxColour() override {
            return this->colour;
        }

        void setMaxColour(int c) override {
            this->colour = c;
        }


    };


}


#endif //IMAGEPROCESSING_PGM_H
