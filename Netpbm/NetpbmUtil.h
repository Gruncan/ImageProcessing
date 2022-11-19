

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


        convert.setImageArray(copy.getImageArray());

        // Replace all 1s with max colour
        convert * convert.getMaxColour();

        // invert to keep black being lowest number
        convert.invertImage();

        return convert;
    }

    PBM fromPGMToPBM(PGM &pgm) {
        PGM copy;
        pgm.copy(copy);

        PBM convert = PBM(copy.getWidth(), copy.getHeight());

        convert.setImageArray(copy.getImageArray());
        convert != 0;

        convert.setMaxColour(1);

        convert.invertImage();

        convert.setMaxColour(-1);

        return convert;

    }


}


#endif //IMAGEPROCESSING_NETPBMUTIL_H
