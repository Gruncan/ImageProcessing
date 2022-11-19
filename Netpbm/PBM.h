

#ifndef IMAGEPROCESSING_PBM_H
#define IMAGEPROCESSING_PBM_H


#include "Netpbm.h"

namespace Netpbm {

    /**
     * Most basic 0-1 image
     */
    class PBM : public Netpbm::Netpbm {
    private:
    public:
        PBM(unsigned int width, unsigned int height) : Netpbm::Netpbm(width, height, 1, -1) {

        }

        PBM() : Netpbm::Netpbm(1) {

        }

    };

}


#endif //IMAGEPROCESSING_PBM_H
