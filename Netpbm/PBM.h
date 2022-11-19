

#ifndef IMAGEPROCESSING_PBM_H
#define IMAGEPROCESSING_PBM_H


#include "Netpbm.h"

namespace Netpbm {

    /**
     * Most basic 0-1 image
     */
    class PBM : public Netpbm::Netpbm {
    private:
        unsigned int colour;
    public:
        PBM(unsigned int width, unsigned int height) : Netpbm::Netpbm(width, height, 1) {
            this->colour = -1;
        }

        PBM() : Netpbm::Netpbm(1) {
            this->colour = -1;
        }

        void setMaxColour(unsigned int colour) override {
            this->colour = colour;
        }

        unsigned int getMaxColour() override {
            return this->colour;
        }

    };

}


#endif //IMAGEPROCESSING_PBM_H
