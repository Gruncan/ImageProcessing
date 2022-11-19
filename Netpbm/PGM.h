

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


        bool exportImageBody(std::ofstream &outImage) override {
            for (int i = 0; i < this->width * this->height; ++i) {
                if (i % this->width == 0 && i != 0)
                    outImage << std::endl;

                outImage << this->imageArray[i] << " ";
            }
            return true;
        }

        bool exportImageHeader(std::ofstream &outImage) override {
            outImage << "P" << this->VERSION_N << std::endl;
            outImage << this->width << " " << this->height << std::endl;
            outImage << this->colour;
            return true;
        }

        bool importImageBody(std::vector<std::string> &inFile) override {
            return false;
        }

        bool importImageHeader(std::vector<std::string> &inFile) override {
            return false;
        }


    };


}


#endif //IMAGEPROCESSING_PGM_H
