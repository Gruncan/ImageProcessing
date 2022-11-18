

#ifndef IMAGEPROCESSING_PBM_H
#define IMAGEPROCESSING_PBM_H


#include "Netpbm.h"

namespace Netpbm {

    class PBM : public Netpbm::Netpbm {
    public:
        PBM(int width, int height) : Netpbm::Netpbm(width, height, 1) {

        }

    };

}


#endif //IMAGEPROCESSING_PBM_H
