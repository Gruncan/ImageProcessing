

#ifndef IMAGEPROCESSING_PBM_H
#define IMAGEPROCESSING_PBM_H


#include "Netpbm.h"

namespace Netpbm {

    /**
     * Most basic 0-1 image
     */
    class PBM : public Netpbm::Netpbm {
    public:
        PBM(unsigned int width, unsigned int height) : Netpbm::Netpbm(width, height, 1) {

        }

        PBM() : Netpbm::Netpbm(1) {

        }

        void setMaxColour(unsigned int colour) override {

        }

        unsigned int getMaxColour() override {
            return -1;
        }

    };

}


#endif //IMAGEPROCESSING_PBM_H
