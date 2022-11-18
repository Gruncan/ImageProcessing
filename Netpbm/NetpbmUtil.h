

#ifndef IMAGEPROCESSING_NETPBMUTIL_H
#define IMAGEPROCESSING_NETPBMUTIL_H

#include "PBM.h"
#include "PGM.h"
#include "PPM.h"

namespace Netpbm {


    PGM fromPBMToPGM(PBM &pbm) {
        PBM copy;
        pbm.copy(copy);

        PGM convert = PGM(copy.getWidth(), copy.getHeight());

        std::cout << copy << std::endl;

        std::cout << "\n" << convert << std::endl;


        convert.setImageArray(copy.getImageArray());

        // Replace all 1s with max colour
        convert * convert.getMaxColour();

        // invert to keep black being lowest number
        convert.invertImage();

        return convert;
    }


}


#endif //IMAGEPROCESSING_NETPBMUTIL_H
