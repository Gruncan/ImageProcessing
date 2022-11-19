

#ifndef IMAGEPROCESSING_PBM_H
#define IMAGEPROCESSING_PBM_H


#include "Netpbm.h"

namespace Netpbm {

    /**
     * Most basic 0-1 image
     */
    class PBM : public Netpbm::Netpbm {
    public:
        PBM(unsigned int width, unsigned int height) : Netpbm::Netpbm(width, height, 1, 1) {

        }

        PBM() : Netpbm::Netpbm(1) {

        }

    protected:
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


#endif //IMAGEPROCESSING_PBM_H
