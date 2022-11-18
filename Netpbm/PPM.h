

#ifndef IMAGEPROCESSING_PPM_H
#define IMAGEPROCESSING_PPM_H

#include <cstddef>
#include "Netpbm.h"

namespace Netpbm {

    class PPM : public Netpbm::Netpbm {
    private:
        int colour;
    public:
        PPM(int width, int height, int colour) : Netpbm::Netpbm(height, width, 3) {
            this->colour = colour;
        }

        PPM(int width, int height) : PPM(height, width, 255) {

        }

        PPM() : Netpbm::Netpbm(3) {

        }

        unsigned int getMaxColour() override {
            return this->colour;
        }

        void setMaxColour(unsigned int c) override {
            this->colour = c;
        }
    };


}


#endif //IMAGEPROCESSING_PPM_H
