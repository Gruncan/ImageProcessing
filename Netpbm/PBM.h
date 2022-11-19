

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

        bool importImageBody(std::vector<std::string> &body) override {
            if (body.size() != this->height) return false;

            int c = 0;
            this->imageArray = (unsigned int *) malloc(this->width * this->height * sizeof(unsigned int));
            for (const std::string &line: body) {
                std::list<unsigned int> split = Netpbm::string_split(line);
                if (split.size() != this->width) return false;

                for (int i = c; i < c + this->width; ++i) {
                    this->imageArray[i] = split.front();
                    split.pop_front();
                }
                c += (int) this->width;
            }
            return true;
        }

        bool importImageHeader(std::vector<std::string> &file) override {
            std::string type;
            bool width_height = false;

            while (!width_height) {
                std::string line = file.front();
                file.erase(file.begin());

                if (type.empty()) {
                    type = line;
                } else {
                    std::list<unsigned int> split = Netpbm::Netpbm::string_split(line);
                    this->width = split.front();
                    split.pop_front();
                    this->height = split.front();

                    width_height = true;
                }
            }

            this->__setN();
            return true;
        }

    };

}


#endif //IMAGEPROCESSING_PBM_H
