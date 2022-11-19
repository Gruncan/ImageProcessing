

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
    public:
        PGM(unsigned int width, unsigned int height, unsigned int colour) : Netpbm::Netpbm(width, height, 2, colour) {

        }

        PGM(unsigned int width, unsigned int height) : PGM(width, height, 15) {

        }

        PGM() : Netpbm::Netpbm(2) {
            this->colour = -1;
        }


        static void test() {
            std::cout << "in test" << std::endl;
        }
    };


}


#endif //IMAGEPROCESSING_PGM_H
